add_executable(tp2_collections src/main_collections.cxx)
target_include_directories(tp2_collections PRIVATE include)

add_executable(tp2_verlet src/main_verlet.cxx)
target_include_directories(tp2_verlet PRIVATE include)
