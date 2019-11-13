CXXFLAGS=-std=c++11 -Wall -Wextra -O0 -g -I . -I ../include -pthread
SRC= \
	main.cpp \
	MockingTest.cpp \

UNIT_TESTS = bin/unit_tests
test: $(UNIT_TESTS)
	$(UNIT_TESTS) --gtest_output="xml:TestResults.xml"

obj/gtest.o: gtest/gtest-all.cc
	@mkdir -p obj
	g++ $? $(CXXFLAGS) -c -o $@

obj/main.o: main.cpp
	g++ $? $(CXXFLAGS) -c -o $@

obj/MockingTest.o: MockingTest.cpp
	g++ $? $(CXXFLAGS) -c -o $@

$(UNIT_TESTS): obj/gtest.o obj/main.o obj/MockingTest.o
	@mkdir -p bin
	g++ $? $(CXXFLAGS) -o $@
