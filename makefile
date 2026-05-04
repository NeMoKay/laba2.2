CXX = clang++

CXXFLAGS = -std=c++17 -Iinclude -I/opt/homebrew/include
LDLIBS   = -L/opt/homebrew/lib -lgtest -lgtest_main -lpthread

SRC_MAIN = src/main.cpp
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



web_interface: interface_html/web_interface.cpp
	g++ -std=c++11 -o web_interface interface_html/web_interface.cpp -I..
	
clean_web:
	rm -f web_interface

run_server: web_interface
	cd interface_html && python3 server.py