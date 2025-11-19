#include "sprite.h"

#include "texture_source.h"

namespace render {

constexpr float CELL_SIZE = 0.25f;

enum class PieceType {
    PAWN,
    KING,
    QUEEN,
    BISHOP,
    HORSE,
    ROOK,
};

enum class PieceColor {
    WHITE,
    BLACK,
};

class Piece : public Sprite {
private:
    int _logical_x;
    int _logical_y;

    PieceColor _color;
    PieceType _type;
public:
    Piece(shared_ptr<spdlog::logger> log);

    using Sprite::Init;
    bool Init(PieceColor color, PieceType type, unsigned int x, unsigned int y);

    void SetLogicalPosition(unsigned int x, unsigned int y);
};

}