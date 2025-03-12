.DEFAULT_GOAL := Chess.cpp

all: clean test

Chess.cpp
	gcc -o ./target/Chess.out ./src/Chess.cpp 

run: Chess.cpp
	./target/Chess.out

test: Chess.cpp
	./target/Chess.out

clean: 
	rm -rf ./target/*.out
