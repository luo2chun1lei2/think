#include <catch.hpp>

#include <Model.hpp>

TEST_CASE("test model", "[base]")
{
	Element elm0("elm0");		// not in model.
	Element elm1("elm1");
	Element elm2("elm2");
	Element elm3("elm3");

	Relation rlt0("rlt0");		// not in model.
	Relation rlt1("rlt1");
	Relation rlt2("rlt2");

	Model model("model");

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

	SECTION("Add relations and find.")
	{
		rlt1.relate(
					   {
					   &elm1, &elm2}
		);
		rlt2.relate(
					   {
					   &elm2, &elm3}
		);

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

		SECTION("Find one element.")
		{
			REQUIRE(model.find_elm(elm1.get_id()) == &elm1);
			REQUIRE(model.find_elm(rlt2.get_id()) == &rlt2);
			REQUIRE(model.find_elm(elm0.get_id()) == nullptr);
		}
		
		SECTION("Find one element by name.")
		{
			std::vector<Element *> found;
			
			found = model.find_elm("elm1");
			REQUIRE( found.size() == 1);
			REQUIRE( found[0] == &elm1);
			
			found = model.find_elm("rlt2");
			REQUIRE( found.size() == 1);
			REQUIRE( found[0] == &rlt2);
			
			found = model.find_elm("xxx");
			REQUIRE( found.size() == 0);
		}

		SECTION("Find a element by relation.")
		{
			std::vector <Element *> found;

			// 根据 元素的名字，以及它的关系的名字，找到涉及到的元素。
			found = model.find_elm_by_rlt("elm1", "rlt1");
			REQUIRE(found.size() == 1);
			REQUIRE(found[0] == &elm2);

			found = model.find_elm_by_rlt("elm2", "rlt2");
			REQUIRE(found.size() == 1);
			REQUIRE(found[0] == &elm3);
		}
	}
}
