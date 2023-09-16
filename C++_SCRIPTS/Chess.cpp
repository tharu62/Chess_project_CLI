#include <iostream>
#include <windows.h>
#include <color.hpp>
#define INVALID -1;
using namespace std;

enum player_color {white = 0, black = 1, red = 2};

class Piece{
    public:
        player_color color;
        string name;
        int row;
        int col;
        bool** moveset;
};

class Board{
    public:
        Piece grid[8][8];
        int turn;
};

Board board;
Piece player_1[16];
Piece player_2[16];

bool** moveset(int row, int col){

    bool** moveset = new bool*[17];
    for (int i = 0; i < 17; ++i) {
        moveset[i] = new bool[17];
    }
 
    if(row == 0 || row == 7){
        switch (col)
        {
        // TORRE    
        case 0:
            
            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    if(row == 8 || col == 8){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;

        // CAVALLO
        case 1:
            
            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    if(((row == 6 || row == 10) && (col == 7 || col == 9)) || ((row == 7 || row == 9) && (col == 6 || col == 10))){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;

        // ALFIERE
        case 2:
            
            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    if(row == col || col == (16-row)){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;

        // RE
        case 3:
            
            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    if((row > 6 && row < 10) && (col > 6 && col < 10)){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;

        // REGINA
        case 4:
            
            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    if(row == 8 || col == 8){
                        moveset[row][col] = true;
                    }else{
                        if(row == col || col == (16-row)){
                            moveset[row][col] = true;
                        }else{
                            
                            if((row > 6 && row < 10) && (col > 6 && col < 10)){
                                moveset[row][col] = true;
                            }else{
                                moveset[row][col] = false;
                            }

                        }
                    }
                }
            } 
            return moveset;
            break;

        default:
            break;
        }

    }else{

        if(row == 1 || col == 6){
            // PEDINA
            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    if((row == 7 || row == 6) && col == 8){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;
        }else{

            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    moveset[row][col] = false;
                }
            }
            return moveset; 

        }
                

    }

}

string nameset(int row, int col){

    if(row == 0 || row == 7){

        switch(col)
        {
        case 0:

            return " rook ";

        case 1:

            return "horse ";

        case 2:

            return "bishop";

        case 3:

            return " king ";
        
        case 4:

            return "queen ";

        case 5:

            return "bishop";

        case 6:

            return " horse";

        case 7:

            return " rook ";    

        default:
            break;
        }

    }else{

        if(row == 1 || row == 6){
            return " pawn ";
        }else{
            return " void ";
        }
    }
    

}

void init_board(){

    for(int row = 0; row < 8; row++){

        for(int col = 0; col < 8; col++){

            board.grid[row][col].name = nameset(row, col);
            board.grid[row][col].moveset = moveset(row, col);
            board.grid[row][col].row = row;
            board.grid[row][col].col = col;
            if(row < 2){
                board.grid[row][col].color = black;
            }
            if(row > 5){
                board.grid[row][col].color = white;
            }
            if(row > 1 && row < 6){
                board.grid[row][col].color = red;
            }

        }

    }

}

void make_a_move(int row, int col, Piece piece){

    if(piece.row > row && piece.col > col){

        if(piece.moveset[8 + (piece.row - row)][8 + (piece.col - col)]){
            board.grid[row][col] = piece;
            board.grid[piece.row][piece.col].name = " void ";
            board.grid[piece.row][piece.col].color = red;
        }else{
            cout << "\nMOVE NOT VALID\n";
        }
    
    }else{

        if(piece.row > row){

            if(piece.moveset[8 + (piece.row - row)][8 - (col - piece.col)]){
                board.grid[row][col] = piece;
                board.grid[piece.row][piece.col].name = " void ";
                board.grid[piece.row][piece.col].color = red;
            }else{
                cout << "\nMOVE NOT VALID\n";
            }

        }else{

            if(piece.col > col){

                if(piece.moveset[8 - (row - piece.row)][8 + (piece.col - col)]){
                    board.grid[row][col] = piece;
                    board.grid[piece.row][piece.col].name = " void ";
                    board.grid[piece.row][piece.col].color = red;
                }else{
                    cout << "\nMOVE NOT VALID\n";
                }

            }else{

                if(piece.moveset[8 - (row - piece.row)][8 - (col - piece.col)]){
                    board.grid[row][col] = piece;
                    board.grid[piece.row][piece.col].name = " void ";
                    board.grid[piece.row][piece.col].color = red;
                }else{
                    cout << "\nMOVE NOT VALID\n";
                }

            }
            
        }

    }
    
    
}

void print_moveset(bool** mat){
    
    for(int row = 0; row < 17; row++){    
        for(int col = 0; col < 17; col++){   
            printf("%d ", mat[row][col]);
            if(col == 16){
                printf("\n");
            }
        }
    } 
}

void print_board(Piece mat[8][8]){

    for(int row = 0; row < 8; row++){
    
        for(int col = 0; col < 8; col++){
            /**
            if(col < 2){
                auto const& colorized_text = color::rize( mat[row][col].name, "Black", "Blue" );
                cout << colorized_text;
                mat[row][col].color = black;
            }
            if(col > 5){
                auto const& colorized_text = color::rize( mat[row][col].name, "White", "Blue" );
                cout << colorized_text;
                mat[row][col].color = white;
            }
            if(col > 1 && col < 6){
                auto const& colorized_text = color::rize( mat[row][col].name, "Red", "Blue" );
                cout << colorized_text;
            }
            */

            switch (mat[row][col].color)
            {
            case black:
                cout << color::rize( mat[row][col].name, "Black", "Blue" );
                break;
            
            case white:
                cout << color::rize( mat[row][col].name, "White", "Blue" );
                break;

            case red:
                cout << color::rize( mat[row][col].name, "Red", "Blue" );
                break;

            default:
                break;
            }

            //cout << mat[row][col].name;
            if(col == 7){
                printf("\n");
            }
        }
    }

}

void game_loop(){

}

int main()
{
    init_board();
    print_board(board.grid);
    make_a_move(2, 2, board.grid[1][2]);
    cout << "\n";
    print_board(board.grid);
    
    return 0;
}