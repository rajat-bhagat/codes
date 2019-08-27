cmake_minimum_required(VERSION 2.8.9)

#to include header files
include_directories(include)

set(LIBSOURCE1 src/add/add.c)
set(LIBSOURCE2 src/sub/sub.c)

#generate the shared library
#add_library(addn SHARED ${LIBSOURCE1})
#add_library(subn SHARED ${LIBSOURCE2})
add_library(basic SHARED ${LIBSOURCE1} ${LIBSOURCE2})

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)

	set(doxygen_in /home/einfochips/lib/cmake/project/Doxyfile)

	# note the option ALL which allows to build the docs together with the application
	add_custom_target(
		doc 		COMMAND 
		${DOXYGEN_EXECUTABLE} ${doxygen_in}
		WORKING_DIRECTORY /home/einfochips/lib/cmake/project/
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
		)
else (DOXYGEN_FOUND)
	message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


#set inatallation path to install .so file
#install(TARGETS addn DESTINATION /home/einfochips/lib/cmake/project/build)
#install(TARGETS subn DESTINATION /home/einfochips/lib/cmake/project/build)


#to link shared library
link_directories(build)

add_executable(demo src/demo.c )
target_link_libraries(demo basic)


install (TARGETS demo DESTINATION test)
