#pragma once
#include "Piece.h"
class Rook :
	public Piece
{
public:
	Rook(const unsigned int row, const unsigned int col, const int isWhite, const bool first);
	static int static_valid(const std::string end, Piece* b[][COL], Board boarder, unsigned int file, unsigned int rank, int color);
	virtual int move(const std::string move, Piece* b[][COL], Board boarder);
	virtual int isValid(const std::string end, Piece* b[][COL], Board boarder);
	virtual std::string return_type()const;
	virtual Piece* return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status);
};

