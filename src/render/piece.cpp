#include "piece.h"

namespace render {

string RetrieveTextureSource(PieceColor color, PieceType type);

Piece::Piece(shared_ptr<spdlog::logger> log) : Sprite(log) {

}

bool Piece::Init(PieceColor color, PieceType type, unsigned int x, unsigned int y) {
    _color = color;
    _type = type;

    if (!Init(RetrieveTextureSource(_color, _type), CELL_SIZE, CELL_SIZE)) {
        return false;
    }

    SetLogicalPosition(x, y);

    return true;
}

void Piece::SetLogicalPosition(unsigned int x, unsigned int y) {
    SetPosition(CELL_SIZE * x, CELL_SIZE * y);
}

PieceType Piece::type() {
    return _type;
}

PieceColor Piece::color() {
    return _color;
}

string RetrieveTextureSource(PieceColor color, PieceType type) {
    string texture_path = texture_source::PATH;
    switch(type) {
        case PieceType::PAWN:
            texture_path += (color == PieceColor::WHITE ? texture_source::white::PAWN : texture_source::black::PAWN);
            break;
        case PieceType::KING:
            texture_path += (color == PieceColor::WHITE ? texture_source::white::KING : texture_source::black::KING);
            break;
        case PieceType::QUEEN:
            texture_path += (color == PieceColor::WHITE ? texture_source::white::QUEEN : texture_source::black::QUEEN);
            break;
        case PieceType::BISHOP:
            texture_path += (color == PieceColor::WHITE ? texture_source::white::BISHOP : texture_source::black::BISHOP);
            break;
        case PieceType::HORSE:
            texture_path += (color == PieceColor::WHITE ? texture_source::white::HORSE : texture_source::black::HORSE);
            break;
        case PieceType::ROOK:
            texture_path += (color == PieceColor::WHITE ? texture_source::white::ROOK : texture_source::black::ROOK);
            break;
        default:
            texture_path += texture_source::BOARD;
    }

    return texture_path;
}

}