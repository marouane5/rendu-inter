add_library(tp3_core
  src/univers.cxx
)
target_include_directories(tp3_core PUBLIC include)

add_executable(tp3_lab3 src/main_lab3.cxx)
target_link_libraries(tp3_lab3 PRIVATE tp3_core)

add_executable(tp3_test_vecteur test/test_vecteur.cxx)
target_include_directories(tp3_test_vecteur PRIVATE include)
add_test(NAME tp3_test_vecteur COMMAND tp3_test_vecteur)
