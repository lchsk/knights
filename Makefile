all:
	g++-6 -std=c++14 \
		src/main.cpp \
		src/game.cpp \
		src/core/resource_mgr.cpp \
		src/map/map.cpp \
		src/map/level.cpp \
	-lsfml-graphics -lsfml-window -lsfml-system
