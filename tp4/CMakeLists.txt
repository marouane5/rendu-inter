add_library(tp4_core
  src/universe.cxx
)
target_include_directories(tp4_core PUBLIC include)

add_executable(tp4_lj_curve src/main_lj_curve.cxx)
target_link_libraries(tp4_lj_curve PRIVATE tp4_core)

add_executable(tp4_collision src/main_collision.cxx)
target_link_libraries(tp4_collision PRIVATE tp4_core)
