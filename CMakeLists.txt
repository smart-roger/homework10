cmake_minimum_required(VERSION 3.2)

project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(bulkmt VERSION 0.0)

include_directories(
	include
)

add_executable(bulkmt
					main.cpp 
					src/TCommandStore.cpp
					src/TCommandProcessor.cpp 
					src/TBlockStore.cpp
					src/TBlockProcessor.cpp
					src/TConsole.cpp
					src/TObserver.cpp)

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
