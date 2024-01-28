#ifndef PIECES_HPP
#define PIECES_HPP

#include "../piece_types/shared/Piece.hpp"
#include <SFML/Graphics.hpp>
#include <bitset>
#include <iostream>

class Pieces
{
private:
    Piece piecesArr[8][8]{};
    float spaceSize{64.f};
    float pieceScale{1.f};
    std::bitset<64> bPiecesData[14]{};
    std::vector<int> allLastMoves{};
    std::vector<std::pair<int, std::vector<int>>> getPawnMoves(const int &col, const int &row, const Piece::PieceColor &color);
    std::vector<std::pair<int, std::vector<int>>> getEnPassant(const int &col, const int &row, const Piece::PieceColor &color);
    std::vector<std::pair<int, std::vector<int>>> getBRQMoves(const int &col, const int &row, const Piece::PieceColor &color, const Piece::PieceType &type);
    std::vector<std::pair<int, std::vector<int>>> getKnKMoves(const int &col, const int &row, const Piece::PieceColor &color, const Piece::PieceType &type);
    std::vector<std::pair<int, std::vector<int>>> getKingCastling(const int &pos, const int &col, const int &row, const Piece::PieceColor &color, const Piece::PieceType &type);
    std::vector<std::pair<int, std::vector<int>>> removeChecks(const Piece::PieceColor &color, const std::vector<std::pair<int, std::vector<int>>> &tempOutput);

public:
    Pieces();
    std::vector<std::pair<int, std::vector<int>>> getPossibleMoves(const int &pos, const bool &checkingKing = false);
    void movePiece(int &pos1, int &pos2, std::vector<int> &additonalMoves);
    void displayPieces(sf::RenderWindow &window);
    static int toInt(const int &col, const int &row);
    static std::pair<int, int> toColRow(const int &pos);
    template <typename T> static std::vector<T> combineVectors(const std::vector<T> &v1, const std::vector<T> &v2);
    std::vector<int> getAllMoves(std::string color);
    void resize(const float &spaceSize);
    void whitePromotion(int col, int row);
    void blackPromotion(int col, int row);
    void getPromote(Piece::PieceColor c, Piece::PieceType t, int col, int row);
    void updateBoard();
};

#endif
