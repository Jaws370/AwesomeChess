# adds piece as a library
add_library(piece Piece.cpp)

# link the graphics portion of sfml to piece
target_link_libraries(piece PRIVATE sfml-graphics)
