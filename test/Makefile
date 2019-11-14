CXXFLAGS=-std=c++11 -Wall -Wextra -O0 -g -I . -I ../include -pthread

UNIT_TESTS = bin/unit_tests
test: $(UNIT_TESTS)
	$(UNIT_TESTS) --gtest_output="xml:TestResults.xml"

obj/gtest.o: gtest/gtest-all.cc
	@mkdir -p obj
	g++ $^ $(CXXFLAGS) -c -o $@

obj/main.o: main.cpp
	g++ $^ $(CXXFLAGS) -c -o $@

obj/MockingTest.o: MockingTest.cpp ../include/cpp_mock.h
	g++ MockingTest.cpp $(CXXFLAGS) -c -o $@

$(UNIT_TESTS): obj/gtest.o obj/main.o obj/MockingTest.o
	@mkdir -p bin
	g++ $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf obj/*.o
	rm -f $(UNIT_TESTS)
