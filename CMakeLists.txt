cmake_minimum_required(VERSION 3.14.0)
project(DP VERSION 0.7 DESCRIPTION "Design Patterns Template Library")


set(INC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_LIST
		${INC_ROOT}/${PROJECT_NAME}/Builder.hpp
		${INC_ROOT}/${PROJECT_NAME}/CreateInfo.hpp
		${INC_ROOT}/${PROJECT_NAME}/Factory.hpp)
set(SRC_LIST
		${SRC_ROOT}/${PROJECT_NAME}/Factory.tpp)


add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE inc)
target_sources(${PROJECT_NAME} INTERFACE ${INC_LIST} PRIVATE ${SRC_LIST})


if (CMAKE_BUILD_TYPE MATCHES Debug)
	enable_testing()
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test ${CMAKE_CURRENT_BINARY_DIR}/Testing)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg @ONLY)
		add_custom_target(${PROJECT_NAME}Doc
			COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
			COMMENT "Generating ${PROJECT_NAME} documentation with Doxygen"
			VERBATIM)
	endif (DOXYGEN_FOUND)
endif()
