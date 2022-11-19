CXX = g++
STD = -std=c++17
CFLAG = -Wall -Wextra -Werror -pedantic
TEST_FILES = tests.cpp

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	GTEST:= $(shell pkg-config --cflags --libs gtest 2>/dev/null)
	ifeq ($(GTEST),)
		GTEST:=-DGTEST_HAS_PTHREAD=1 -lgtest -pthread
	endif
	LEAKS_CMD = CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes  --leak-check=full --show-leak-kinds=all ./test
endif
ifeq ($(UNAME), Darwin)
	LEAKS_CMD = CK_FORK=no leaks --atExit -- ./test
	GTEST = -fsanitize=address -DGTEST_HAS_PTHREAD=1 -lgtest -pthread
endif

all: clean install tests

build:
	mkdir build
	cd ./build/ && qmake6 ../ && make && mv s21_Smart_Calc.app Calculator.app

install: build
	mkdir $(HOME)/Desktop/SmartCalc/
	cp -rf build/Calculator.app $(HOME)/Desktop/SmartCalc/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/SmartCalc/

dvi:
	open dvi.md

dist:
	rm -rf SmartCalc
	mkdir SmartCalc
	mkdir SmartCalc/src
	mkdir SmartCalc/src/Model
	mkdir SmartCalc/src/View
	mkdir SmartCalc/src/Control
	mkdir SmartCalc/src/Ui
	cp Makefile *.md *.cpp *.h *.pro SmartCalc/src/
	cp Model/*.h Model/*.cpp SmartCalc/src/Model
	cp View/*.h View/*.cpp SmartCalc/src/View
	cp Control/*.h Control/*.cpp SmartCalc/src/Control
	cp Ui/*.ui SmartCalc/src/Ui
	tar -cvzf SmartCalc.tar.gz SmartCalc
	mv SmartCalc.tar.gz $(HOME)/Desktop/
	rm -rf SmartCalc/

tests: clean
	$(CXX) $(STD) $(CFLAG) -o test $(TEST_FILES) $(GTEST)
	./test

gcov_report: clean
	$(CXX) $(STD) $(CFLAG) -o test $(TEST_FILES) $(GTEST) --coverage
	./test || true
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o  *.gc* report *.a tests test test.info build *.out *.pro.user *.pro.user.* *.dSYM

rebuild: clean all

leaks:
	CK_FORK=no leaks --atExit -- ./test

clang:
	clang-format -n Control/smartCalcController.cpp
	clang-format -n Control/smartCalcController.h
	clang-format -n Model/creditCalculatorModel.cpp
	clang-format -n Model/creditCalculatorModel.h
	clang-format -n Model/smartCalcModel.cpp
	clang-format -n Model/smartCalcModel.h
	clang-format -n View/creditCalculatorView.cpp
	clang-format -n View/creditCalculatorView.h
	clang-format -n View/graphView.cpp
	clang-format -n View/graphView.h
	clang-format -n View/smartCalcView.cpp
	clang-format -n View/smartCalcView.h
	clang-format -n main.cpp

check: leaks clang
