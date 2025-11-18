#include "sprite.h"

namespace render {

constexpr float CELL_SIZE = 0.25f;

class Piece : public Sprite {
private:
    int _logical_x;
    int _logical_y;
public:
    Piece(shared_ptr<spdlog::logger> log);

    void SetLogicalPosition(int x, int y);
};

}