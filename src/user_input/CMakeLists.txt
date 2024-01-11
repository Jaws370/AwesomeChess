# create the user_input library
add_library(user_input UserInput.cpp)

# link the user_input class to pieces
target_link_libraries(user_input PUBLIC pieces)

# link sfml graphics library
target_link_libraries(user_input PRIVATE sfml-graphics)
