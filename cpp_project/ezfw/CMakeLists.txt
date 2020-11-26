file(GLOB ezsrcs src/*.cpp)
add_definitions(-DEZFW_SIMULATION)
add_library(ezfw ${ezsrcs})
target_include_directories(ezfw INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
