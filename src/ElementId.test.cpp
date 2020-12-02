#include <catch.hpp>

#include <ElementId.hpp>

TEST_CASE("test Element Id", "[base]")
{
	ElementId id1;
	ElementId id2;

	REQUIRE(id1.is_empty());
	REQUIRE(id2.is_empty());

	REQUIRE(id1 == id2);

	SECTION("Two ids are not same.")
	{
		id1.generate();
		id2.generate();

		REQUIRE(id1 != id2);
	}

	SECTION("Compare and assgn value.")
	{
		id1.generate();
		id2.generate();

		REQUIRE(id1 != id2);

		ElementId id3(id2);
		REQUIRE(id2 == id2);

		id1.generate();
		REQUIRE(id1 != id2);

		id1 = id2;
		REQUIRE(id1 == id2);
	}
}

TEST_CASE("test factory of element id", "[base]")
{
	ElementIdFactory *factory = ElementIdFactory::get_instance();

	REQUIRE(factory != NULL);

	SECTION("Generate a element id.")
	{
		ElementId id1 = factory->generate();
		ElementId id2 = factory->generate();

		REQUIRE(!id1.is_empty());
		REQUIRE(!id2.is_empty());
		REQUIRE(id1 != id2);
	}
}
