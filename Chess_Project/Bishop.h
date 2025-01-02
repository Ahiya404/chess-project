#pragma once
#include "Piece.h"
class Bishop :
	public Piece
{
public:
	Bishop(const unsigned int row, const unsigned int col, const int isWhite, const bool first);
	virtual int move(const std::string move, Piece* b[][ROW], Board boarder);
	virtual int isValid(const std::string end, Piece* b[][ROW], Board boarder);
	static int static_valid(const std::string end, Piece* b[][COL], Board boarder, unsigned int file, unsigned int rank, int color);
	virtual std::string return_type()const;
	Piece* return_allocated(const unsigned int row, const unsigned int col, const int color, const bool status);
};

