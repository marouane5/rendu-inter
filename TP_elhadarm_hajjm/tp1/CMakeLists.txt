add_library(tp1_core
  src/trace_utils.cxx
  src/ode.cxx
)

target_include_directories(tp1_core PUBLIC include)

add_executable(tp1_trace src/main_trace.cxx)
target_link_libraries(tp1_trace PRIVATE tp1_core)

add_executable(tp1_trace_fast src/main_trace_fast.cxx)
target_link_libraries(tp1_trace_fast PRIVATE tp1_core)

add_executable(tp1_trace_profile src/main_trace.cxx)
target_link_libraries(tp1_trace_profile PRIVATE tp1_core)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(tp1_trace_profile PRIVATE -pg)
  target_link_options(tp1_trace_profile PRIVATE -pg)
endif()

add_executable(tp1_ode src/main_ode.cxx)
target_link_libraries(tp1_ode PRIVATE tp1_core)
