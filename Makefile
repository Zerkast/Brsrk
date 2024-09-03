CC = g++
#FLAGS = -O3 -std=c++11
FLAGS = -g -ggdb -std=c++11
INCLUDE = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
S_DIR = src
S_FILES=$(wildcard src/*.cpp)
B_DIR=build
EXEC=./$(B_DIR)/BRSRK

all:Build #scelta predefinita se scrivi solo make

Build:
	$(CC) $(FLAGS) $(S_FILES) -o $(EXEC) $(INCLUDE) 

run:Build #Chiama build e poi esegue con la variabile exec
	$(EXEC)

# clean:
#   rm -rf $(B_DIR)/*
