#include "piece.h"

namespace render {

Piece::Piece(shared_ptr<spdlog::logger> log) : Sprite(log) {

}

void Piece::SetLogicalPosition(int x, int y) {
    SetPosition(CELL_SIZE * x, CELL_SIZE * y);
}

}