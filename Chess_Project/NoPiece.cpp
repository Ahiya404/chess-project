#include "NoPiece.h"

NoPiece::NoPiece(const unsigned int row, const unsigned int col, const int isWhite, const  bool first) :Piece(row, col, isWhite, first)
{

}
//try to move mothing,aoutomaticly 3
int NoPiece::isValid(const std::string end, Piece* b[][COL], Board boarder)
{
	return not_Your_Piece;
}
//try to move mothing,aoutomaticly 3
int NoPiece::move(const std::string move_to, Piece* b[][COL], Board boarder)
{
	return not_Your_Piece;
}
//the type of nothing
std::string NoPiece::return_type()const
{
	return "#";
}
//function will allocate the memory of the object
Piece* NoPiece::return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)
{
	Piece* ret = new NoPiece(row, col, color, status);
	return ret;
}