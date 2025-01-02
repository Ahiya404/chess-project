#include "Piece.h"
/*
* construator
*/
Piece::Piece(const unsigned int row, const unsigned int col, const int isWhite, const bool first)
{
	this->_firstMove = first;
	this->_file = row;
	this->_rank = col;
	this->_isWhite = isWhite;
}
//function will return the color of the PIECE
int Piece::get_color()const
{
	return this->_isWhite;
}
//function will get the first move of the player
bool Piece::get_first_move()const
{
	return this->_firstMove;
}
//function will get the first move and if the user have moved two squares
bool Piece::get_first()const
{
	return done_first;
}
//function will set the state if the first move
void Piece::setFirst(const bool state)
{
	done_first = state;
}
/*
* function will overload the operator =
* input:the other piece
* output:the other piece
*/
Piece& Piece::operator=(Piece& other)
{
	// copy fields
	this->_isWhite = other._isWhite;
	this->_file = other._file;
	this->_firstMove = other._firstMove;

	// allocating memory 
	this->_file = this->_file;

	// copy all the elements
	return *this;
}
/*
* function will actualize the copy constructor
* input:the other piece
* output:none
*/
Piece::Piece(Piece& other)
{
	*this = other;
}
//function will get the file of the Piece
unsigned int Piece::get_file()const
{
	return this->_file;
}
//function will return the rank of the piece
unsigned int Piece::get_rank()const
{
	return this->_rank;
}
