#include "King.h"
#include "NoPiece.h"
#include "Board.h"
#include "Bishop.h"

/*
* constructor
*/
Bishop::Bishop(const unsigned int row, const unsigned int col, const int isWhite, bool status) :Piece(row, col, isWhite, status)
{
}


int Bishop::move(const std::string move, Piece* b[][COL], Board boarder)
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
	if (check == Vaild_Move || check == Has_Checked || check == CheckMate)
	{
		//allocate the last place
		delete[] b[Con[move[1]]][Con[move[0]]];

		//move # to the place 
		b[Con[FirstPlace[0]]][Con[FirstPlace[1]]] = new NoPiece(0, 0, 2, true);

		//delete memory
		delete[] b[Con[move[3]]][Con[move[2]]];

		//creating new king at the destination point
		b[Con[SecendPlace[0]]][Con[SecendPlace[1]]] = new Bishop(Con[SecendPlace[0]], Con[SecendPlace[1]], status, true);
		//setting the turn to the next player
		boarder.setWhosTurn(!(boarder.WhoTurn()));
		return check;
	}
	else
		return check;

}

int Bishop::isValid(const std::string end, Piece* b[][COL], Board boarder)
{
	return Bishop::static_valid(end, b, boarder, this->_file, this->_rank, this->get_color());
}
int Bishop::static_valid(const std::string end, Piece* b[][COL], Board boarder, unsigned int file, unsigned int rank, int color)
{
	std::string FirstPlace = "";
	FirstPlace += end[1];
	FirstPlace += end[0];


	std::string SecendPlace = "";
	SecendPlace += end[3];
	SecendPlace += end[2];
	std::string moveTo = FirstPlace + SecendPlace;

	std::string Sourcer = moveTo.substr(0, 2);;
	std::string dester = moveTo.substr(2, 2);;
	// in the dest there is a player of his turn 
	if (b[Con[moveTo[2]]][Con[moveTo[3]]]->get_color() == boarder.WhoTurn())
	{
		return Cant_Eat_Your_Piece;
	}

	//probalm 7 , dest = source
	if (moveTo[0] == moveTo[2] && moveTo[1] == moveTo[3])
	{
		return Move_To_Same_Square;
	}

	//problam 5 we check on the board so i dont need to check this here
	// always wont to enter here 
	if (true == true)
	{
		int source[2], dest[2];
		int check = 0, PlusPlus = 1, MinusMinus = 1, PlusMinus = 1, MinusPlus = 1;
		//get the source and dest as string
		source[0] = Con[Sourcer[0]];
		source[1] = Con[Sourcer[1]];
		dest[0] = Con[dester[0]];
		dest[1] = Con[dester[1]];
		int i = source[0], j = source[1];
		// i have 4 Diagonals, ++, --, +-, -+
		//so there i do ++

		//++

		//run all over ++ diagnol and if i found the Place in this diagnol so PlusPlus = 0
		while (i < 8 && j < 8)
		{
			if (i == dest[0] && j == dest[1])
				//the index is in ++ Diagnol
				PlusPlus = 0;
			//go ++ diagnol
			i++, j++;
		}

		//reset them for next loop
		i = source[0], j = source[1];


		//--
		//WHILE INDEX ARE FINE
		while (i >= 0 && j >= 0)
		{
			//if i found the place
			if (i == dest[0] && j == dest[1])
				//the index is in -- Diagnol
				MinusMinus = 0;

			//go -- diagnol
			i--, j--;
		}

		//reset them for next loop
		i = source[0], j = source[1];

		//+-
		//WHILE INDEX ARE FINE
		while (i < 8 && j >= 0)
		{
			//if i found the place
			if (i == dest[0] && j == dest[1])
				//the index is in +- Diagnol
				PlusMinus = 0;

			//go +- diagnol
			i++, j--;
		}

		//reset them for next loop
		i = source[0], j = source[1];

		//-+
		//WHILE INDEX ARE FINE
		while (j < 8 && i >= 0)
		{
			//if i found the place
			if (i == dest[0] && j == dest[1])
				//the index is in -+ Diagnol
				MinusPlus = 0;

			//go -+ diagnol
			i--, j++;
		}


		//reset them for next loop
		i = source[0], j = source[1];




		//if the place is in this diagnol
		if (PlusPlus == 0)
		{
			//++

			//run all over ++ diagnol and if i found the Place in this diagnol so PlusPlus = 0
			while (i < 8 && j < 8)
			{
				//go ++ diagnol
				i++, j++;

				if (i == dest[0] && j == dest[1])
					//if i found the place
					check = 1;

				//out of index
				if (i < 0 || i >= 8 || j < 0 || j >= 8)
					break;

				//if there is a player so leave 
				if (b[i][j]->return_type() != "#")
					break;
			}

		}
		//reset them for next loop
		i = source[0], j = source[1];

		//if the player is in -- Diagnol
		if (MinusMinus == 0 && check == 0)
		{
			//--
			//WHILE INDEX ARE FINE
			while (i >= 0 && j >= 0)
			{
				//go -- diagnol
				i--, j--;
				if (i == dest[0] && j == dest[1])
					//if i found the place
					check = 1;

				//out of index
				if (i < 0 || i >= 8 || j < 0 || j >= 8)
					break;

				//if there is a player so leave 
				if (b[i][j]->return_type() != "#")
					break;

			}

		}

		//reset them for next loop
		i = source[0], j = source[1];
		if (MinusPlus == 0 && check == 0)
		{
			//-+
			//WHILE INDEX ARE FINE
			while (j < 8 && i >= 0)
			{

				//go -+ diagnol
				i--, j++;

				if (i == dest[0] && j == dest[1])
					//if i found the place
					check = 1;

				//out of index
				if (i < 0 || i >= 8 || j < 0 || j >= 8)
					break;

				//if there is a player so leave 
				if (b[i][j]->return_type() != "#")
					break;

			}

		}
		//reset them for next loop
		i = source[0], j = source[1];

		if (PlusMinus == 0 && check == 0)
		{
			//+-
			//WHILE INDEX ARE FINE
			while (i < 8 && j >= 0)
			{
				//go +- diagnol
				i++, j--;

				if (i == dest[0] && j == dest[1])
					//if i found the place
					check = 1;

				//out of index
				if (i < 0 || i >= 8 || j < 0 || j >= 8)
					break;

				//if there is a player so leave 
				if (b[i][j]->return_type() != "#")
					break;

			}
		}



		//if there was a problem so leave
		if (check == 0)
			return Not_Valid_Move;
	}

	return Vaild_Move;
}
std::string Bishop::return_type()const
{
	if (this->get_color() == WHITE)
		return "B";
	return "b";
}
Piece* Bishop::return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)
{
	Piece* ret = new Bishop(row, col, color, status);
	return ret;

}