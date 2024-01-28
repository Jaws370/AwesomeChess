# include the libraries for each folder
add_library(
  piece_types
  shared/Piece.cpp
  rook/Rook.cpp
  bishop/Bishop.cpp
  knight/Knight.cpp
  queen/Queen.cpp
  king/King.cpp
  pawn/Pawn.cpp)

# include the headers in the folders
target_include_directories(
  piece_types
  PUBLIC shared
         pawn
         rook
         bishop
         knight
         queen
         king)

# link the graphics portion of sfml to piece_types
target_link_libraries(piece_types PRIVATE sfml-graphics)
