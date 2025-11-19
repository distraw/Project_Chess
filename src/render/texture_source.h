#pragma once

#include <string>
using namespace std;

namespace texture_source {

constexpr const char* PATH = "./texture/";
constexpr const char* BOARD = "board.jpg";

    namespace white {

    constexpr const char* PAWN = "white-pawn.png";
    constexpr const char* KING = "white-king.png";
    constexpr const char* QUEEN = "white-queen.png";
    constexpr const char* HORSE = "white-knight.png";
    constexpr const char* BISHOP = "white-bishop.png";
    constexpr const char* ROOK = "white-rook.png";

    }

    namespace black {

    constexpr const char* PAWN = "black-pawn.png";
    constexpr const char* KING = "black-king.png";
    constexpr const char* QUEEN = "black-queen.png";
    constexpr const char* HORSE = "black-knight.png";
    constexpr const char* BISHOP = "black-bishop.png";
    constexpr const char* ROOK = "black-rook.png";

    }
}