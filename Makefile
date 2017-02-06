CXX=clang++
CXXFLAGS=-std=c++1z -Wall -O2 -g -fno-omit-frame-pointer

.PHONY: all
all: build/libschedule.a build/a.out


build/libschedule.a: schedule.cpp
	$(CXX) $(CXXFLAGS) -c schedule.cpp -o build/schedule.o
	ar rcs build/libschedule.a build/schedule.o
	rm build/schedule.o

build/a.out: build/libschedule.a main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o build/a.out -L./build -lschedule


.PHONY: clean
clean:
	rm build/libschedule.a build/a.out
