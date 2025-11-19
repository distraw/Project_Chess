#include "piece.h"

namespace render {

string RetrieveTextureSource(PieceType type);

Piece::Piece(shared_ptr<spdlog::logger> log) : Sprite(log) {

}

bool Piece::Init(PieceType type, unsigned int x, unsigned int y) {
    if (!Init(RetrieveTextureSource(type), CELL_SIZE, CELL_SIZE)) {
        return false;
    }

    SetLogicalPosition(x, y);

    return true;
}

void Piece::SetLogicalPosition(unsigned int x, unsigned int y) {
    SetPosition(CELL_SIZE * x, CELL_SIZE * y);
}

string RetrieveTextureSource(PieceType type) {
    string texture_path = texture_source::PATH;
    switch(type) {
        case PieceType::BLACK_PAWN:
            texture_path += texture_source::black::PAWN;
            break;
        case PieceType::BLACK_KING:
            texture_path += texture_source::black::KING;
            break;
        case PieceType::BLACK_QUEEN:
            texture_path += texture_source::black::QUEEN;
            break;
        case PieceType::BLACK_BISHOP:
            texture_path += texture_source::black::BISHOP;
            break;
        case PieceType::BLACK_HORSE:
            texture_path += texture_source::black::HORSE;
            break;
        case PieceType::BLACK_ROOK:
            texture_path += texture_source::black::ROOK;
            break;


        case PieceType::WHITE_PAWN:
            texture_path += texture_source::white::PAWN;
            break;
        case PieceType::WHITE_KING:
            texture_path += texture_source::white::KING;
            break;
        case PieceType::WHITE_QUEEN:
            texture_path += texture_source::white::QUEEN;
            break;
        case PieceType::WHITE_BISHOP:
            texture_path += texture_source::white::BISHOP;
            break;
        case PieceType::WHITE_HORSE:
            texture_path += texture_source::white::HORSE;
            break;
        case PieceType::WHITE_ROOK:
            texture_path += texture_source::white::ROOK;
            break;
        default:
            texture_path += texture_source::BOARD;
    }

    return texture_path;
}

}