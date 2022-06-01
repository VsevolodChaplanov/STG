#include "TestsHeader.hpp"

TEST_CASE( "Generate flow field using Smrinov algorythm on coarse grid", "[Smirnov][CoarseGrid]")
{
	FEM::VtkFEMParser test_vtk("./test_resources/Rect.1.1mesh.1.vtk");
	FEM::FiniteElementsMesh test_mesh = test_vtk.load_mesh();
	STG::Generator<std::mt19937, std::normal_distribution<>> genengine(0, 1, 2134);
	STG::FlowField test_flow(&test_mesh, &genengine);
	test_flow.generate_FlowField();
	test_flow.save_flow_field("./test_resources/Rect.1.1mesh.1_flowfield.vtk");
}

TEST_CASE( "Generate flow field using Smrinov algorythm on fine grid", "[Smirnov][FineGrid]")
{
	FEM::VtkFEMParser test_vtk("./test_resources/triangle_1000.vtk");
	FEM::FiniteElementsMesh test_mesh = test_vtk.load_mesh();
	STG::Generator<std::mt19937, std::normal_distribution<>> genengine(0, 1, 2134);
	STG::FlowField test_flow(&test_mesh, &genengine);
	test_flow.generate_FlowField();
	test_flow.save_flow_field("./test_resources/triangle_1000_flowfield.vtk");
}

TEST_CASE( "Generate flow field using Smrinov algorythm on fine grid with added const z component", "[Smirnov][FineGrid]")
{
	FEM::VtkFEMParser test_vtk("./test_resources/triangle_1000.vtk");
	FEM::FiniteElementsMesh test_mesh = test_vtk.load_mesh();
	STG::Generator<std::mt19937, std::normal_distribution<>> genengine(0, 1, 2134);
	STG::FlowField test_flow(&test_mesh, &genengine);
	test_flow.generate_FlowField();
	test_flow.add_const_component(3, 2);
	test_flow.save_flow_field("./test_resources/triangle_1000_flowfield_added_z_const.vtk");
}