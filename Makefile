#OBJS specifies which files to compile as part of the project
OBJS =  Main.cpp Engine.cpp Game.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Snake.run

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -g -w -lSDL2 -o $(OBJ_NAME) -L./
