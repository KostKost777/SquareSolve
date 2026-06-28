FLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
NODEBUG = -DNMA -g
all: out

out: main.o print_many_stars.o console_interface.o unit_tests_solvesquare.o unit_tests_doubleissame.o unit_tests_solveline.o UI.o double_operations.o Equation_Solve.o skipline.o
	g++ $(NODEBUG) main.o print_many_stars.o console_interface.o unit_tests_solvesquare.o unit_tests_doubleissame.o unit_tests_solveline.o UI.o double_operations.o Equation_Solve.o skipline.o -o out

main.o: main.cpp
	g++ $(NODEBUG) -c main.cpp

print_many_stars.o: print_many_stars.cpp
	g++ $(NODEBUG) -c print_many_stars.cpp

console_interface.o: console_interface.cpp
	g++ $(NODEBUG) -c console_interface.cpp

unit_tests_solvesquare.o: unit_tests_solvesquare.cpp
	g++ $(NODEBUG) -c unit_tests_solvesquare.cpp

unit_tests_solveline.o: unit_tests_solveline.cpp
	g++ $(NODEBUG) -c unit_tests_solveline.cpp

unit_tests_doubleissame.o: unit_tests_doubleissame.cpp
	g++ $(NODEBUG) -c unit_tests_doubleissame.cpp

UI.o: UI.cpp
	g++ $(NODEBUG) -c UI.cpp

double_operations.o: double_operations.cpp
	g++ $(NODEBUG) -c double_operations.cpp

Equation_Solve.o: Equation_Solve.cpp
	g++ $(NODEBUG) -c Equation_Solve.cpp

skipline.o: skipline.cpp
	g++ $(NODEBUG) -c skipline.cpp

