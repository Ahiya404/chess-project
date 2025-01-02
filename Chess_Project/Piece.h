#pragma once
#include "Board.h"
#include <iostream>
#include <string>
#include <map>
#define ROW 8
#define COL 8
using std::map;
static map<char, int> Con{ {'1',0},{'2',1},{'3',2} ,{'4',3} ,{'5',4} ,{'6',5} ,{'7',6} ,{'8',7},{'a',0},{'b',1},{'c',2} ,{'d',3} ,{'e',4} ,{'f',5} ,{'g',6} ,{'h',7} };


class Board;
class Player;

class Piece
{
public:
	static bool done_first;
	bool get_first_move()const;
	Piece(const unsigned int row, const unsigned int col, const int isWhite, const bool first);
	virtual int move(const std::string move, Piece* b[][COL], Board boarder) = 0;
	virtual int isValid(const std::string end, Piece* b[][ROW], Board boarder) = 0;
	int get_color()const;
	virtual std::string return_type()const = 0;
	bool get_first()const;
	void setFirst(const bool state);
	unsigned int get_file()const;
	unsigned int get_rank()const;
	virtual Piece* return_allocated(const unsigned int row, const unsigned int col, const int color, const bool status) = 0;
	Piece& operator=(Piece& other);
	Piece(Piece& other);
protected:

	bool _firstMove;
	unsigned int _file;
	unsigned int _rank;
	int _isWhite;

};

