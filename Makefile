# .DEFAULT_GOAL := Chess.cpp
CXX=g++
CFLAGS=-Wall -c++11
LDFLAGS= -Iinclude -LC:\Users\SriLi\Documents\C++\Chess_project_CLI\include

SRC_F=src
BUILD_F=build

default: chess.exe run

chess.exe: chess.o
	g++ $(BUILD_F)/chess.o $(LDFLAGS) -o $(BUILD_F)/chess.exe

chess.o:
	g++ -c $(SRC_F)/chess.cpp $(LDFLAGS) -o $(BUILD_F)/chess.o

run: chess.exe
	./build/chess.exe