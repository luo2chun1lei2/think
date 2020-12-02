#include <catch.hpp>

#include <Element.hpp>

TEST_CASE("test element", "[base]")
{
	Element elm1;
	Element elm2;

	SECTION("Elements have id and are not same.")
	{
		REQUIRE(!elm2.get_id().is_empty());
		REQUIRE(!elm1.get_id().is_empty());

		REQUIRE(elm1.get_id() != elm2.get_id());
	}

/*    
    SECTION( "Add relation" ) {
    	elm1.add_relation();
    }
    */

}
