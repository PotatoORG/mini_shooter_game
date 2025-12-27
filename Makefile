CC = g++
FLAGS = -O3
INC_SFML_FLAG = -lsfml-system -lsfml-window -lsfml-graphics

game : EntityManager.o Entity.o Vec2.o Game.o main.o
	${CC} $^ -o $@ ${INC_SFML_FLAG}

EntityManager.o : EntityManager.cpp
	${CC} ${FLAGS}  -c $^ -o $@

Entity.o : Entity.cpp
	${CC} ${FLAGS}  -c $^ -o $@

Vec2.o : Vec2.cpp
	${CC} ${FLAGS}  -c $^ -o $@

Game.o : Game.cpp
	${CC} ${FLAGS}  -c $^ -o $@

main.o : main.cpp
	${CC} ${FLAGS}  -c $^ -o $@

clean :
	rm -f *.o game
