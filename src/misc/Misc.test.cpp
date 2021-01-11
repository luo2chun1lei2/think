#include <catch.hpp>

#include <Misc.hpp>

using namespace std;

TEST_CASE("test log", "[misc]") {
    LOGE("error message.\n");
    LOGI("information message.\n");
}

TEST_CASE("test combine line", "[misc]") {
	CombineLine clines;
	SECTION("one line") {
		string all;
		
    	REQUIRE(clines.add(" this is only one line", all));
    	REQUIRE(all == " this is only one line");
    	
    	REQUIRE(clines.add(" this is only 1 line \\ ", all));	// 注意，后面有一个空格。
    	REQUIRE(all == " this is only 1 line \\ ");
    }
    
    SECTION("two lines") {
		string all;
		
    	REQUIRE(!clines.add("this is one line. \\", all));
    	REQUIRE(clines.add("this is two line.", all));
    	REQUIRE(all == "this is one line. this is two line.");
    	
    	// 之后再有一个单独行。
    	REQUIRE(clines.add(" this is only one line", all));
    	REQUIRE(all == " this is only one line");
    }
    
    SECTION("three lines") {
		string all;
		
    	REQUIRE(!clines.add("this is one line. \\", all));
    	REQUIRE(!clines.add("this is two line. \\", all));
    	REQUIRE(clines.add("this is three line.", all));
    	REQUIRE(all == "this is one line. this is two line. this is three line.");
    	
    	// 之后再有一个单独行。
    	REQUIRE(clines.add(" this is only one line", all));
    	REQUIRE(all == " this is only one line");
    }
}

TEST_CASE("parse command line with properties", "[misc]") {
	ParseCommandLineWithProperties parse;
	SECTION("one line") {
	
		REQUIRE(!parse.parse("XXX a=1 b="));
		REQUIRE(!parse.parse("XXX a= b=2"));
		REQUIRE(!parse.parse("a=1 b=2"));
		REQUIRE(!parse.parse("xxx a b=2"));
		
		REQUIRE(parse.parse("xxx"));
		REQUIRE(parse.get_start() == "xxx");

		REQUIRE(parse.parse("x_x_x"));
		REQUIRE(parse.get_start() == "x_x_x");

		REQUIRE(parse.parse("\"x x x\""));
		REQUIRE(parse.get_start() == "\"x x x\"");
		
    	REQUIRE(parse.parse("XXX a=1 b=2"));
    	REQUIRE(parse.get_start() == "XXX");
    	REQUIRE(parse.get_properties().size() == 2);
    	REQUIRE(parse.get_properties()[0].first == "a");
    	REQUIRE(parse.get_properties()[0].second == "1");
    	REQUIRE(parse.get_properties()[1].first == "b");
    	REQUIRE(parse.get_properties()[1].second == "2");


		REQUIRE(parse.parse("XXX a_123=1.a_b_c"));
    	REQUIRE(parse.get_start() == "XXX");
    	REQUIRE(parse.get_properties().size() == 1);
    	REQUIRE(parse.get_properties()[0].first == "a_123");
    	REQUIRE(parse.get_properties()[0].second == "1.a_b_c");

    	
    	REQUIRE(parse.parse("\"X X X\" a=1 b=2"));
    	REQUIRE(parse.get_start() == "\"X X X\"");
    	
    	REQUIRE(parse.parse("XXX \"a a\"=1 b=\"2 3 2\""));
    	REQUIRE(parse.get_start() == "XXX");
    	REQUIRE(parse.get_properties().size() == 2);
    	REQUIRE(parse.get_properties()[0].first == "\"a a\"");
    	REQUIRE(parse.get_properties()[0].second == "1");
    	REQUIRE(parse.get_properties()[1].first == "b");
    	REQUIRE(parse.get_properties()[1].second == "\"2 3 2\"");
    	
    }
}

TEST_CASE("parse expr", "[misc]") {
	ParseExpr parse;
	SECTION("relation") {

		ParseExpr::Path path;
	
		REQUIRE(parse.parse("1.2.3.4"));
		path = parse.get_path();
		REQUIRE(path.size() == 4);
		REQUIRE(path[0] == "1");
		REQUIRE(path[1] == "2");
		REQUIRE(path[2] == "3");
		REQUIRE(path[3] == "4");

		REQUIRE(parse.parse("\"1 1\".2.3.\"4 4\""));
		path = parse.get_path();
		REQUIRE(path.size() == 4);
		REQUIRE(path[0] == "\"1 1\"");
		REQUIRE(path[1] == "2");
		REQUIRE(path[2] == "3");
		REQUIRE(path[3] == "\"4 4\"");
    }

	SECTION("logic") {
		//REQUIRE(parse.parse("1 = 2"));
		//REQUIRE(parse.parse("a.1 = b.2"));
    }

	SECTION("algo") {
		//REQUIRE(parse.parse("1 + 2"));
		//REQUIRE(parse.parse("a.1 + b.2"));
    }
}

