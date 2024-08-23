CPP = g++
CC = gcc
FLAGS = -Wall -Wextra -Werror
STANDART_CPP=-std=c++17
SANITIZE=-fsanitize=address -g
LFLAGS=$(FLAGS) -lncurses
TST_LIBS = -lcheck
LCOVFLAGS = --ignore-errors inconsistent --ignore-errors mismatch

BACK_TETRIS=$(wildcard brick_game/tetris/backend/*.c)
OBJ_BACK_TETRIS=$(BACK_TETRIS:.c=.o)

BACK_SNAKE=$(wildcard brick_game/snake/backend/*.cpp)
FRONT_CLI=$(wildcard gui/cli/*.c)
OBJ_BACK_SNAKE=$(BACK_SNAKE:.cpp=.o)
TEST_TETRIS=$(wildcard brick_game/tetris/tests/check.c)
TEST_SNAKE=$(wildcard brick_game/snake/tests/check.cpp)

all: install

%.o: %.cpp
	@$(STANDART_CPP) $(CPP) $(FLAGS) -c $< -o $@

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

mkbuild:
	@rm -rf build/
	@mkdir build

uninstall :
	@rm -rf build/
	@echo "\033[31mGame uninstall \033[0m"

install : desktop
	@echo "\033[32mGame install \033[0m"

brick_game_cli : mkbuild back_lib front_lib
	@$(STANDART_CPP) $(CPP) -c brick_game/model.cpp -o build/model.o
	@$(STANDART_CPP) $(CPP) -c controller/controller.cpp -o build/controller.o
	@$(STANDART_CPP) $(CPP) -lncurses build/back_tetris.a build/back_snake.a build/front.a build/model.o build/controller.o gui/cli/brick_game.cpp -o build/BRICK_GAME
	@echo "\033[32mGame install \033[0m"

model :
	@$(STANDART_CPP) $(CPP) -c build/back.a brick_game/model.cpp -o brick_game/model.o

back_lib_snake : $(OBJ_BACK_SNAKE) 
	@ar rc build/back_snake.a $^
	@ranlib build/back_snake.a 
	@rm brick_game/snake/backend/*.o


back_lib : back_lib_snake back_lib_tetris

front_lib:
	@$(STANDART_CPP) $(CPP) -c gui/cli/frontend.cpp -o gui/cli/frontend.o
	@ar rc build/front.a gui/cli/frontend.o
	@ranlib build/front.a 
	@rm gui/cli/*.o

dvi:
	@doxygen .Doxyfile
	@open doxygen/html/index.html

dist: install
	@rm -rf dist.tar.gz
	@tar -cvzf dist.tar.gz build/
	

clang-format:
	clang-format -i brick_game/tetris/backend/*.c brick_game/tetris/*.h gui/cli/*.cpp gui/cli/*.h brick_game/tetris/tests/*.c brick_game/snake/backend.h brick_game/snake/backend/*.cpp brick_game/snake/backend/inc/*.h controller/*.cpp controller/*.h brick_game/*.h brick_game/model*.cpp
	clang-format -i gui/desktop/*.cpp gui/desktop/*.h brick_game/snake/tests/*.cpp

clean :
	rm -rf brick_game/tetris/backend/*.o gui/cli/*.o build/ *.dSYM doxygen/ brick_game/tetris/backend/*.gcda brick_game/tetris/backend/*.gcno *.gcda *gcno *.info .saveScore.txt report/ test dist.tar.gz
	rm -rf brick_game/snake/backend/*.gcda brick_game/snake/backend/*.gcno
	rm -rf .*.txt

sanitize : mkbuild back_lib front_lib
	@$(STANDART_CPP) $(CPP) -c brick_game/model.cpp -o build/model.o
	@$(STANDART_CPP) $(CPP) -c controller/controller.cpp -o build/controller.o
	@$(CPP) $(FLAGS) $(SANITIZE) -lncurses build/back_tetris.a build/back_snake.a build/front.a build/model.o build/controller.o gui/cli/brick_game.cpp -o build/BRICK_SANITAZE
	@echo "\033[32mSanitize done \033[0m"

add_coverage_flag:
	$(eval FLAGS += --coverage)

tests_tetris : clean mkbuild back_lib_tetris
	$(CC) $(FLAGS) $(TEST_TETRIS) build/back_tetris.a $(TST_LIBS) -o test

gcov_report_tetris: add_coverage_flag tests_tetris
	./test
	lcov -t "check" -o check.info -c -d ./  --no-external $(LCOVFLAGS)
	genhtml -o report check.info $(LCOVFLAGS)
	open report/index.html

leaks: install
	leaks -atExit -- ./Game

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .


back_lib_tetris : $(OBJ_BACK_TETRIS) 
	@ar rc build/back_tetris.a $^
	@ranlib build/back_tetris.a 
	@rm brick_game/tetris/backend/*.o

desktop:
	@rm -rf build
	@mkdir build
	@cd build && cmake ../ && make snake
#   && ./snake.app/Contents/MacOS/snake

tests: clean mkbuild back_lib_snake
	@$(CPP) $(FLAGS) $(STANDART_CPP) $(TEST_SNAKE) build/back_snake.a -lgtest -o test

gcov_report: add_coverage_flag tests
	./test
	lcov -t "check" -o check.info -c -d ./  --no-external $(LCOVFLAGS)
	genhtml -o report check.info $(LCOVFLAGS)
	open report/index.html