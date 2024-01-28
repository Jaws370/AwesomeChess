# include the pieces library
add_library(pieces Pieces.cpp)

# link the pieces class to piece
target_link_libraries(pieces PUBLIC piece_types)

# link the graphics portion of sfml to pieces
target_link_libraries(pieces PRIVATE sfml-graphics)
