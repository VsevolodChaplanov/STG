#include "STG_FlowField.hpp"

STG::FlowField::FlowField(const FEM::FiniteElementsMesh* mesh
	, const STG::IGenerator* engine) : fem_mesh(mesh), engine(engine) { }

STG::FlowField::~FlowField()
{
	for (size_t i = 0; i < Field.size(); i++)
	{
		delete Field[i];
	}
}

void STG::FlowField::generate_FlowField()
{
	size_t Nvert = fem_mesh->get_vertices_number();
	Field.resize(Nvert);
	for (size_t i = 0; i < Nvert; i++)
	{
		Field[i] = new VelocitySmirnov(fem_mesh->get_vertex(i), 0);
		Field[i]->generate(engine);
	}
}

void STG::FlowField::add_const_component(double v_av, size_t i)
{
	for(STG::IVelocity* velocity : Field)
	{
		velocity->add_const_component(v_av, i);
	}
}

void STG::FlowField::save_flow_field(const std::string& save_filename) const
{
	fem_mesh->save_mesh_vtk(save_filename);

	std::ofstream file;
	file.open(save_filename, std::ios::app);

	file << std::endl;
	file << "POINT_DATA " << Field.size() << std::endl;
	file << "VECTORS " << "RandomFlowField double" << std::endl;

	for (const STG::IVelocity* velocity : Field)
	{
		std::array<double, 3> vector = velocity->get_vector().get_values();
		for (size_t j = 0; j < 3; j++)
		{
			file << vector[j] << " ";
		}
		file << std::endl;
	}

	file.close();
}
