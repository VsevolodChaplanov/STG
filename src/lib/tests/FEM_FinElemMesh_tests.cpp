#include "TestsHeader.hpp"

TEST_CASE( "Finite elements mesh parser", "[ParserVTK][Parser]" )
{
	FEM::VtkFEMParser test_vtk("./test_resources/Rect.1.1mesh.1.vtk");

	FEM::FiniteElementsMesh test_mesh = test_vtk.load_mesh();

	REQUIRE( test_mesh.get_vertices_number() == 98 );
	REQUIRE( test_mesh.get_elements_number() == 198 );
	REQUIRE( test_mesh.get_cell_types().size() == 198);

	std::vector<double> vertices_test = test_mesh.get_vertices();
	std::vector<std::vector<size_t>> cells_test = test_mesh.get_cells();
	std::vector<size_t> cell_types_test = test_mesh.get_cell_types();

	// -------------- Vertices data check -------------- // 
			// First vertice
	for (size_t i = 0; i < 3; i++)
	{
		CHECK( vertices_test[i] == 0.0 );
	}
	
	// Random vertice from the centre
	CHECK( vertices_test[177] ==  0.31331768157997741);
	CHECK( vertices_test[178] ==  0.75237107335505982);
	CHECK( vertices_test[179] ==  0.0);

	// Last vertice
	CHECK( vertices_test[98 * 3 - 1] == 0.0);
	CHECK( vertices_test[98 * 3 - 2] == 0.8253550026152658);
	CHECK( vertices_test[98 * 3 - 3] == 0.7489644266062752);
	// -------------- Vertices data check -------------- // 

	// -------------- Cells data check -------------- // 
	// Nodes of the rectangle
	REQUIRE( cells_test[0].size() == 1);
	CHECK( cells_test[0][0] == 0 );
	// Edges of the rectangle
	REQUIRE( cells_test[4].size() == 2);
	CHECK( cells_test[4][0] == 0 );
	CHECK( cells_test[4][1] == 4 );
	// Internal triangles
	REQUIRE( cells_test[37].size() == 3);
	CHECK( cells_test[36][0] == 67);
	CHECK( cells_test[36][1] == 78);
	CHECK( cells_test[36][2] == 37);
	// Last triangle
	REQUIRE( cells_test[197].size() == 3);
	CHECK( cells_test[97][0] == 6);
	CHECK( cells_test[97][1] == 36);
	CHECK( cells_test[97][2] == 5);
	// Last triangle
	REQUIRE( cells_test[197].size() == 3);
	CHECK( cells_test[197][0] == 82);
	CHECK( cells_test[197][1] == 97);
	CHECK( cells_test[197][2] == 60);
	// -------------- Cells data check -------------- // 

	// -------------- Cell types data check -------------- // 

	// All cell types check
	for (std::vector<size_t>::iterator it = cell_types_test.begin(); it != cell_types_test.begin() + 4; it++)
	{
		CHECK( *it == 1 );
	}
	for (std::vector<size_t>::iterator it = cell_types_test.begin() + 4; it != cell_types_test.begin() + 36; it++)
	{
		CHECK( *it == 3 );
	}
	for (std::vector<size_t>::iterator it = cell_types_test.begin() + 36; it != cell_types_test.end(); it++)
	{
		CHECK( *it == 5 );
	}
	// -------------- Cell types data check -------------- // 
}

TEST_CASE( "Save as vtk format tests", "[Savevtk]" )
{
	FEM::VtkFEMParser test_vtk("./test_resources/Rect.1.1mesh.1.vtk");
	FEM::FiniteElementsMesh test_mesh = test_vtk.load_mesh();

	test_mesh.save_mesh_vtk("./test_resources/Rect.1.1mesh.1_test_save.vtk");
}