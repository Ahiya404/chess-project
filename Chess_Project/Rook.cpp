#include "Rook.h"
#include "NoPiece.h"

Rook::Rook(const unsigned int row, const unsigned int col, const int isWhite, const bool first) :Piece(row, col, isWhite, first)
{

}
std::string Rook::return_type()const
{
	if (this->_isWhite)
		return "R";
	return "r";
}

int Rook::move(const std::string move, Piece* b[][COL], Board boarder)
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
		b[Con[move[3]]][Con[move[2]]] = new Rook(Con[SecendPlace[0]], Con[SecendPlace[1]], color, false);

		this->_firstMove = false;
		//fine move return the check
		return check;
	}
	else
		//return the error
		return check;


	return check;
}



int Rook::isValid(const std::string end, Piece* b[][COL], Board boarder)
{
	return Rook::static_valid(end, b, boarder, this->_file, this->_rank, this->_isWhite);
}
/*
* function will staticly check if the movment of the piece is valid(static because the use of the queen function)
*/
int Rook::static_valid(const std::string end, Piece* b[][COL], Board boarder, unsigned int _file, unsigned int _rank, int color)
{
	std::string SecendPlace = end;
	if (Con[SecendPlace[2]] != Con[SecendPlace[0]] && Con[SecendPlace[3]] != Con[SecendPlace[1]])
		return Not_Valid_Move;
	if (Con[SecendPlace[2]] == Con[SecendPlace[0]] && Con[SecendPlace[3]] == Con[SecendPlace[1]])
		return Move_To_Same_Square;

	//checking throw all files and ranks that are avalibale from the rook direction
	if (Con[SecendPlace[3]] != Con[SecendPlace[1]])
	{
		if (Con[SecendPlace[1]] < Con[SecendPlace[3]])
		{
			for (int i = Con[SecendPlace[1]] + 1; i < Con[SecendPlace[3]]; i++)
			{
				//checking if there are any pieces on the way
				if (b[i][Con[SecendPlace[0]]]->return_type() != "#")
				{
					return Cant_Eat_Your_Piece;
				}
			}
		}
		else
		{
			for (int i = Con[SecendPlace[1]] - 1; i > Con[SecendPlace[3]]; i--)
			{
				if (b[i][Con[SecendPlace[0]]]->return_type() != "#")
				{
					return Cant_Eat_Your_Piece;
				}
			}
		}
	}
	else
	{
		if (Con[SecendPlace[0]] < Con[SecendPlace[2]])
		{
			for (int i = Con[SecendPlace[0]] + 1; i < Con[SecendPlace[2]]; i++)
			{
				if (b[Con[SecendPlace[1]]][i]->return_type() != "#")
				{
					return Cant_Eat_Your_Piece;
				}
			}
		}
		else
		{
			for (int i = Con[SecendPlace[0]] - 1; i > Con[SecendPlace[2]]; i--)
			{
				if (b[Con[SecendPlace[1]]][i]->return_type() != "#")
				{
					return Cant_Eat_Your_Piece;
				}
			}
		}
	}
	return Vaild_Move;
}
Piece* Rook::return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)
{
	Piece* ret = new Rook(row, col, color, status);
	return ret;
}