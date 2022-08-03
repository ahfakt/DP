cmake_minimum_required(VERSION 3.14.0)
project(DP VERSION 0.7 DESCRIPTION "Design Patterns Template Library")

set(CMAKE_CXX_STANDARD 20)


set(INC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_LIST
		${INC_ROOT}/${PROJECT_NAME}/Builder.hpp
		${INC_ROOT}/${PROJECT_NAME}/CreateInfo.hpp
		${INC_ROOT}/${PROJECT_NAME}/Factory.hpp)
set(SRC_LIST
		${SRC_ROOT}/Factory.tpp)

add_library(${PROJECT_NAME}OBJ INTERFACE)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}OBJ INTERFACE include)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_sources(${PROJECT_NAME}OBJ INTERFACE ${INC_LIST} PRIVATE ${SRC_LIST})
target_sources(${PROJECT_NAME} INTERFACE ${INC_LIST} PRIVATE ${SRC_LIST})


if (CMAKE_BUILD_TYPE MATCHES Debug)
	enable_testing()
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test ${CMAKE_CURRENT_BINARY_DIR}/Testing)
endif()


if ((DEFINED DOC_ROOT) AND (NOT ${DOC_ROOT} STREQUAL ""))
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
		set(DOXYGEN_IN_CFG ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg)
		set(DOXYGEN_OUTPUT_DIR ${DOC_ROOT}/${PROJECT_NAME})
		set(DOXYGEN_CFG ${DOC_ROOT}/.doxy/${PROJECT_NAME}.cfg)

		configure_file(${DOXYGEN_IN_CFG} ${DOXYGEN_CFG} @ONLY)
		message("Doxygen configuration ${DOXYGEN_CFG} generated.")

		add_custom_target(${PROJECT_NAME}Doc
				COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CFG}
				WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR}
				COMMENT "Generating ${PROJECT_NAME} documentation with Doxygen"
				VERBATIM)
	else (DOXYGEN_FOUND)
		message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif()
