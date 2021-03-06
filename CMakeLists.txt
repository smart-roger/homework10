﻿cmake_minimum_required(VERSION 3.2)

project(bulkmt VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(bulkmt VERSION 0.0)

include_directories(
	include
)

find_package (Threads)

add_executable(bulkmt
					main.cpp 
					src/TCommandProcessor.cpp 
					src/TBulk.cpp
					src/TBlockProcessor.cpp
					src/TConsole.cpp
					src/TObserver.cpp)

target_link_libraries (bulkmt ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(bulkmt PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

install(TARGETS bulkmt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT __shurik@list.ru)

include(CPack)
