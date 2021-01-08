cmake_minimum_required(VERSION 3.13)

include(FetchContent)

FetchContent_Declare(
	yaml
	GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
	GIT_TAG yaml-cpp-0.6.3
)
FetchContent_GetProperties(yaml)
if(NOT yaml_POPULATED)
	FetchContent_Populate(yaml)
	add_subdirectory(${yaml_SOURCE_DIR} ${yaml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(build_static_lib TRUE)

FetchContent_Declare(
	easylogger
	GIT_REPOSITORY https://github.com/amrayn/easyloggingpp.git
	GIT_TAG v9.97.0
)
FetchContent_GetProperties(easylogger)
if(NOT easylogger_POPULATED)
	FetchContent_Populate(easylogger)
	add_subdirectory(${easylogger_SOURCE_DIR} ${easylogger_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG 7.1.3
)
FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
	FetchContent_Populate(fmt)
	add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


project(lab002)

#set(CMAKE_CXX_COMPILER g++-10)

set(Experiment_SOURCES ${CMAKE_SOURCE_DIR}/src/Experiment.cpp)
set(Experiment_HEADERS ${CMAKE_SOURCE_DIR}/include/Experiment.h)
add_library(lib_Experiment ${Experiment_SOURCES} ${Experiment_HEADERS})
set_target_properties(lib_Experiment PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE)
target_include_directories(lib_Experiment PUBLIC ${CMAKE_SOURCE_DIR}/include ${easylogger_SOURCE_DIR}/src)
target_link_libraries(lib_Experiment PUBLIC easyloggingpp)

set(Report_SOURCES ${CMAKE_SOURCE_DIR}/src/Report.cpp)
set(Report_HEADERS ${CMAKE_SOURCE_DIR}/include/Report.h)
add_library(lib_Report ${Report_SOURCES} ${Report_HEADERS})
set_target_properties(lib_Report PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE)
#target_include_directories(lib_Report PUBLIC ${CMAKE_SOURCE_DIR}/include ${easylogger_SOURCE_DIR}/src)
target_link_libraries(lib_Report PUBLIC lib_Experiment yaml-cpp fmt)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${easylogger_SOURCE_DIR}/src)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC lib_Report)
