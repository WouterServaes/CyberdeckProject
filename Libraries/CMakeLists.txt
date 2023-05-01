
add_library(nlohmann STATIC json.hpp)
add_library(mlohmann_fwd STATIC json_fwd.hpp)
target_link_libraries(${PROJECT_NAME} nlohmann)
target_link_libraries(${PROJECT_NAME} nlohmann_fwd)
