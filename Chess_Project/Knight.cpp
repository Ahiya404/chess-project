#include "Knight.h"
#include "NoPiece.h"
#include "Board.h"

Knight::Knight(const unsigned int row, const unsigned int col, const int isWhite, const bool first) :Piece(row, col, isWhite, first)
{

}
/*
* function will move the king to the dest
* input:the cordination of the movement
* output:none
*/
int Knight::move(const std::string move, Piece* b[][ROW], Board boarder)
{
	//first place = the place
	//first place = the place
	std::string FirstPlace = "";
	FirstPlace += move[1];
	FirstPlace += move[0];


	std::string SecendPlace = "";
	SecendPlace += move[3];
	SecendPlace += move[2];
	int status = this->_isWhite;
	std::string ValidMove = FirstPlace + SecendPlace;


	//call is valid to check if the place is fine 
	int check = isValid(ValidMove, b, boarder);
	std::cout << check;
	if (check == Vaild_Move || check == Has_Checked || check == CheckMate)
	{
		//allocate the last place
		delete[] b[Con[FirstPlace[0]]][Con[FirstPlace[1]]];

		//move # to the place 
		b[Con[FirstPlace[0]]][Con[FirstPlace[1]]] = new NoPiece(0, 0, 2, true);

		//delete memory
		delete[] b[Con[SecendPlace[0]]][Con[SecendPlace[1]]];

		//creating new king at the destination point
		b[Con[SecendPlace[0]]][Con[SecendPlace[1]]] = new Knight(SecendPlace[0], SecendPlace[1], status, true);
		//setting the turn to the next player
		boarder.setWhosTurn(!(boarder.WhoTurn()));
		return check;
	}
	else
		return check;
}
/*
* function will check if the movement of knight
* input:the movment string the piece board and the board object
* output:none
*/
int Knight::isValid(const std::string end, Piece* b[][ROW], Board boarder)
{
	std::string Sourcer = end.substr(0, 2);;
	std::string dester = end.substr(2, 2);;


	//in the source there is no player that he can move ( Maybe he is White that wont to move black )
	if (b[Con[end[0]]][Con[end[1]]]->get_color() != boarder.WhoTurn())
	{
		std::cout << 2;
		return 2;
	}


	// in the dest there is a player of his turn 
	if (b[Con[end[2]]][Con[end[3]]]->get_color() == boarder.WhoTurn())
	{
		return Cant_Eat_Your_Piece;
	}

	//probalm 7 , dest = source
	if (end[0] == end[2] && end[1] == end[3])
	{
		return Not_Valid_Move;
	}

	//problam 5 we check on the board so i dont need to check this here
	// always wont to enter here 
	if (true == true)
	{
		int source[2], dest[2];

		//get the source and dest as string
		source[0] = Con[Sourcer[0]];
		source[1] = Con[Sourcer[1]];
		dest[0] = Con[dester[0]];
		dest[1] = Con[dester[1]];

		//the places
		int i = source[0], j = source[1], check = 0;

		//There is 4 places , up down right left
		
		//I start with the UP

		int UpHeight = i + 2, Upwidth = j;

		//go 2 up check right + left
		if (UpHeight == dest[0] && (Upwidth + 1) == dest[1])
			check = true;
		else if (UpHeight == dest[0] && (Upwidth - 1) == dest[1])
			check = true;


		//check Down if i dont found the place
		if (check == false)
		{
			int DownHeight = i - 2, DownWidth = j;
			//go 2 down check right + left
			if (DownHeight == dest[0] && (DownWidth + 1) == dest[1])
				check = true;
			else if (DownHeight == dest[0] && (DownWidth - 1) == dest[1])
				check = true;

		}


		//check right 
		if (check == false)
		{
			int RightHeight = i, RightDown = j - 2;

			//2 left 1 high
			if ((RightHeight + 1) == dest[0] && RightDown == dest[1])
				check = true;
			//2 left 1 Minus
			else if ((RightHeight - 1) == dest[0] && RightDown == dest[1])
				check = true;
		}



		//check left
		if (check == false)
		{
			int LeftHeight = i, LeftDown = j + 2;

			//2 left 1 high
			if ((LeftHeight + 1) == dest[0] && LeftDown == dest[1])
				check = true;
			//2 left 1 Minus
			else if ((LeftHeight - 1) == dest[0] && LeftDown == dest[1])
				check = true;
		}



		//not fine place
		if (check == false)
			return Not_Valid_Move;
	}







	return 0;
}
//function will return the type of the knight
std::string Knight::return_type()const
{
	if (this->_isWhite)
		return "N";
	return "n";
}
//function will allocate memory for the knight object
Piece* Knight::return_allocated(const unsigned int col, const unsigned int row, const int color, const bool status)
{
	Piece* ret = new Knight(row, col, color, status);
	return ret;
}