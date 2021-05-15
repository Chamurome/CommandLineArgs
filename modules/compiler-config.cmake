# set build type to Release if not provided via command line
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Built type" FORCE)
endif()

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# variables to store additional compiler flags
set(CXX_FLAGS)
set(CXX_FLAGS_DEBUG)
set(CXX_FLAGS_RELEASE)

# append global compiler flags to list
list(APPEND CXX_FLAGS "-fPIC" "-Wall")


# append compile flags depending on the selected compiler and build type
if(CMAKE_CXX_COMPILER MATCHES "g\\+\\+|c\\+\\+")
  list(APPEND CXX_FLAGS "-fno-rtti" )
  list(APPEND CXX_FLAGS_DEBUG "-g" "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()

if(CMAKE_CXX_COMPILER MATCHES Clang)
  list(APPEND CXX_FLAGS "-fno-rtti" "-Qunused-arguments" "-fcolor-diagnostics")
  list(APPEND CXX_FLAGS_DEBUG "-Wdocumentation")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()


message(STATUS "--> Generator:            ${CMAKE_GENERATOR}")
message(STATUS "--> Build type:           ${CMAKE_BUILD_TYPE}")
message(STATUS "--> Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "--> Flags:                ${CXX_FLAGS}")

if(CXX_FLAGS_DEBUG)
  message(STATUS "--> Build flags:          ${CXX_FLAGS_DEBUG}")
else()
message(STATUS "--> Build flags:          ${CXX_FLAGS_RELEASE}")
endif()