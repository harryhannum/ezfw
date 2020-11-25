file(GLOB ezsrcs src/*.cpp)
add_library(ezfw ${ezsrcs})
target_include_directories(ezfw INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
