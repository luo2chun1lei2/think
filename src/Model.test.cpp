#include <catch.hpp>

#include <Model.hpp>

TEST_CASE("test model", "[base]")
{
	Element elm0;	// not in model.
	Element elm1;
	Element elm2;
	Element elm3;

	Relation rlt0;	// not in model.
	Relation rlt1;
	Relation rlt2;
	
	Model model;
	
	SECTION("Add elements.")
	{
		model.add_elm(&elm1);
		model.add_elm(&elm2);
		model.add_elm(&elm3);
		
		REQUIRE(model.get_elm(0) == &elm1);
		REQUIRE(model.get_elm(1) == &elm2);
		REQUIRE(model.get_elm(2) == &elm3);
		REQUIRE(model.get_elm(3) == nullptr);
	}

	SECTION("Add relations.")
	{
		rlt1.relate({&elm1, &elm2});
		rlt2.relate({&elm2, &elm3});
		
		model.add_elm(&elm1);
		model.add_elm(&elm2);
		model.add_elm(&elm3);
		
		model.add_elm(&rlt1);
		model.add_elm(&rlt2);
		
		REQUIRE(model.get_elm(0) == &elm1);
		REQUIRE(model.get_elm(1) == &elm2);
		REQUIRE(model.get_elm(2) == &elm3);
		REQUIRE(model.get_elm(3) == &rlt1);
		REQUIRE(model.get_elm(4) == &rlt2);
		REQUIRE(model.get_elm(5) == nullptr);
		
		SECTION("Find one element.") {
			REQUIRE(model.find_elm(elm1.get_id()) == &elm1);
			REQUIRE(model.find_elm(rlt2.get_id()) == &rlt2);
			REQUIRE(model.find_elm(elm0.get_id()) == nullptr);
		}
		
		SECTION("Find a element by relation.") {
		}
	}
}
