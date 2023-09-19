#include <iostream>
#include <windows.h>
#include <color.hpp>
#include <climits>
#include <windows.h> 
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

void pos(short C, short R)
{
    COORD xy ;
    xy.X = C ;
    xy.Y = R ;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void cls()
{
    pos(0,0);
    for(int j=0;j<100;j++)
    cout << string(100, ' ');
    pos(0,0);
} 

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
    board.turn = 0;

}

void make_move(int row, int col, Piece piece){

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

    cout << "    A     B     C     D     E     F     G     H\n";

    for(int row = 0; row < 8; row++){
        
        cout << row << " ";
        for(int col = 0; col < 8; col++){

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

void print_board_with_moveset(Piece piece){

}

void game_turn(player_color color, int dest_row, int dest_col, int piece_row, int piece_col){
    
    cls();
    print_board(board.grid);
    //make_move(dest_row, dest_col, board.grid[piece_row][piece_col]);

}

int controlled_input_integer(){
    int temp;
    cin >> temp;
    while (cin.fail())
    {
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << " Puoi solo inserire numeri interi.\n";
        cout << " Ritenta.\n";
        cin >> temp;
    }
    return temp;
}

int controller_input_char(){
    char temp;
    while(1){
        cin >> temp;
        switch (toupper(temp))
        {
        case 'A':
            return 0;
        
        case 'B':
            return 1;

        case 'C':
            return 2;

        case 'D':
            return 3;        

        case 'E':
            return 4;

        case 'F':
            return 5;

        case 'G':
            return 6;

        case 'H':
            return 7;            

        default:
            cout << " Puoi solo inserire caratter tra A e H.\n";
            cout << " Ritenta.\n";
            break;
        }
    }
    return -1;
}

int main()
{
    int piece_row = 0;
    int piece_col = 0;
    int dest_row = 0;
    int dest_col = 0;

    init_board();

    while(1){

        if(board.turn == 0){

            cout << " <BIANCO> Inserisci il pezzo da spostare. \n";
            cout << " <BIANCO> Inserisci la RIGA ( NUMERO 0 -> 7 ) ( -1 per forfait ) : ";
            //cin >> piece_row;
            piece_row = controlled_input_integer();
            if(piece_row == -1){
                cout << " HA VINTO IL NERO PER FORFAIT! ";
                return 0;
            }
            cout << " <BIANCO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
            piece_col = controller_input_char();

            cout << " <BIANCO> Inserisci la nuova posizione del pezzo da spostare. \n";
            cout << " <BIANCO> Inserisci la RIGA ( NUMERO 0 -> 7 ) : ";
            dest_row = controlled_input_integer();
            cout << " <BIANCO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
            dest_col = controller_input_char();

            game_turn(white, dest_row, dest_col, piece_row, piece_col);
            board.turn = 1;

        }else{

            cout << " <NERO> Inserisci il pezzo da spostare. \n";
            cout << " <NERO> Inserisci la RIGA ( NUMERO 0 -> 7 ) ( -1 per forfait ) : ";
            piece_row = controlled_input_integer();
            if(piece_row == -1){
                cout << " HA VINTO IL BIANCO PER FORFAIT! ";
                return 0;
            }
            cout << " <NERO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
            piece_col = controller_input_char();

            cout << " <NERO> Inserisci la nuova posizione del pezzo da spostare. \n";
            cout << " <NERO> Inserisci la RIGA ( NUMERO 0 -> 7 ) : ";
            dest_row = controlled_input_integer();
            cout << " <NERO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
            dest_col =  controller_input_char();

            game_turn(black, dest_row, dest_col, piece_row, piece_col);
            board.turn = 0;
        }
        
    }    

    return 0;
}