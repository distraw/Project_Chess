#include "sprite.h"

#include "texture_source.h"

namespace render {

constexpr float CELL_SIZE = 0.25f;

enum class PieceType {
    WHITE_PAWN,
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_BISHOP,
    WHITE_HORSE,
    WHITE_ROOK,

    BLACK_PAWN,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_BISHOP,
    BLACK_HORSE,
    BLACK_ROOK
};

class Piece : public Sprite {
private:
    int _logical_x;
    int _logical_y;
public:
    Piece(shared_ptr<spdlog::logger> log);

    using Sprite::Init;
    bool Init(PieceType type, unsigned int x, unsigned int y);

    void SetLogicalPosition(unsigned int x, unsigned int y);
};

}