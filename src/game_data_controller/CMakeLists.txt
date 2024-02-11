# create the user_input library
add_library(game_data_controller GameDataController.cpp)

# link the user_input class to pieces
target_link_libraries(game_data_controller PUBLIC piece_types)

# link sfml graphics library
target_link_libraries(game_data_controller PRIVATE sfml-graphics)
