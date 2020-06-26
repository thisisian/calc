CXX=g++
CPPFLAGS=-g -std=c++17 -Wall -Wpedantic

SRCDIR=./src
SRCS=$(SRCDIR)/exception.cpp $(SRCDIR)/lexer.cpp $(SRCDIR)/ast.cpp $(SRCDIR)/parser.cpp
INCLS=$(SRCDIR)/exception.hpp $(SRCDIR)/lexer.hpp $(SRCDIR)/ast.hpp $(SRCDIR)/parser.hpp
MAIN=./main.cpp

TARGET=calc

TESTMAIN=./test/testmain.cpp
TESTTARGET=./test/testmain


calc: $(SRCS) $(INCLS) $(MAIN)
	$(CXX) -o $(TARGET) $(CPPFLAGS) $(SRCS) $(MAIN)


test: $(SRCS) $(INCLS) $(TESTMAIN)
	$(CXX) -o $(TESTTARGET) $(CPPFLAGS) $(SRCS) $(TESTMAIN)
	./test/testmain

.PHONY: test
