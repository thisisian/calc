#include <iostream>

#include "../src/parser.hpp"
#include "../src/exception.hpp"

static int passed_count = 0;
static int failed_count = 0;

void assert_parse_equals(std::string input, long double expected) {
    std::cout << input << ": ";
    long double actual;
    try {
        actual = Parser::parse_and_eval(input);
    } catch (ParserException &e) {
        std::cout << "TEST FAILED! Got exception: " << e.what() << std::endl;
        ++failed_count;
        return;
    }
    if (expected == actual) {
        std::cout << "OK!" << std::endl;
        ++passed_count;
        return;
    }

    std::cout << "TEST FAILED! Expected " << expected
                << " but got " << actual << std::endl;
    ++failed_count;
}

void assert_parse_fails(std::string input) {
    std::cout << input << " (testing failure): ";
    long double actual;
    try {
        actual = Parser::parse_and_eval(input);
    } catch (ParserException &e) {
        std::cout << "OK! Got exception: " << e.what() << std::endl;
        ++passed_count;
        return;
    } catch (std::exception &e) {
        std::cout <<" TEST FAILED! Unexpected exception: " << e.what() << std::endl;
        ++failed_count;
        return;
    }
    std::cout << "TEST FAILED! Expected exception but got " << actual << std::endl;
    ++failed_count;
    return;
}

int main(void) {
    assert_parse_equals("1", 1);
    assert_parse_equals("1+1", 2);
    assert_parse_equals(" ( 1  + 1  ) ", 2);
    assert_parse_equals("5-1-1", 3);
    assert_parse_equals("2*3+4", 10);
    assert_parse_equals("2+3*4", 14);
    assert_parse_equals("10-2-2-3*2", 0);
    assert_parse_equals("3 - ( 1- -1 - 1 )", 2);
    assert_parse_equals("3*5/2", 7.5);
    assert_parse_equals("3*5/-2", -7.5);
    assert_parse_equals("3*5/-2", -7.5);
    assert_parse_equals("((3*(9-2-1)*((3-2)-(3-5))))", 54);
    assert_parse_equals("(100-2)/2*5", 245);
    assert_parse_equals("2.5", 2.5);
    assert_parse_equals("2.5/2", 1.25);
    assert_parse_equals("10 * 9", 90);

    assert_parse_fails("");
    assert_parse_fails("(3*+9)");
    assert_parse_fails("3*");
    assert_parse_fails("((3)");
    assert_parse_fails("(3))");
    assert_parse_fails("3 3");
    assert_parse_fails("333)");
    assert_parse_fails(")");
    assert_parse_fails("gg+9");
    assert_parse_fails("3.2.3");
    assert_parse_fails("3gg");

    std::cout << "\n" << passed_count << " tests passed.\n";
    if (failed_count != 0) {
        std::cout << failed_count << " tests failed.\n";
    } else {
        std::cout << "All tests passed!\n";
    }
    return 0;
}
