#include <catch.hpp>

#include <stdlib.h>
#include <unistd.h>

#include <Output.hpp>

TEST_CASE("test output about graphviz", "[app]")
{
	Element elm0("elm0");	// not in model.
	Element elm1("elm1");
	Element elm2("elm2");
	Element elm3("elm3");

	Relation rlt0("rlt0");	// not in model.
	Relation rlt1("rlt1");
	Relation rlt2("rlt2");

	Model model("model");

	model.add_elm(&elm1);
	model.add_elm(&elm2);
	model.add_elm(&elm3);

	rlt1.relate( {
		    &elm1, &elm2}
	);
	rlt2.relate( {
		    &elm2, &elm3}
	);

	model.add_elm(&elm1);
	model.add_elm(&elm2);
	model.add_elm(&elm3);

	model.add_elm(&rlt1);
	model.add_elm(&rlt2);

	SECTION("init and export") {
		OutputGraphviz output;
		char path[] = "/tmp/XXXXXX.txt";
		int fd = mkstemps(path, 4);
		REQUIRE(fd != -1);
		close(fd);

		output.set_output_filepath(path);
		REQUIRE(output.output(model));
	}

}
