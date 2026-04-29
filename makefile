CXX = clang++

CXXFLAGS = -std=c++17 -Iinclude -I/opt/homebrew/include
LDLIBS   = -L/opt/homebrew/lib -lgtest -lgtest_main -lpthread

SRC_MAIN = src/main.cpp src/main_func.cpp 
SRC_TEST = tests/test.cpp

OBJ_MAIN = $(SRC_MAIN:.cpp=.o)

main: $(OBJ_MAIN)
	$(CXX) $^ -o $@ $(CXXFLAGS)
	./$@

test: $(SRC_TEST)
	$(CXX) $(SRC_TEST) -o $@ $(CXXFLAGS) $(LDLIBS)
	./$@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_MAIN) main test

.PHONY: main test clean