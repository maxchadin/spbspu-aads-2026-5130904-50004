CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Wold-style-cast

OBJS = main.o Player.o Collection.o Squad.o Manager.o
TEST_SQUAD_OBJS = test-squad.o test-main.o Squad.o Player.o
TEST_COLL_OBJS = test-collection.o test-main.o Collection.o Player.o

all: manager test_squad test_collection

manager: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_squad: $(TEST_SQUAD_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_collection: $(TEST_COLL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o manager test_squad test_collection

.PHONY: all clean
