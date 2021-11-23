#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
    "DEPOSIT Ivanov 100\n"
 "INCOME 5\n"
 "BALANCE Ivanov\n"
 "TRANSFER Ivanov Petrov 50\n"
 "WITHDRAW Petrov 100\n"
 "BALANCE Petrov\n"
 "BALANCE Sidorov"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() ==
    "105\n"
    "-50\n"
    "ERROR\n"
    );
}

TEST_CASE("one block", ""){
    std::stringstream input(
            "BALANCE Ivanov\n"
 "BALANCE Petrov\n"
 "DEPOSIT Ivanov 100\n"
 "BALANCE Ivanov\n"
 "BALANCE Petrov\n"
 "DEPOSIT Petrov 150\n"
 "BALANCE Petrov\n"
 "DEPOSIT Ivanov 10\n"
 "DEPOSIT Petrov 15\n"
 "BALANCE Ivanov\n"
 "BALANCE Petrov\n"
 "DEPOSIT Ivanov 46\n"
 "BALANCE Ivanov\n"
 "BALANCE Petrov\n"
 "DEPOSIT Petrov 14\n"
 "BALANCE Ivanov\n"
 "BALANCE Petrov"
            );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
    "ERROR\n"
 "ERROR\n"
 "100\n"
 "ERROR\n"
 "150\n"
 "110\n"
 "165\n"
 "156\n"
 "165\n"
 "156\n"
 "179\n"
    );
}

TEST_CASE("test 3", ""){
    std::stringstream input(
            "BALANCE a\n"
 "BALANCE b\n"
 "DEPOSIT a 100\n"
 "BALANCE a\n"
 "BALANCE b\n"
 "WITHDRAW a 20\n"
 "BALANCE a\n"
 "BALANCE b\n"
 "WITHDRAW b 78\n"
 "BALANCE a\n"
 "BALANCE b\n"
 "WITHDRAW a 784\n"
 "BALANCE a\n"
 "BALANCE b\n"
 "DEPOSIT b 849\n"
 "BALANCE a\n"
 "BALANCE b"
            );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
 "ERROR\n"
 "ERROR\n"
 "100\n"
 "ERROR\n"
 "80\n"
 "ERROR\n"
 "80\n"
 "-78\n"
 "-704\n"
 "-78\n"
 "-704\n"
 "771\n"
    );
}
