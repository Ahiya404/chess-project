#include "Board.h"
#include "NoPiece.h"
#include "Rook.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include <string> 

//detructor
Board::~Board()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            delete[] this->_board[i][j];
        }
    }
    delete[] this->_P1;
    delete[] this->_P2;
}
//constructor
Board::Board(const bool p1, const  bool p2)
{
    this->_P1 = new Player(p1);
    this->_P2 = new Player(p2);
    this->which_turn = false;
    this->initBoard();
}
/*
* function will init the borad
* input:none
* output:none
*/
void Board::initBoard()
{
    //first line 
    _board[0][0] = new Rook(0, 0, WHITE, true);
    _board[0][1] = new Knight(0, 0, WHITE, true);
    _board[0][2] = new Bishop(0, 0, WHITE, true);
    _board[0][3] = new King(3, 0, WHITE, true);
    _board[0][4] = new Queen(4, 0, WHITE, true);
    _board[0][5] = new Bishop(0, 0, WHITE, true);
    _board[0][6] = new Knight(0, 0, WHITE, true);
    _board[0][7] = new Rook(7, 0, WHITE, true);

    //put pawns on the first line 
    for (int i = 0; i < 8; i++)
        _board[1][i] = new Pawn(1, i, WHITE, true);

    //put all no piece
    for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++)
            _board[i][j] = new NoPiece(i, j, NOPIECE, true);

    for (int i = 0; i < 8; i++)
        _board[6][i] = new Pawn(1, i, BLACK, true);

    //put all the black
    _board[7][0] = new Rook(0, 7, BLACK, true);
    _board[7][1] = new Knight(0, 0, BLACK, true);
    _board[7][2] = new Bishop(0, 0, BLACK, true);
    _board[7][3] = new King(3, 7, BLACK, true);
    _board[7][4] = new Queen(4, 7, BLACK, true);
    _board[7][5] = new Bishop(0, 0, BLACK, true);
    _board[7][6] = new Knight(0, 0, BLACK, true);
    _board[7][7] = new Rook(7, 7, BLACK, true);

}
//function will return what turn it is
bool Board::WhoTurn()const
{
    return this->which_turn;
}
/*
* function will move the bishop from source to the dest
* input:where to move the bishop
* output:wether or not the move is valid
*/
int Board::board_move(const std::string move_to)
{
    int n3 = std::stoi(&move_to[1]);
    int n2 = std::stoi(&move_to[3]);
    if ((n3 > Max_num || n3 < Min_num) || (n2 > Max_num || n2 < Min_num) || (move_to[0] > Max_char || move_to[0] < Min_char) || (move_to[2] > Max_char || move_to[2] < Min_char))
    {
        return Out_of_Index;
    }
    if (this->WhoTurn() != this->_board[Con[move_to[1]]][Con[move_to[0]]]->get_color())
    {
        return not_Your_Piece;
    }
    if (_board[Con[move_to[3]]][Con[move_to[2]]]->return_type() != "#" && _board[Con[move_to[3]]][Con[move_to[2]]]->get_color() == this->which_turn)
        return Cant_Eat_Your_Piece;
    Board temp(*this);
    temp._board[Con[move_to[1]]][Con[move_to[0]]]->move(move_to, temp._board, temp);
   
    //need to change color to see if the one that has checked is still in check
    temp.which_turn = !(temp.which_turn);
    bool check = temp.check_Shach(move_to);
    temp.which_turn = !(temp.which_turn);

    if (check == true)
        return Cant_Make_Self_Check;
    int status = this->_board[Con[move_to[1]]][Con[move_to[0]]]->move(move_to, _board, *this);
    //if there was a valid move , check if i made a Shach
    if (status == Has_Checked || status == Vaild_Move || status == CheckMate || status == enPassent || status == castle || status == promote)
        check = check_Shach(move_to);
    //he made shach !!! 
    if (check == true)
        status = Has_Checked;

    //if the move was valid it is the next player turn
    if (status == Has_Checked || status == Vaild_Move || status == CheckMate || status == enPassent || status == castle || status == promote)
    {
        this->setWhosTurn(!(this->WhoTurn()));
    }
    return status;
}
/*
* function will change whos turn is it
* input:if it is white's turn or not
* output:none
*/
void Board::setWhosTurn(const bool set)
{
    this->which_turn = set;
}


/*
* function will check if the current player did a check
* input:the string where to move
* output: wether or not the user made chess 
*/
bool Board::check_Shach(const std::string to_move)
{
    bool isWhite = false;

    //to Know What is my king 
    if (this->which_turn == 1)
        isWhite = true;

    //make a int kingPlace
    int KingPlace[2] = { 0 };

    //run all over the board and get the other player KingPlace
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //if i am black player and i wont to get White King
            if (_board[i][j]->return_type() == "K" && isWhite == false)
                KingPlace[0] = i, KingPlace[1] = j;
            else if (_board[i][j]->return_type() == "k" && isWhite == true)
                KingPlace[0] = i, KingPlace[1] = j;


        }
    }


    //KingPlace[1] - Convert, KingPlace[0] - add 1


    //run all over the board and check if i can eat his king 
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            //white or black player
            if (isWhite == true)
            {
                //not no piece and its a white player
                if (_board[i][j]->return_type() != "#" && _board[i][j]->get_color() == 1)
                {
                    //get it by stirng
                    std::string ForMove = toChar(j) + IntChar(i) + toChar(KingPlace[1]) + IntChar(KingPlace[0]);

                    //source = my player, dest = his king 


                    //get the check
                    int RealCheck = _board[i][j]->isValid(ForMove, _board, *this);

                    //if he can move the other player is in chess
                    if (RealCheck == 0 || RealCheck == 1 || RealCheck == 8)
                        return true;
                }
            }

            else if (isWhite == false)
            {
                //not no piece and its a white player
                if (_board[i][j]->return_type() != "#" && _board[i][j]->get_color() == 0)
                {
                    //get it by stirng
                    std::string ForMove = toChar(j) + IntChar(i) + toChar(KingPlace[1]) + IntChar(KingPlace[0]);

                    //source = my player, dest = his king 


                    //get the check
                    int RealCheck = _board[i][j]->isValid(ForMove, _board, *this);

                    //if he can move the other player is in chess
                    if (RealCheck == 0 || RealCheck == 1 || RealCheck == 8)
                        return true;
                }
            }
        }
    }

    return false;
}
//function will convert from int to char
std::string Board::toChar(int num)
{

    //return it by the num
    if (num == 0)
        return "a";
    if (num == 1)
        return "b";
    if (num == 2)
        return "c";
    if (num == 3)
        return "d";
    if (num == 4)
        return "e";
    if (num == 5)
        return "f";
    if (num == 6)
        return "g";
    if (num == 7)
        return "h";

    return "a";
}
//function will convert from int to char
std::string Board::IntChar(int num)
{
    //return it by the num
    if (num == 0)
        return "1";
    if (num == 1)
        return "2";
    if (num == 2)
        return "3";
    if (num == 3)
        return "4";
    if (num == 4)
        return "5";
    if (num == 5)
        return "6";
    if (num == 6)
        return "7";
    if (num == 7)
        return "8";
    return "0";
}
/*
* opertaot =, function will get a board object and then
*/
Board& Board::operator=(Board& other)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->_board[i][j] = other._board[i][j]->return_allocated(other._board[i][j]->get_file(), other._board[i][j]->get_rank(), other._board[i][j]->get_color(), other._board[i][j]->get_first_move());
        }
    }
    this->_P1 = new Player(other._P1->_isWhite);
    this->_P2 = new Player(other._P2->_isWhite);
    this->which_turn = other.which_turn;
    return *this;


}
//copy constructot
Board::Board(Board& other)
{
    *this = other;
}

