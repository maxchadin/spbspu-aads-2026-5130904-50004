CXX = g++
CXXFLAGS = -Wall -Wextra -Wold-style-cast -std=c++14 -O2
SOURCES = main.cpp Player.cpp Collection.cpp Squad.cpp Manager.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = fc26_manager

TEST_SOURCES = test-main.cpp test-collection.cpp test-squad.cpp Player.cpp Collection.cpp Squad.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_EXECUTABLE = test_fc26

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE)
