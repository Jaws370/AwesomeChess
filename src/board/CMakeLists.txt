# adds board library
add_library(board Board.cpp)

# link the graphics portion of sfml to board
target_link_libraries(board PRIVATE sfml-graphics)
