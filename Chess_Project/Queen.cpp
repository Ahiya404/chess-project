#include "Queen.h"
#include "Bishop.h"
#include "NoPiece.h"
Queen::Queen(const unsigned int row, const  unsigned int col, const int isWhite, const bool first) :Piece(row, col, isWhite, first)
{

}
std::string Queen::return_type()const
{
	if (this->_isWhite)
		return "Q";
	return "q";
}
/*
* function will move the queen from the source to the dest
* input:the string:where to go from where,the board and the Piece board
* output:valid or not valid
*/
int Queen::move(const std::string move, Piece* b[][COL], Board boarder)
{

	//first place = the place
	std::string FirstPlace = "";
	FirstPlace += move[0];
	FirstPlace += move[1];
	int color = this->get_color();

	std::string SecendPlace = "";
	SecendPlace += move[2];
	SecendPlace += move[3];



	//call is valid to check if the place is fine 
	int check = isValid(move, b, boarder);

	if (check == 0 || check == 1 || check == 8)
	{
		//allocate the last place
		delete[] b[Con[move[1]]][Con[move[0]]];

		//move # to the place 
		b[Con[move[1]]][Con[move[0]]] = new NoPiece(1, 1, NOPIECE, true);

		delete[] b[Con[move[3]]][Con[move[2]]];
		//make them at the place
		b[Con[move[3]]][Con[move[2]]] = new	Queen(Con[SecendPlace[0]], Con[SecendPlace[1]], color, false);


		//fine move return the check
		return check;
	}
	else
		//return the error
		return check;


	return check;
}
/*
* function will check if the queen move is valid or not
* input:where to go from where
* output:if the movment is valid
*/
int Queen::isValid(const std::string end, Piece* b[][ROW], Board boarder)
{



	int Rook_result = Rook::static_valid(end, b, boarder, this->_file, this->_rank, this->_isWhite);
	int Bishop_Result = Bishop::static_valid(end, b, boarder, this->_file, this->_rank, this->_isWhite);
	//because the queen consists of the rook and the bishop,check both the rook and the queen 
	if (Rook_result == Vaild_Move || Rook_result == Has_Checked || Rook_result == CheckMate)
		return Rook_result;
	if (Bishop_Result == Vaild_Move || Bishop_Result == Has_Checked || Bishop_Result == CheckMate)
		return Bishop_Result;
	return Rook_result;

}
/*
* function will return the alocated memory object
*/
Piece* Queen::return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)
{
	Piece* ret = new Queen(row, col, color, status);
	return ret;
}