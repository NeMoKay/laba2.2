CXX = clang++

CXXFLAGS = -std=c++23 -Iinclude -I/opt/homebrew/include
LDLIBS   = -L/opt/homebrew/lib -lgtest -lgtest_main -lpthread

SRC_MAIN = src/main.cpp

TEST_SRCS = $(wildcard tests/*.cpp) 

OBJ_MAIN = $(SRC_MAIN:.cpp=.o)

main: $(OBJ_MAIN)
	$(CXX) $^ -o $@ $(CXXFLAGS)
	./$@

test: $(TEST_SRCS)
	$(CXX) $^ -o test $(CXXFLAGS) $(LDLIBS)
	./test

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_MAIN) main test
	rm -f web_interface

.PHONY: main test clean run_server clean_web
