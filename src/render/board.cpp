#include "board.h"

namespace render {

Board::Board(shared_ptr<spdlog::logger> log) {
    _log = log;

    _board = nullptr;
}

Board::~Board() {
    _log->trace("deleting rendering board...");

    CleanupBoard();
    delete _background;
}

void Board::InitializeEmptyBoard() {
    if (_board != nullptr) {
        _log->error("attempted to initialize existent chess board");
        return;
    }

    _board = new Piece**[BOARD_SIZE];
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        _board[i] = new Piece*[BOARD_SIZE];

        for (size_t j = 0; j < BOARD_SIZE; j++) {
            _board[i][j] = nullptr;
        }
    }
}

bool Board::FillEmptyBoard() {
    if (_board == nullptr) {
        _log->error("attempted to fill non-existent chess board");
        return false;
    }

    constexpr int BLACK_PAWN_ROW = 6;
    constexpr int WHITE_PAWN_ROW = 1;

    for (size_t i = 0; i < BOARD_SIZE; i++) {
        Insert(i, BLACK_PAWN_ROW, PieceColor::BLACK, PieceType::PAWN);
        Insert(i, WHITE_PAWN_ROW, PieceColor::WHITE, PieceType::PAWN);
    }

    Insert(0, 0, PieceColor::WHITE, PieceType::ROOK);
    Insert(0, 7, PieceColor::BLACK, PieceType::ROOK);
    Insert(1, 0, PieceColor::WHITE, PieceType::HORSE);
    Insert(1, 7, PieceColor::BLACK, PieceType::HORSE);
    Insert(2, 0, PieceColor::WHITE, PieceType::BISHOP);
    Insert(2, 7, PieceColor::BLACK, PieceType::BISHOP);
    Insert(3, 0, PieceColor::WHITE, PieceType::QUEEN);
    Insert(3, 7, PieceColor::BLACK, PieceType::QUEEN);
    Insert(4, 0, PieceColor::WHITE, PieceType::KING);
    Insert(4, 7, PieceColor::BLACK, PieceType::KING);
    Insert(5, 0, PieceColor::WHITE, PieceType::BISHOP);
    Insert(5, 7, PieceColor::BLACK, PieceType::BISHOP);
    Insert(6, 0, PieceColor::WHITE, PieceType::HORSE);
    Insert(6, 7, PieceColor::BLACK, PieceType::HORSE);
    Insert(7, 0, PieceColor::WHITE, PieceType::ROOK);
    Insert(7, 7, PieceColor::BLACK, PieceType::ROOK);

    return true;
}

void Board::CleanupBoard() {
    if (_board == nullptr) {
        _log->error("attempted to cleanup non-existent rendering board");
        return;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            CleanupCell(i, j);
        }

    }
    delete[] _board;
    _board = nullptr;
}

void Board::CleanupCell(unsigned int x, unsigned int y) {
    if (x > BOARD_SIZE || y > BOARD_SIZE) {
        _log->warn("tried to cleanup the cell outside of chess board borders");
        return;
    }

    if (_board[x][y] == nullptr) {
        return;
    }

    delete _board[x][y];
    _board[x][y] = nullptr;
}

bool Board::Init(GLuint shader_program) {
    _shader_program = shader_program;

    _background = new Sprite(_log);
    if (!_background->Init(string(texture_source::PATH) + texture_source::BOARD, CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE)) {
        _log->critical("failed to load sprite for board");
        return false;
    }
    _background->AttachProgram(_shader_program);
    _background->SetPosition(0, 0);

    InitializeEmptyBoard();
    FillEmptyBoard();

    return true;
}

void Board::Insert(unsigned int x, unsigned int y, PieceColor color, PieceType type) {
    if (x > BOARD_SIZE || y > BOARD_SIZE) {
        _log->warn("attempted to insert outside of chess board borders");
        return;
    }

    CleanupCell(x, y);
    _board[x][y] = new Piece(_log);
    if (!_board[x][y]->Init(color, type, x, y)) {
        _log->warn("failed to initialize piece at [{0},{1}]", x, y);
    }
    _board[x][y]->AttachProgram(_shader_program);
}

void Board::Move(unsigned int x, unsigned int y, unsigned int destination_x, unsigned int destination_y) {
    if (_board[destination_x][destination_y] != nullptr) {
        CleanupCell(destination_x, destination_y);
    }

    _board[x][y]->SetLogicalPosition(destination_x, destination_y);

    _board[destination_x][destination_y] = _board[x][y];
    _board[x][y] = nullptr;
}


void Board::Draw() {
    _background->Draw();

    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            if (_board[i][j] == nullptr) {
                continue;
            }

            _board[i][j]->Draw();
        }
    }
}

}