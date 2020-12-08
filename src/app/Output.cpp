#include <Output.hpp>

#include <graphviz/gvc.h>

OutputGraphviz::OutputGraphviz()
{
}

OutputGraphviz::~OutputGraphviz()
{
}

void OutputGraphviz::set_output_filepath(const std::string path)
{
	output_file_path = path;
}

bool OutputGraphviz::output(const Model & model)
{
	Agraph_t *g;
    Agnode_t *n, *m;
    Agedge_t *e;
    GVC_t *gvc;

    /* 1. set up a graphviz context */
    gvc = gvContext();

    /* parse command line args - minimally argv[0] sets layout engine */
    //gvParseArgs(gvc, argc, argv);

    /* Create a simple digraph */
    g = agopen("g", Agdirected, 0);
    n = agnode(g, "n", 1);
    m = agnode(g, "m", 1);
    e = agedge(g, n, m, 0, 1);

    /* Set an attribute - in this case one that affects the visible rendering */
    agsafeset(n, "color", "red", "");

    /* Compute a layout using layout engine from command line args */
    gvLayoutJobs(gvc, g);

    /* Write the graph according to -T and -o options */
    gvRenderJobs(gvc, g);

    /* Free layout data */
    gvFreeLayout(gvc, g);

    /* Free graph structures */
    agclose(g);

    /* close output file, free context */
	gvFreeContext(gvc);
    
    return true;
}

typedef struct {
	Agrec_t hdr;
	int x, y, z;
} mydata;
