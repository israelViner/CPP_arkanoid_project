CXX = g++
CC = $(CXX)

CXXFLAGS = -Wall -pedantic -std=c++17
CXXFLAGS += -Werror
# CXXFLAGS += -g3

CPPFLAGS = -I ./includes -I ./src  -I ./settings/includes -I ./settings/src

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main : main.o src/ball.o src/paddle.o src/bricks.o \
src/brick.o  src/lives_player.o src/collision.o src/lives_brick.o \
src/score.o src/game_flow.o src/player.o \
src/top_high_score.o src/evevt_tools.o src/opening_screen.o \
src/brick_classes.o src/graphic_tools.o \
src/audio_icon.o src/gifts.o src/ball_direct.o \
settings/src/fonts_settings.o settings/src/audio.o \
settings/src/texture_settings.o settings/src/structure_bricks_settings.o \
src/explosion.o $(LIBS) 

main.o : main.cpp settings/includes/texture_settings.hpp includes/game_flow.hpp includes/player.hpp \
includes/opening_screen.hpp includes/evevt_tools.hpp includes/top_high_score.hpp \
settings/includes/audio.hpp settings/includes/structure_bricks_settings.hpp includes/brick_types_enum.hpp
src/ball.o : src/ball.cpp includes/ball.hpp includes/player.hpp settings/includes/audio.hpp includes/ball_direct.hpp
src/brick.o : src/brick.cpp includes/brick.hpp includes/brick.hpp 
src/bricks.o : src/bricks.cpp includes/bricks.hpp includes/brick_classes.hpp \
settings/includes/texture_settings.hpp includes/gifts.hpp
src/collision.o : src/collision.cpp includes/collision.hpp includes/brick.hpp includes/ball.hpp \
includes/player.hpp settings/includes/audio.hpp includes/ball_direct.hpp includes/explosion.hpp includes/bricks.hpp
src/lives_player.o : src/lives_player.cpp includes/lives_player.hpp
src/paddle.o : src/paddle.cpp includes/paddle.hpp settings/includes/texture_settings.hpp
src/player.o : src/player.cpp includes/player.hpp
src/score.o : src/score.cpp includes/score.hpp includes/brick.hpp includes/evevt_tools.hpp
src/game_flow.o : src/game_flow.cpp includes/game_flow.hpp settings/includes/fonts_settings.hpp includes/ball.hpp \
includes/bricks.hpp includes/collision.hpp includes/player.hpp includes/top_high_score.hpp includes/opening_screen.hpp includes/evevt_tools.hpp \
includes/graphic_tools.hpp includes/audio_icon.hpp settings/includes/audio.hpp includes/ball_direct.hpp \
settings/includes/texture_settings.hpp
src/top_high_score.o : src/top_high_score.cpp includes/top_high_score.hpp settings/includes/fonts_settings.hpp \
includes/evevt_tools.hpp includes/graphic_tools.hpp settings/includes/audio.hpp settings/includes/texture_settings.hpp
src/opening_screen.o : src/opening_screen.cpp includes/opening_screen.hpp settings/includes/fonts_settings.hpp \
includes/evevt_tools.hpp settings/includes/audio.hpp includes/audio_icon.hpp settings/includes/texture_settings.hpp
src/brick_classes.o : src/brick_classes.cpp includes/brick_classes.hpp
src/evevt_tools.o : src/evevt_tools.cpp includes/evevt_tools.hpp settings/includes/fonts_settings.hpp includes/graphic_tools.hpp
src/graphic_tools.o : src/graphic_tools.cpp includes/graphic_tools.hpp
src/lives_brick.o : src/lives_brick.cpp includes/lives_brick.hpp
src/audio_icon.o : src/audio_icon.cpp includes/audio_icon.hpp settings/includes/texture_settings.hpp
src/gifts.o : src/gifts.cpp includes/gifts.hpp
src/ball_direct.o : src/ball_direct.cpp includes/ball_direct.hpp
src/explosion.o : src/explosion.cpp includes/explosion.hpp settings/includes/audio.hpp includes/brick.hpp includes/bricks.hpp \
includes/player.hpp
settings/src/fonts_settings.o : settings/src/fonts_settings.cpp settings/includes/fonts_settings.hpp
settings/src/structure_bricks_settings.o : settings/src/structure_bricks_settings.cpp settings/includes/structure_bricks_settings.hpp
settings/src/texture_settings.o : settings/src/texture_settings.cpp settings/includes/texture_settings.hpp
settings/src/audio.o : settings/src/audio.cpp settings/includes/audio.hpp

clean :
	$(RM) *.o */*.o settings/src/*.o main
	