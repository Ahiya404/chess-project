#include "King.h"
#include "NoPiece.h"
#include "Board.h"
#include "Rook.h"
King::King(const unsigned int row, const unsigned int col, const int isWhite, const bool first) :Piece(row, col, isWhite, first)
{

}
//function will return the type of the piece
std::string King::return_type()const
{
	if (this->_isWhite)
		return "K";
	return "k";
}
/*
* function will move the piece from the source to the dest
* input:the movment of the piece the piece board and the board object
* output:if the move is valid or nah
*/
int King::move(const std::string move, Piece* b[][COL], Board boarder)
{

	std::string FirstPlace = "";
	FirstPlace += move[1];
	FirstPlace += move[0];


	std::string SecendPlace = "";
	SecendPlace += move[3];
	SecendPlace += move[2];


	int status = this->_isWhite;

	//call is valid to check if the place is fine 
	int check = isValid(move, b, boarder);
	if (check == Vaild_Move || check == Has_Checked || check == CheckMate || check == castle)
	{
		//allocate the last place
		delete[] b[Con[FirstPlace[0]]][Con[FirstPlace[1]]];

		//move # to the place 
		b[Con[FirstPlace[0]]][Con[FirstPlace[1]]] = new NoPiece(0, 0, NOPIECE, true);

		//delete memory
		delete[] b[Con[SecendPlace[0]]][Con[SecendPlace[1]]];

		//creating new king at the destination point
		b[Con[SecendPlace[0]]][Con[SecendPlace[1]]] = new King(Con[SecendPlace[0]], Con[SecendPlace[1]], status, false);
		//setting the turn to the next player
		if (check == castle)
		{
			if (SecendPlace[1] == 'b')
			{
				//if the user decides that he wants to castle and the castle is valid
				delete[] b[Con[SecendPlace[0]]][Con[SecendPlace[1]] - 1];
				b[Con[SecendPlace[0]]][Con[SecendPlace[1]] - 1] = new NoPiece(0, 0, NOPIECE, true);
				delete[] b[Con[SecendPlace[0]]][Con[SecendPlace[1]] + 1];
				b[Con[SecendPlace[0]]][Con[SecendPlace[1]] + 1] = new Rook(Con[SecendPlace[1] + 1], Con[SecendPlace[0]], status, false);
			}
			else
			{
				delete[] b[Con[SecendPlace[0]]][Con[SecendPlace[1]] + 2];
				b[Con[SecendPlace[0]]][Con[SecendPlace[1]] + 2] = new NoPiece(0, 0, NOPIECE, true);
				delete[] b[Con[SecendPlace[0]]][Con[SecendPlace[1]] - 1];
				b[Con[SecendPlace[0]]][Con[SecendPlace[1]] - 1] = new Rook(Con[SecendPlace[1] - 1], Con[SecendPlace[0]], status, false);
			}
		}
		this->_firstMove = false;

		return check;
	}
	else
		return check;

}
/*
* function will check if the king move is correct
* input:string, what the user wants to do, the board with the pieces,and the board object
* output:if the move valid return 0,1,8,10 else is invalid
*/
int King::isValid(const std::string end, Piece* b[][COL], Board boarder)
{
	//e2b3, i wont to get 2 and 3

	//check if the castle is on the left or on the right
	if ((end[1] == end[3]) && (end[0] == end[2] - 2) && this->_firstMove && ((b[0][7]->get_first_move() && (this->get_color() == b[0][7]->get_color())) || (b[7][7]->get_first_move() && (b[7][7]->get_color() == this->get_color()))))
	{
		//checks if there is a pieces on the way to the king
		for (int i = Con[end[0]] + 1; i < Con['h']; i++)
		{
			if (b[Con[end[1]]][i]->return_type() != "#")
			{
				return Cant_Eat_Your_Piece;
			}
		}
		return castle;
	}
	//check if the castle is on the left or on the right
	if ((end[1] == end[3]) && (end[0] == end[2] + 2) && this->_firstMove && ((b[0][0]->get_first_move() && this->get_color() == b[0][0]->get_color()) || (b[7][0]->get_first_move() && (this->get_color() == b[7][0]->get_color()))))
	{
		//checks if there is a pieces on the way to the king
		for (int i = Con[end[0]] - 1; i > Con['a']; i--)
		{
			if (b[Con[end[1]]][i]->return_type() != "#")
			{
				return Cant_Eat_Your_Piece;
			}
		}
		return castle;
	}
	//if there is nothing or another color so return 2
	if (b[Con[end[3]]][Con[end[2]]]->get_color() == this->get_color())
	{
		return Cant_Eat_Your_Piece;
	}
	// the indexex is unvalid
	else if (end[2] > end[0] + 1 || end[2] < end[0] - 1 || end[3] > end[1] + 1 || end[3] < end[1] - 1)
	{
		return Not_Valid_Move;
	}
	//dest = source
	else if (end[0] == end[2] && end[1] == end[3])
	{
		return Move_To_Same_Square;
	}

	return Vaild_Move;

}
Piece* King::return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)
{
	Piece* ret = new King(row, col, color, status);
	return ret;
}