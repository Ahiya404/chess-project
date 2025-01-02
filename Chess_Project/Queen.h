#pragma once
#include "Piece.h"
#include "Rook.h"
class Queen :
    public Piece
{
public:
    Queen(const unsigned int row, const unsigned int col, const int isWhite, const bool first);
    virtual std::string return_type()const;
    virtual int move(const std::string move, Piece* b[][COL], Board boarder);
    virtual int isValid(const std::string end, Piece* b[][ROW], Board boarder);
    virtual Piece* return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status);
};

