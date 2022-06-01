set(HEADERS include/STG_Vector.hpp
	include/STG_Generator.hpp
	include/STG_FiniteElementsMesh.hpp
	include/STG_VelocityVector.hpp
	include/STG_FlowField.hpp
	include/STG_CompMatrix.hpp
	include/Math.hpp
	include/FEM_Parser.hpp
)
set(SRC stg/STG_Vector.cpp
	stg/STG_Generator.cpp
	stg/STG_FiniteElementsMesh.cpp
	stg/STG_VelocityVector.cpp
	stg/STG_FlowField.cpp
	stg/STG_CompMatrix.cpp
	stg/Math.cpp
	stg/FEM_Parser.cpp
)

set(STG_lib STG_ex)

find_package(Boost REQUIRED)

add_library(${STG_lib} SHARED ${SRC} ${HEADERS})
target_include_directories(${STG_lib} PRIVATE include)
target_include_directories(${STG_lib} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${STG_lib} PRIVATE ${Boost_LIBARARIES})

add_subdirectory(tests)