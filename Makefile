CXX=clang++
CXXFLAGS=-std=c++1z -Wall -O2 -g -fno-omit-frame-pointer

.PHONY: all
all: build/libschedule.a build/a.out


build/libschedule.a: schedule.h schedule.cpp
	$(CXX) $(CXXFLAGS) -c schedule.cpp -o build/schedule.o
	ar rcs build/libschedule.a build/schedule.o

build/a.out: build/libschedule.a main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o build/a.out -L./build -lschedule


.PHONY: clean
clean:
	rm -f build/libschedule.a build/*.out

.PHONY: check
check: build/a.out
	$(CXX) $(CXXFLAGS) -I. tests/basic_test.cpp -o build/basic_test.out -Lbuild -lschedule
	./build/basic_test.out
#	cat tests/Inputs/basic_input.txt | ./build/a.out
	
