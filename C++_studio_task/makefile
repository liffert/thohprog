.PHONY: greet build rebuild run clear debug_build

greet:
	@echo "Terminating make - please specify target explicitly"
	@echo "    build   : fast rebuild / build"
	@echo "    D_build   : fast debug rebuild / build"
	@echo "    rebuild : full rebuild"
	@echo "    run     : run after fast rebuild / build"
	@echo "    clean   : perform full clean"

CC=g++
CFLAGS=-c -o
D_CFLAGS=-g -c -o
CREATE_FLAGS=-o 
LIB_FLAGS=-lprogbase -lm
D_build: debug_test
build: test
rebuild: clean test
run: build
	./test
clear:
	rm -rvf *.o test

test: source.o Menu.o beginner.o Easy.o Normal.o
	$(CC) $(CREATE_FLAGS) test source.o Menu.o beginner.o Easy.o Normal.o $(LIB_FLAGS)

debug_test:	D_source.o D_Menu.o D_Beginner.o D_Easy.o D_Normal.o
	$(CC) -g $(CREATE_FLAGS) test D_source.o D_Menu.o D_Beginner.o D_Easy.o D_Normal.o $(LIB_FLAGS)

source.o: source.cpp Menu.h
	$(CC) $(CFLAGS) source.o source.cpp $(LIB_FLAGS)

Menu.o: Menu.cpp Menu.h
	$(CC) $(CFLAGS) Menu.o Menu.cpp $(LIB_FLAGS)

beginner.o: beginner.cpp beginner.h Menu.h
	$(CC) $(CFLAGS) beginner.o beginner.cpp $(LIB_FLAGS)

Easy.o: Easy.cpp Easy.h Menu.h
	$(CC) $(CFLAGS) Easy.o Easy.cpp $(LIB_FLAGS)

Normal.0: Normal.cpp Normal.h Menu.h
	$(CC) $(CFLAGS) Normal.o Normal.cpp $(LIB_FLAGS)

D_source.o: source.cpp Menu.h
	$(CC) $(D_CFLAGS) D_source.o source.cpp $(LIB_FLAGS)

D_Menu.o: Menu.cpp Menu.h
	$(CC) $(D_CFLAGS) D_Menu.o Menu.cpp $(LIB_FLAGS)

D_Beginner.o: beginner.cpp beginner.h Menu.h
	$(CC) $(D_CFLAGS) D_Beginner.o beginner.cpp $(LIB_FLAGS)

D_Easy.o: Easy.cpp Easy.h Menu.h
	$(CC) $(D_CFLAGS) D_Easy.o Easy.cpp $(LIB_FLAGS)

D_Normal.o: Normal.cpp Normal.h Menu.h
	$(CC) $(D_CFLAGS) D_Normal.o Normal.cpp $(LIB_FLAGS)