#pragma once
#include "Board.h"
#include "Piece.h"

class Board;
class Piece;

class Player
{
	friend Board;
public:
	Player(const bool color);
	bool isCheck(Piece* b[][8]);

private:
	bool _check;
	bool _isWhite;
};

