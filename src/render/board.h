#include "piece.h"

constexpr int BOARD_SIZE = 8;

namespace render {

class Board {
private:
    Piece*** _board;
    Sprite* _background;
    GLuint _shader_program;

    void InitializeEmptyBoard();
    bool FillEmptyBoard();
    void CleanupBoard();
    void CleanupCell(unsigned int x, unsigned int y);

    shared_ptr<spdlog::logger> _log;
public:
    Board(shared_ptr<spdlog::logger> log);
    ~Board();

    bool Init(GLuint shader_program);

    void Insert(unsigned int x, unsigned int y, PieceType type);

    void Draw();
};

}