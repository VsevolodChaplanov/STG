#ifndef __FLOW_FIELD__
#define __FLOW_FIELD__

#include <vector>
#include "STG_VelocityVector.hpp"
#include "STG_FiniteElementsMesh.hpp"
#include "STG_Generator.hpp"
#include <iostream>
#include <fstream>

//Сделать статичтику отдельно

namespace STG
{
	class FlowField
	{
	private:
		// Velocty vectors
		std::vector<STG::IVelocity*> Field;
		// Finite elements mesh
		const FEM::FiniteElementsMesh* fem_mesh;
		// Random number generator
		const STG::IGenerator* engine;

	public:
		FlowField(const FEM::FiniteElementsMesh* mesh, const STG::IGenerator* engine);
		// Generate flow field along fem mesh
		void generate_FlowField();
		// Add a constant component to all vectors
		void add_const_component(double v_av, size_t i_comp);
		// Save field to file in .vtk format
		void save_flow_field(const std::string& save_filename) const;
		~FlowField();
	};
} // namespace STG


#endif