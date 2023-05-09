CXX= g++
CXXFLAGS= -std=c++20 -g
# SFML_LIBS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: build
build: a.out run

a.out: main.cpp *.hpp
	@$(CXX) $(CXXFLAGS) -o a.out $^ $(SFML_LIBS)

.PHONY: run
run: a.out
	./a.out

.PHONY: clean
clean:
	@rm -f a.out
