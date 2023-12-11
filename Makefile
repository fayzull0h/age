EXEC = main

CC = g++

CFLAGS = -std=c++20 -Wall -g -lncurses

SRC = $(wildcard *.cc)

OBJECTS = $(SRC:.cc=.o)

${EXEC}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${EXEC}

Engine.o: Engine.cc Engine.h metadata.h subject.h observer.h Item.h
	${CC} ${CFLAGS} -c Engine.cc

GameBoard.o: GameBoard.cc subject.h observer.h metadata.h
	${CC} ${CFLAGS} -c GameBoard.cc

main.o: main.cc Engine.h GameBoard.h Rectangle.h Single.h metadata.h
	${CC} ${CFLAGS} -c main.cc

Item.o: Item.cc metadata.h observer.h PeriodicMovement.h
	${CC} ${CFLAGS} -c Item.cc

Single.o: Single.cc Item.h
	${CC} ${CFLAGS} -c Single.cc

Rectangle.o: Rectangle.cc Item.h PeriodicMovement.h
	${CC} ${CFLAGS} -c Rectangle.cc
