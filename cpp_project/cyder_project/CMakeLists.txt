file(GLOB ezsrcs src/*.cpp)
add_library(cyder_project ${ezsrcs})
target_include_directories(cyder_project INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
