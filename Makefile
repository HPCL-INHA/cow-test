CXX=g++

all: cow-test.o
	$(CXX) -o cow-test.out cow-test.o

cow-test.o: src/cow-test.cpp
	$(CXX) -c src/cow-test.cpp

clean:
	rm -rf *.out *.o