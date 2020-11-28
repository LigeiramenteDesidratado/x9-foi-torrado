#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>
#include "../../common/common.h"

#define DURATION 1000
#define FREQUENCY 60
#define AMPLITUDE 16

typedef struct {
    long duration;
    long start_time;
    long t;

    int freq;

    int sample_count;
    float* samples;

    bool_t is_shaking;

} shake_t;

// Forward declaration
private float __shake_decay(read_only shake_t * shake);
private float __shake_noise(read_only shake_t* shake, int s);
private float __shake_amplitude(read_only shake_t* shake);


shake_t* shake_new(void) {
    shake_t* shake = (shake_t*)malloc(sizeof(shake_t));
    shake->samples = NULL;

    return shake;
}

int shake_ctor(shake_t* shake, int duration, int freq) {

    // The duration in miliseconds
    shake->duration = duration;

    // The frequency in Hz
    shake->freq = freq;

    // The sample count = number of peaks/valleys in the Shake
    shake->sample_count = (duration/1000) * freq;

    // Allocate and populate the samples array with randomized values between -1.0 and 1.0
    shake->samples = (float*)malloc(sizeof(float)*shake->sample_count);
    for (int i = 0; i < shake->sample_count; ++i) {
        shake->samples[i] = (float)(rand() / (float)(RAND_MAX) * 2.0 - 1.0);
    }

    shake->start_time = 0;
    shake->t = 0;
    shake->is_shaking = false_t;

    return 0;
}

void shake_dtor(shake_t* shake) {
    free(shake->samples);
    shake->samples = NULL;
}


void shake_do(shake_t* shake, float* x, float* y) {

    if (shake->is_shaking == false_t) return;

    shake->t = SDL_GetTicks() - shake->start_time;

    if (shake->t > shake->duration) {
        shake->is_shaking = false_t;
    }

    float amp = (__shake_amplitude(shake)*AMPLITUDE);

    if (shake->is_shaking) {
        switch (rand()% 4) {
            case 0:
                *x  = (*x) + amp;
                *y  = (*y) - amp;
                break;

            case 1:
                *x  = (*x) - amp;
                *y  = (*y) + amp;
                break;

            case 2:
                *x  = (*x) - amp;
                *y  = (*y) - amp;
                break;

            default:
                *x  = (*x) + amp;
                *y  = (*y) + amp;
                break;

        }
    }
}

// Start the shake, initializing time variables and flags
void shake_start(shake_t* shake) {

    shake->start_time = SDL_GetTicks();
    shake->t = 0;
    shake->is_shaking = true_t;
}

// Retrieve the amplitude.
private float __shake_amplitude(read_only shake_t* shake) {


    // Get the previous and next sample
    double s = (double)shake->t / 1000L * (double)shake->freq;

    double j = floor(s); int s0 = (int)j;
    int s1 = s0 + 1;

    // Get the current decay
    float k = __shake_decay(shake);

    // reutrn the current amplitide
    return (float)((__shake_noise(shake, s0) + (s - s0) * (__shake_noise(shake, s1) - __shake_noise(shake, s0))) * k);
}


// Retrieve the noise at the specified sample.
// s The randomized sample we are interested in.
private float __shake_noise(read_only shake_t* shake, int s) {

        if (s >= shake->sample_count) return 0;

        // Retrieve the randomized value from the samples
        return shake->samples[s];
}

// Get the decay of the shake as a floating point value from 0.0 to 1.0
private float __shake_decay(read_only shake_t* shake) {

    // Linear decay
    if (shake->t >= shake->duration) { return 0; }
    return ((float)shake->duration - (float)shake->t) / (float)shake->duration;
}
