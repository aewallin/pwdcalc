cmake_minimum_required(VERSION 2.6)
PROJECT(pwdcalc)


if (CMAKE_BUILD_TOOL MATCHES "make")
    add_definitions(-Wall -fno-math-errno)
endif (CMAKE_BUILD_TOOL MATCHES "make")
#     -Werror 

# this figures out the Python include directories and adds them to the
# header file search path
execute_process(
    COMMAND python-config --includes
    COMMAND sed -r "s/-I//g; s/ +/;/g"
    COMMAND tr -d '\n'
    OUTPUT_VARIABLE Python_Includes
)
include_directories(${Python_Includes})

find_package( Boost COMPONENTS python numpy REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS "Boost_LIB_VERSION: " ${Boost_LIB_VERSION})
    MESSAGE(STATUS "Boost_INCLUDE_DIRS are: " ${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS "Boost_PYTHON_LIBRARY is: " ${Boost_PYTHON_LIBRARY})
    MESSAGE(STATUS "boost_LIBRARY_DIRS is: " ${Boost_LIBRARY_DIRS})
    MESSAGE(STATUS "Boost_LIBRARIES is: " ${Boost_LIBRARIES})    
endif()

set(SRC_FILES
    pwdcalc.cpp
)

########################################################################
# this makes the Python module
add_library(
    pwdcalc
    MODULE
    ${SRC_FILES}
)

set_target_properties(pwdcalc PROPERTIES PREFIX "") 
target_link_libraries(pwdcalc ${Boost_LIBRARIES} ) 


find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(pwdcalc PUBLIC OpenMP::OpenMP_CXX)
endif()
