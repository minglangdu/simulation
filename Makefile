.PHONY: all goal clean

all: goal clean

.SILENT: goal
.SILENT: clean
goal: ai.cpp map.cpp main.cpp
	echo "Compiling..."
	g++ -c -std=c++11 -Wall ai.cpp
	g++ -c -std=c++11 -Wall map.cpp
	g++ -c -std=c++11 -Wall main.cpp
	-g++ ai.o map.o main.o -o main
	echo "Running..."
	-./main
clean: main
	echo "Cleaning..."
	-rm main
	-rm ai.o
	-rm map.o
	-rm main.o