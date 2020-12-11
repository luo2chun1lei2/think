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
		ParseCommandLineWithProperties::Properties propties;
	
    	REQUIRE(parse.parse("XXX a=1 b=2"));
    	REQUIRE(parse.get_start() == "XXX");
    	REQUIRE(parse.get_properties().size() == 2);
    	REQUIRE(parse.get_properties()[0].first == "a");
    	REQUIRE(parse.get_properties()[0].second == "1");
    	REQUIRE(parse.get_properties()[1].first == "b");
    	REQUIRE(parse.get_properties()[1].second == "2");
    }
}
