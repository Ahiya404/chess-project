#include "Pawn.h"
#include "NoPiece.h"
#include "Queen.h"
Pawn::Pawn(const unsigned int row, const unsigned int col, const int isWhite, const bool first) :Piece(row, col, isWhite, first)
{
}
/*
* function will move the pawn from the source to the dest
* input:the movment string the piece board and the board object
* output:valid or not
*/
int Pawn::move(const std::string move, Piece* b[][COL], Board boarder)
{
	//first place = the place
	//first place = the place
	std::string FirstPlace = "";
	FirstPlace += move[1];
	FirstPlace += move[0];

	int check = isValid(move, b, boarder);

	std::string SecendPlace = "";
	SecendPlace += move[3];
	SecendPlace += move[2];
	bool status_black = move[1] > move[3] + 1;
	bool status_white = move[1] < move[3] + 1;
	int status = this->_isWhite;
	//call is valid to check if the place is fine
	if (check == Vaild_Move || check == Has_Checked || check == CheckMate || check == enPassent)
	{
		//enpassent check:succses
		if (this->get_color() == 0)
		{
			Piece::done_first = this->_firstMove && status_black;
		}
		else if (this->get_color() == WHITE)
		{
			Piece::done_first = this->_firstMove && status_white;
		}
		//allocate the last place
		delete[] b[Con[FirstPlace[0]]][Con[FirstPlace[1]]];

		//move # to the place 
		b[Con[FirstPlace[0]]][Con[FirstPlace[1]]] = new NoPiece(0, 0, NOPIECE, true);
		if (check == enPassent)
		{
			delete[] b[Con[SecendPlace[0]] - 1][Con[SecendPlace[1]]];
			b[Con[SecendPlace[0]] - 1][Con[SecendPlace[1]]] = new NoPiece(0, 0, NOPIECE, true);
		}

		//delete memory
		delete[] b[Con[SecendPlace[0]]][Con[SecendPlace[1]]];

		//creating new king at the destination point
		if (SecendPlace[0] == '8' || SecendPlace[0] == '1')
		{
			b[Con[SecendPlace[0]]][Con[SecendPlace[1]]] = new Queen(SecendPlace[0], SecendPlace[1], status, false);
			return 8;
		}
		else
		{
			b[Con[SecendPlace[0]]][Con[SecendPlace[1]]] = new Pawn(SecendPlace[0], SecendPlace[1], status, false);
		}
		//setting the turn to the next player

		return check;
	}
	else
		return check;

}
/*
* function will check if the movement of the pawn is legal
* input:the string:where do the user want to move the pawn and which pawn does he want to move
* the board, and the board object
* output:if the movment is legal or not
*/
int Pawn::isValid(const std::string end, Piece* b[][ROW], Board boarder)
{
	
	if (this->_isWhite == WHITE)
	{
		if (end[0] != end[2] && end[3] > end[1] + 1)
			return Not_Valid_Move;
		if (end[0] == end[2] && end[3] == end[1])
			return Move_To_Same_Square;
		if (end[3] > (end[1] + 1) && !(this->_firstMove))
			return Not_Valid_Move;
		if (end[3] > end[1] + 2)
			return Not_Valid_Move;
		if (end[2] > end[0] + 1 || end[2] < end[0] - 1)
			return Not_Valid_Move;
		if (end[1] > end[3])
			return Not_Valid_Move;
		if (end[0] != end[2] && end[3] == end[1]) 
			return Not_Valid_Move;
		if (end[0] == end[2] && b[Con[end[3]]][Con[end[2]]]->return_type() != "#")
			return Not_Valid_Move;
		if (b[Con[end[3] - 1]][Con[end[2]]]->return_type() == "p"  && Piece::done_first)
			return enPassent;
		if (end[0] != end[2] && b[Con[end[3]]][Con[end[2]]]->return_type() == "#")
			return Cant_Eat_Your_Piece;

		return Vaild_Move;
	}
	else
	{
		if (end[0] != end[2] && end[1] - 1 > end[3])
			return Not_Valid_Move;
		if (end[2] > end[0] + 1 || end[2] < end[0] - 1)
			return Not_Valid_Move;
		if (end[0] == end[2] && end[3] == end[1])
			return Move_To_Same_Square;
		if (end[1] > (end[3] + 1) && !(this->_firstMove))
			return Not_Valid_Move;
		if (end[1] > end[3] + 2)
			return Not_Valid_Move;
		if (end[3] > end[1])
			return Not_Valid_Move;
		if (end[0] != end[2] && end[3] == end[1])
			return Not_Valid_Move;
		if (end[0] == end[2] && b[Con[end[3]]][Con[end[2]]]->return_type() != "#")
			return Cant_Eat_Your_Piece;
		if (b[Con[end[3] + 1]][Con[end[2]]]->return_type() == "P" && Piece::done_first)
			return enPassent;
		if (end[0] != end[2] && b[Con[end[3]]][Con[end[2]]]->return_type() == "#")
			return Not_Valid_Move;
		return Vaild_Move;
	}

}
std::string Pawn::return_type()const
{
	if (this->_isWhite)
		return "P";
	return "p";
}
Piece* Pawn::return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)
{
	Piece* ret = new Pawn(row, col, color, status);
	return ret;
}