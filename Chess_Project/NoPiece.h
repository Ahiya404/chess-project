#pragma once
#include "Piece.h"
class NoPiece :public Piece
{
public:
	NoPiece(const unsigned int row, const unsigned int col, const int isWhite, const bool first);
	int move(const std::string move, Piece* b[][COL], Board boarder);
	int isValid(const std::string end, Piece* b[][COL], Board boarder);
	std::string return_type()const;
	virtual Piece* return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)override;

};

