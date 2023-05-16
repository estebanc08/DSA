CXX= g++
CXXFLAGS= -std=c++20 -g

.PHONY: build
build: a.out run

a.out: main.cpp *.hpp
	@$(CXX) $(CXXFLAGS) -o a.out $^

.PHONY: run
run: a.out
	./a.out

.PHONY: clean
clean:
	@rm -f a.out
