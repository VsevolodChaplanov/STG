set(HEADERS TestsHeader.hpp)
set(SRC main.cpp 
	STG_Vector_tests.cpp
	STG_Velocity_tests.cpp
	STG_FlowField_tests.cpp
	STG_Generator_tests.cpp
	FEM_FinElemMesh_tests.cpp
	Math_tests.cpp)

set(STG_tests STG_unit_tests)

add_executable(${STG_tests} ${SRC} ${HEADERS})

target_link_libraries(${STG_tests} PRIVATE ${STG_lib} ${CATCH2_FRAMEWORK})
target_include_directories(${STG_tests} PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/include)

