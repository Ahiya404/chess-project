#pragma once
#include "Piece.h"
#include <string>
#include "Player.h"
#define Max_num 8
#define Min_num 0
#define Max_char 'h'
#define Min_char 'a'
static enum {
	Vaild_Move, Has_Checked, not_Your_Piece, Cant_Eat_Your_Piece, Cant_Make_Self_Check, Out_of_Index, Not_Valid_Move, Move_To_Same_Square, CheckMate, enPassent, castle, promote
};


#define WHITE 1
#define BLACK 0
#define NOPIECE -1

class Board
{
public:
	int board_move(const std::string move_to);
	~Board();
	Board(const bool P1, const bool P2);
	void initBoard();
	bool WhoTurn()const;
	bool check_Shach(const std::string move_to);
	std::string toChar(int num);
	std::string IntChar(int num);
	void setWhosTurn(const bool set);
	Piece* _board[8][8];
	Board& operator=(Board& other);
	Board(Board& other);

private:
	Player* _P1;
	Player* _P2;
	bool which_turn;
};

