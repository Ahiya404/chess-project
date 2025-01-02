
#pragma once
#include "Piece.h"
class Knight :
	public Piece
{
public:
	Knight(const unsigned int row, const unsigned int col, const int isWhite, const bool first);
	virtual int move(const std::string move, Piece* b[][ROW], Board boarder);
	virtual int isValid(const std::string end, Piece* b[][ROW], Board boarder);
	virtual std::string return_type()const;
	virtual Piece* return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status);
};

