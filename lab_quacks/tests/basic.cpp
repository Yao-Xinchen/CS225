#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../stack.h"
#include "../queue.h"
#include <iostream>
#include <sstream>
#include <string>

#include "../exercises.h"
#include "../quackfun.h"

using std::to_string;
using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using cs225::stack;
using cs225::queue;
 
TEST_CASE("RecursionExercises::sumDigits"){
	SECTION("Base cases work") {
		REQUIRE(RecursionExercises::sumDigits(1) == 1);
		REQUIRE(RecursionExercises::sumDigits(0) == 0);
	}
	SECTION("Multiple digits sum correctly") {
		REQUIRE(RecursionExercises::sumDigits(243) == 9);
		REQUIRE(RecursionExercises::sumDigits(49) == 13);
	}
} 
 
TEST_CASE("RecursionExercises::triangle"){
	SECTION("Base cases work") {
		REQUIRE(RecursionExercises::triangle(0) == 0);
	}
	SECTION("Recursive cases work") {
		REQUIRE(RecursionExercises::triangle(3) == 6);
		REQUIRE(RecursionExercises::triangle(6) == 21);
		REQUIRE(RecursionExercises::triangle(8) == 36);
	}
}
 
TEST_CASE("SUM"){
	stack<int> s;
	for (int i = 0; i <= 16; i++)
		s.push(i);
	stack<int> s2 = s;
	SECTION("Sum is correct") {
		REQUIRE(QuackFun::sum(s) == 136);
	}
	SECTION("stack is unchanged") {
		REQUIRE(s == s2);
	}
 
	stack<double> s3;
    for (int i = 0; i <= 10; i++)
        s3.push(2.1+4.5*i);
    stack<double> s4 = s3;

    stack<double>::_ctor_count = 0;
    double sumFloat = QuackFun::sum<double>(s3);

    SECTION("Float sum is correct") {
    	if (sumFloat > 270.61 || sumFloat < 270.59)
    		FAIL("Expected sum = 270.6; Actual = " + to_string(sumFloat));
    }
    SECTION("stack is unchanged"){
    	REQUIRE(s3 == s4);
    }
    SECTION("Did not make any additional stack objects"){
    	REQUIRE(stack<double>::_ctor_count == 0);
    }
}

TEST_CASE("scramble 17") {
	queue<int> q;
	for (int i = 1; i <= 17; i++)
		q.push(i);

	QuackFun::scramble<int>(q);

	stringstream scrambled_output;
	while (!q.empty())
	{
		scrambled_output << q.front() << ' ';
		q.pop();
	}
	string scrambled = scrambled_output.str();
	string expected = "1 3 2 4 5 6 10 9 8 7 11 12 13 14 15 17 16 ";

	cout << "Scrambled queue: " << scrambled << endl;
	cout << "Expected:        " << expected << endl;

	if (scrambled != expected)
		FAIL("See output above");
}

TEST_CASE("scramble 9") {
    queue<int> q;
    for (int i = 4; i <= 12; i++)
        q.push(i);

    QuackFun::scramble<int>(q);

    stringstream scrambled_output;
    while (!q.empty())
    {
        scrambled_output << q.front() << ' ';
        q.pop();
    }
    string scrambled = scrambled_output.str();
    string expected = "4 6 5 7 8 9 12 11 10 ";

    cout << "Scrambled queue: " << scrambled << endl;
    cout << "Expected:        " << expected << endl;

    if (scrambled != expected)
        FAIL("See output above");
}

TEST_CASE("QuackFun::verifySame results") {
	// Test different
	{
		stack<int> s;
		queue<int> q;
		for (int i = 2; i < 7; i++)
		{
			s.push(i);
			q.push(i);
		}
		s.push(4);
		q.push(6);
		for (int i = 7; i < 10; i++)
		{
			s.push(i);
			q.push(i);
		}
		stack<int> sb = s;
		queue<int> qb = q;

		SECTION("Result for different stack and queue is false") {
			bool result = QuackFun::verifySame(s, q);
			REQUIRE(result == false);
		}
		SECTION("Data structures are unmodified") {
			if (s != sb)
				FAIL("stack was modified");
			else if (q != qb)
				FAIL("Queue was modified");
		}	
	}

	// Test the same
	{
		stack<int> s;
		queue<int> q;
		for (int i = 2; i < 7; i++)
		{
			s.push(i);
			q.push(i);
		}
		stack<int> sb = s;
		queue<int> qb = q;
 
		SECTION("Result for same stack and queue is true") {
			bool result = QuackFun::verifySame(s, q);
			REQUIRE(result == true);
		}
		SECTION("Data structures are unmodified") {
			if (s != sb)
				FAIL("stack was modified");
			else if (q != qb)
				FAIL("Queue was modified");
		}
	}
}
 
TEST_CASE ("QuackFun::verifySame structures unmodified (EXTRA CREDIT)") {
	// Test different
    {
        stack<int> s;
        queue<int> q;
        for (int i = 2; i < 7; i++)
        {
            s.push(i);
            q.push(i);
        }
        s.push(4);
        q.push(6);
        for (int i = 7; i < 10; i++)
        {
            s.push(i);
            q.push(i);
        }
        stack<int> sb = s;
        queue<int> qb = q;
 
        stack<int>::_ctor_count = 0;
        queue<int>::_ctor_count = 0;
        SECTION("Result for different stack and queue is different") {
			bool result = QuackFun::verifySame(s, q);
			REQUIRE(result == false);
		}
		SECTION("Data structures are unmodified") {
			if (s != sb)
				FAIL("stack was modified");
			else if (q != qb)
				FAIL("Queue was modified");
		}
		SECTION("No new stacks or queues are made") {
			if (stack<int>::_ctor_count != 0)
            	FAIL("You may not make a second stack object");
        	if (queue<int>::_ctor_count != 0)
            	FAIL("You may not make a second queue object");
		}
    }
 
    // Test the same
    {
        stack<int> s;
        queue<int> q;
        for (int i = 2; i < 7; i++)
        {
            s.push(i);
            q.push(i);
        }
        stack<int> sb = s;
        queue<int> qb = q;
 
        stack<int>::_ctor_count = 0;
        queue<int>::_ctor_count = 0;
        SECTION("Result for same stack and queue is the same") {
			bool result = QuackFun::verifySame(s, q);
			REQUIRE(result == true);
		}
		SECTION("Data structures are unmodified") {
			if (s != sb)
				FAIL("stack was modified");
			else if (q != qb)
				FAIL("Queue was modified");
		}
		SECTION("No new stacks or queues are made") {
			if (stack<int>::_ctor_count != 0)
            	FAIL("You may not make a second stack object");
        	if (queue<int>::_ctor_count != 0)
            	FAIL("You may not make a second queue object");
		}
    }
}
