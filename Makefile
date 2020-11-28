CC = gcc
CV = -std=c11

FLAGS = $(CV) -Wall -Wextra -Wpedantic -g -flto -O2 -pipe \
		-fvisibility=hidden -fcf-protection=full \
		-Werror=format-security -Wfloat-conversion \
		-Werror=implicit-function-declaration -Wbad-function-cast#-Werror

BINARY_NAME = x9-foi-torrado

LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image -lm
LOG = @echo -e "\n---> $@"

OBJ = obj
OUTOBJ = -o $@
objects = screen.o game.o main.o input.o \
		  audio.o debug.o text.o graphic.o \
		  particle.o helpers.o glow.o menu.o \
		  background.o stage.o entity.o player.o \
		  common.o scene.o transition.o lvl_one.o \
		  camera.o shake.o texture.o

all: sayhello $(BINARY_NAME)

.PHONY: sayhello
sayhello:
	@echo "===#=== $(BINARY_NAME) ===#==="

$(BINARY_NAME): main.o
	$(LOG)
	$(CC) $(FLAGS) $(objects) $(LIBS) -o $(BINARY_NAME)

main.o: common.o game.o src/main.c
	$(LOG)
	$(CC) -c $(FLAGS) src/main.c $(OUTOBJ)

game.o: common.o screen.o graphic.o input.o debug.o audio.o text.o stage.o src/game.c src/game.h
	$(LOG)
	$(CC) -c $(FLAGS) src/game.c $(OUTOBJ)

input.o: common.o screen.o src/input/input.c common.o src/input/input.h
	$(LOG)
	$(CC) -c $(FLAGS) src/input/input.c $(OUTOBJ)

screen.o: common.o src/screen/screen.c src/screen/screen.h
	$(LOG)
	$(CC) -c $(FLAGS) src/screen/screen.c $(OUTOBJ)

audio.o: src/audio/audio.c src/audio/audio.h src/audio/audio-defs.h
	$(LOG)
	$(CC) -c $(FLAGS) src/audio/audio.c $(OUTOBJ)

debug.o: common.o graphic.o screen.o src/debug/debug.c src/debug/debug.h
	$(LOG)
	$(CC) -c $(FLAGS) src/debug/debug.c $(OUTOBJ)

text.o: common.o graphic.o src/text/text.c src/text/text.h
	$(LOG)
	$(CC) -c $(FLAGS) src/text/text.c $(OUTOBJ)

stage.o: common.o menu.o camera.o lvl_one.o scene.o src/stage/stage.h src/stage/stage.c
	$(LOG)
	$(CC) -c $(FLAGS) src/stage/stage.c $(OUTOBJ)

background.o: common.o graphic.o screen.o src/background/background.h src/background/background.c
	$(LOG)
	$(CC) -c $(FLAGS) src/background/background.c $(OUTOBJ)

graphic.o: screen.o src/graphic/graphic.c src/graphic/graphic.h
	$(LOG)
	$(CC) -c $(FLAGS) src/graphic/graphic.c $(OUTOBJ)

particle.o: common.o helpers.o entity.o graphic.o texture.o src/graphic/effects/particle.c src/graphic/effects/particle.h
	$(LOG)
	$(CC) -c $(FLAGS) src/graphic/effects/particle.c $(OUTOBJ)

shake.o: common.o src/graphic/effects/shake.h src/graphic/effects/shake.c
	$(LOG)
	$(CC) -c $(FLAGS) src/graphic/effects/shake.c $(OUTOBJ)

helpers.o: src/graphic/effects/helpers.h src/graphic/effects/helpers.c
	$(LOG)
	$(CC) -c $(FLAGS) src/graphic/effects/helpers.c $(OUTOBJ)

glow.o: graphic.o helpers.o src/graphic/effects/glow.h src/graphic/effects/glow.c
	$(LOG)
	$(CC) -c $(FLAGS) src/graphic/effects/glow.c $(OUTOBJ)

player.o: entity.o graphic.o input.o src/player/player.h src/player/player.c
	$(LOG)
	$(CC) -c $(FLAGS) src/player/player.c $(OUTOBJ)

camera.o: common.o screen.o shake.o src/camera/camera.h src/camera/camera.c
	$(LOG)
	$(CC) -c $(FLAGS) src/camera/camera.c $(OUTOBJ)

entity.o: common.o src/entity/entity.h src/entity/entity.c
	$(LOG)
	$(CC) -c $(FLAGS) src/entity/entity.c $(OUTOBJ)

fire.o: common.o helpers.o entity.o glow.o particle.o src/graphic/effects/fire.h src/graphic/effects/fire.c
	$(LOG)
	$(CC) -c $(FLAGS) src/graphic/effects/fire.c $(OUTOBJ)

menu.o: scene.o graphic.o input.o screen.o background.o text.o common.o audio.o src/menu/menu.h src/menu/menu.c
	$(LOG)
	$(CC) -c $(FLAGS) src/menu/menu.c $(OUTOBJ)

texture.o: graphic.o src/texture/texture.h src/texture/texture.c
	$(LOG)
	$(CC) -c $(FLAGS) src/texture/texture.c $(OUTOBJ)

lvl_one.o: graphic.o particle.o glow.o background.o player.o entity.o scene.o screen.o common.o src/levels/lvl_one/lvl_one.h src/levels/lvl_one/lvl_one.c
	$(LOG)
	$(CC) -c $(FLAGS) src/levels/lvl_one/lvl_one.c $(OUTOBJ)

common.o: src/common/common.h src/common/common.c
	$(LOG)
	$(CC) -c $(FLAGS) src/common/common.c $(OUTOBJ)

scene.o: transition.o src/scene/scene.h src/scene/scene_defs.h src/scene/scene.c src/scene/scene_p.h
	$(LOG)
	$(CC) -c $(FLAGS) src/scene/scene.c $(OUTOBJ)

transition.o: common.o screen.o entity.o graphic.o src/transition/transition.h src/transition/transition.c
	$(LOG)
	$(CC) -c $(FLAGS) src/transition/transition.c $(OUTOBJ)

.PHONY : clean
clean:
	rm -f $(objects) $(BINARY_NAME)
