add_library(tp1_core
  src/trace_utils.cxx
  src/ode.cxx
)

target_include_directories(tp1_core PUBLIC include)

add_executable(tp1_trace src/main_trace.cxx)
target_link_libraries(tp1_trace PRIVATE tp1_core)

add_executable(tp1_ode src/main_ode.cxx)
target_link_libraries(tp1_ode PRIVATE tp1_core)
