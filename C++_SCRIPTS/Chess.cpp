#include <iostream>
#include <windows.h>
#include <color.hpp>
#include <climits>
#include <windows.h> 
#define INVALID -1
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
int piece_row = 0;
int piece_col = 0;
int dest_row = 0;
int dest_col = 0;
bool white_king_checked = false;
bool black_king_checked = false;
Piece king_cheking_piece[16];
int n = 0;

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
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
                    if(row == 8 || col == 8){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;

        case 7:
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
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
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
                    if(((row == 6 || row == 10) && (col == 7 || col == 9)) || ((row == 7 || row == 9) && (col == 6 || col == 10))){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;

        case 6:
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
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
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
                    if(row == col || col == (16-row)){
                        moveset[row][col] = true;
                    }else{
                        moveset[row][col] = false;
                    }
                }
            } 
            return moveset;

        case 5:
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
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
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
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
            
            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
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

        default:
            break;
        }

    }else{

        if(row == 1 || row == 6){
            // PEDINA
            if(board.grid[row][col].color == black){

                for(int row = 0; row < 17; row++){
                    for(int col = 0; col < 17; col++){
                        if((row == 7 || row == 6) && col == 8){
                            moveset[row][col] = true;
                        }else{
                            moveset[row][col] = false;
                        }
                    }
                }

            }else{

                for(int row = 0; row < 17; row++){
                    for(int col = 0; col < 17; col++){
                        if((row == 9 || row == 10) && col == 8){
                            moveset[row][col] = true;
                        }else{
                            moveset[row][col] = false;
                        }
                    }
                }

            }
            
            return moveset;
        }else{

            for(int row = 0; row < 17; row++){
                for(int col = 0; col < 17; col++){
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

            if(row < 2){
                board.grid[row][col].color = black;
            }
            if(row > 5){
                board.grid[row][col].color = white;
            }
            if(row > 1 && row < 6){
                board.grid[row][col].color = red;
            }
            board.grid[row][col].name = nameset(row, col);
            board.grid[row][col].moveset = moveset(row, col);
            board.grid[row][col].row = row;
            board.grid[row][col].col = col;

        }

    }
    board.turn = 0;

}

bool valid_move(int row, int col, Piece piece){

    /**
    if(piece.row > row && piece.col > col){
        if(piece.moveset[8 + (piece.row - row)][8 + (piece.col - col)]){
            return true;

        }else{
            return false;
        }

    }else{
        if(piece.row > row){
            if(piece.moveset[8 + (piece.row - row)][8 - (col - piece.col)]){
                return true;
            }else{
                return false;
            }
        }else{
            if(piece.col > col){
                if(piece.moveset[8 - (row - piece.row)][8 + (piece.col - col)]){
                    return true;
                }else{
                    return false;
                }

            }else{
                if(piece.moveset[8 - (row - piece.row)][8 - (col - piece.col)]){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }*/
    
    // diagonale superiore sinistra
    if(piece.row > row && piece.col > col){
        if(piece.moveset[8 + (piece.row - row)][8 + (piece.col - col)]){
            int temp_col = piece.col-1;
            for(int temp_row = piece.row-1; temp_row >= row; temp_row--){
                if(temp_col < col){
                    break;
                }
                if(board.grid[temp_row][temp_col].color != red){
                    return false;
                }
                temp_col--;
            }
        }else{
            return false;
        }
    }
    
    // diagonale inferiore destra
    if(piece.row < row && piece.col < col){
        if(piece.moveset[8 - (row - piece.row)][8 - (col - piece.col)]){
            int temp_col = piece.col+1;
            for(int temp_row = piece.row+1; temp_row <= row; temp_row++){
                if(temp_col < col){
                    break;
                }
                if(board.grid[temp_row][temp_col].color != red){
                    return false;
                }
                temp_col++;
            }
        }else{
            return false;
        }
    }

    // diagonale superiore destra
    if(piece.row > row && piece.col < col){
        if(piece.moveset[8 + (piece.row - row)][8 - (col - piece.col)]){
            int temp_col = piece.col+1;
            for(int temp_row = piece.row-1; temp_row >= row; temp_row--){
                if(temp_col > col){
                    break;
                }
                if(board.grid[temp_row][temp_col].color != red){
                    return false;
                }
                temp_col++;
            }
        }else{
            return false;
        } 
    }

    // diagonale inferiore sinistra
    if(piece.row < row && piece.col > col){
        if(piece.moveset[8 - (row - piece.row)][8 + (piece.col - col)]){   
            int temp_col = piece.col-1;
            for(int temp_row = piece.row+1; temp_row <= row; temp_row++){
                if(temp_col < col){
                    break;
                }
                if(board.grid[temp_row][temp_col].color != red){
                    return false;
                }
                temp_col--;
            }
        }else{
            return false;
        }
    }

    // colonna orizzonatale
    if(piece.row == row){
        // destra
        if(piece.col < col){
            if(piece.moveset[8][8 + (col - piece.col)]){
                for(int temp_col = piece.col+1; temp_col <= col; temp_col++){
                    if(board.grid[piece.row][temp_col].color != red){
                        return false;
                    }
                }
            }else{
                return false;
            }
        }else{
        // sinistra    
            if(piece.moveset[8][8 - (piece.col - col)]){
                for(int temp_col = piece.col-1; temp_col >= col; temp_col--){
                    if(board.grid[piece.row][temp_col].color != red){
                        return false;
                    }
                }    
            
            }else{
                return false;
            }
        }
    }

    // colonna verticale
    if(piece.col == col){
        // inferiore
        if(piece.row < row){
            if(piece.moveset[8 - (row - piece.row)][8]){
                for(int temp_row = piece.row+1; temp_row <= row; temp_row++){
                    if(board.grid[temp_row][piece.col].color != red){
                        return false;
                    }
                }
            }else{
                return false;
            }
        }else{
        // superiore
            if(piece.moveset[8 + (piece.row - row)][8]){

                for(int temp_row = piece.row-1; temp_row >= row; temp_row--){
                    if(board.grid[temp_row][piece.col].color != red){
                        return false;
                    }
                }
                
            }else{
                return false;
            }
        }
    }

    return true;
}

void make_move(int row, int col, Piece piece){

    if((board.turn == 1 && piece.color ==  white) || (board.turn == 0 && piece.color == black)){
        cout << "\nMOVE NOT VALID\n";
        return;
    }
    if(piece.row > row && piece.col > col){

        if(piece.moveset[8 + (piece.row - row)][8 + (piece.col - col)]){
            board.grid[row][col].col = col;
            board.grid[row][col].row = row;
            board.grid[row][col].color = piece.color;
            board.grid[row][col].moveset = piece.moveset;
            board.grid[row][col].name = piece.name;
            board.grid[piece.row][piece.col].name = " void ";
            board.grid[piece.row][piece.col].color = red;
        }else{
            cout << "\nMOVE NOT VALID\n";
        }
    
    }else{

        if(piece.row > row){

            if(piece.moveset[8 + (piece.row - row)][8 - (col - piece.col)]){
                board.grid[row][col].col = col;
                board.grid[row][col].row = row;
                board.grid[row][col].color = piece.color;
                board.grid[row][col].moveset = piece.moveset;
                board.grid[row][col].name = piece.name;
                board.grid[piece.row][piece.col].name = " void ";
                board.grid[piece.row][piece.col].color = red;
            }else{
                cout << "\nMOVE NOT VALID\n";
            }

        }else{

            if(piece.col > col){

                if(piece.moveset[8 - (row - piece.row)][8 + (piece.col - col)]){
                    board.grid[row][col].col = col;
                    board.grid[row][col].row = row;
                    board.grid[row][col].color = piece.color;
                    board.grid[row][col].moveset = piece.moveset;
                    board.grid[row][col].name = piece.name;
                    board.grid[piece.row][piece.col].name = " void ";
                    board.grid[piece.row][piece.col].color = red;
                }else{
                    cout << "\nMOVE NOT VALID\n";
                }

            }else{

                if(piece.moveset[8 - (row - piece.row)][8 - (col - piece.col)]){
                    board.grid[row][col].col = col;
                    board.grid[row][col].row = row;
                    board.grid[row][col].color = piece.color;
                    board.grid[row][col].moveset = piece.moveset;
                    board.grid[row][col].name = piece.name;
                    board.grid[piece.row][piece.col].name = " void ";
                    board.grid[piece.row][piece.col].color = red;
                }else{
                    cout << "\nMOVE NOT VALID\n";
                }

            }
            
        }

    }
    
    
}

// Funzione di debug, inutile per il funzionamento del programma.
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

    cout << "\n";
    cout << "    A     B     C     D     E     F     G     H\n";

    for(int row = 0; row < 8; row++){
        
        cout << row+1 << " ";
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

            if(col == 7){
                printf("\n");
            }
        }
    }

    cout << "\n";

}

void print_board_with_moveset(Piece piece){
    cout << "\n";
    cout << "    A     B     C     D     E     F     G     H\n";
    for(int row = 0; row < 8; row++){
        cout << row+1 << " ";
        for(int col = 0; col < 8; col++){

            if(valid_move(row, col, piece)){

                switch (board.grid[row][col].color)
                {
                case black:
                    cout << color::rize(board.grid[row][col].name, "Black", "Yellow" );
                    break;
                
                case white:
                    cout << color::rize(board.grid[row][col].name, "White", "Yellow" );
                    break;

                case red:
                    cout << color::rize(board.grid[row][col].name, "Red", "Yellow" );
                    break;

                default:
                    break;
                }
                
            }else{

                switch (board.grid[row][col].color)
                {
                case black:
                    cout << color::rize(board.grid[row][col].name, "Black", "Blue" );
                    break;
                
                case white:
                    cout << color::rize(board.grid[row][col].name, "White", "Blue" );
                    break;

                case red:
                    cout << color::rize(board.grid[row][col].name, "Red", "Blue" );
                    break;

                default:
                    break;
                }

            }

            if(col == 7){
                printf("\n");
            }
        }
    }
    cout << "\n";
}

bool king_under_check(player_color color){
    
    int king_row = 0;
    int king_col = 0;
    for(king_row = 0; king_row < 8; king_row++){
        for(king_col = 0; king_col < 8; king_col++){
            if(board.grid[king_row][king_col].name == " king " && board.grid[king_row][king_col].color == color){
                goto endFor;
            }
        }
    }
    endFor:

    /** ESEMPIO DI LINEE CONTROLLATE PER CHECK SUL RE' (RE = K)
     * 
     *  | CONTROLLO PER TORRE-ALFIERE-REGINA-RE-PEDINA | 
     * 
     *       A  B  C  D  E  F  G  H
     * 
     *  1    0  -  -  -  0  -  -  -
     *  2    -  0  -  -  0  -  -  0 
     *  3    -  -  0  -  0  -  0  - 
     *  4    -  -  -  0  0  0  -  - 
     *  5    0  0  0  0  K  0  0  0 
     *  6    -  -  -  0  0  0  -  - 
     *  7    -  -  0  -  0  -  0  -
     *  8    -  0  -  -  0  -  -  0
     *  
     *  | CONTROLLO PER CAVALLO |
     *  
     *       A  B  C  D  E  F  G  H
     * 
     *  1    -  -  -  -  -  -  -  -
     *  2    -  -  -  -  -  -  -  - 
     *  3    -  -  -  0  -  0  -  - 
     *  4    -  -  0  -  -  -  0  - 
     *  5    -  -  -  -  K  -  -  - 
     *  6    -  -  0  -  -  -  0  - 
     *  7    -  -  -  0  -  0  -  -
     *  8    -  -  -  -  -  -  -  -     
     *    
    */
    
    // Controllo colonna superiore.
    for(int row = king_row+1; row < 8; row++){
        if(board.grid[row][king_col].color == color){
            break;
        }
        if(board.grid[row][king_col].color != color && board.grid[row][king_col].color != red){
            if(valid_move(king_row, king_col, board.grid[row][king_col])){
                //king_cheking_piece[n] = board.grid[row][king_col];
                return true;
            }
        }
    }
    
    // Controllo colonna inferiore.
    for(int row = king_row-1; row >= 0; row--){
        if(board.grid[row][king_col].color == color){
            break;
        }
        if(board.grid[row][king_col].color != color && board.grid[row][king_col].color != red){
            if(valid_move(king_row, king_col, board.grid[row][king_col])){
                //king_cheking_piece[n] = board.grid[row][king_col];
                return true;
            }
        }
    }
    
    
    // Controllo riga destra.
    for(int col = king_col+1; col < 8; col++){
        if(board.grid[king_row][col].color == color){
            break;
        }
        if(board.grid[king_row][col].color != color && board.grid[king_row][col].color != red){
            if(valid_move(king_row, king_col, board.grid[king_row][col])){
                //king_cheking_piece[n] = board.grid[king_row][col];
                return true;
            }
        }
    }

    // Controllo riga sinistra.
    for(int col = king_col-1; col >= 0; col--){
        if(board.grid[king_row][col].color == color){
            break;
        }
        if(board.grid[king_row][col].color != color && board.grid[king_row][col].color != red){
            if(valid_move(king_row, king_col, board.grid[king_row][col])){
                //king_cheking_piece[n] = board.grid[king_row][col];
                return true;
            }
        }
    }
    
    // Controllo per il cavallo
    if(king_row > 0 && king_col > 0){
        if(king_row > 1){
            if(board.grid[king_row-2][king_col-1].color != color && board.grid[king_row-2][king_col-1].color != red){
                if(valid_move(king_row, king_col, board.grid[king_row-2][king_col-1])){
                    //king_cheking_piece[n] = board.grid[king_row-2][king_col-1];
                    return true;
                }
            }
        }
        if(king_col > 1){
            if(board.grid[king_row-1][king_col-2].color != color && board.grid[king_row-1][king_col-2].color != red){
                if(valid_move(king_row, king_col, board.grid[king_row-1][king_col-2])){
                    //king_cheking_piece[n] = board.grid[king_row-1][king_col-2];
                    return true;
                }
            }
        }
    }
    if(king_row < 7 && king_col < 7){
        if(king_row < 6){
            if(board.grid[king_row+2][king_col+1].color != color && board.grid[king_row+2][king_col+1].color != red){
                if(valid_move(king_row, king_col, board.grid[king_row+2][king_col+1])){
                    //king_cheking_piece[n] = board.grid[king_row+2][king_col+1];
                    return true;
                }
            }
        }
        if(king_col < 6){
            if(board.grid[king_row+1][king_col+2].color != color && board.grid[king_row+1][king_col+2].color != red){
                if(valid_move(king_row, king_col, board.grid[king_row-1][king_col-2])){
                    //king_cheking_piece[n] = board.grid[king_row+1][king_col+2];
                    return true;
                }
            }
        }
    }
    return false;
}

void game_turn(player_color color, int dest_row, int dest_col, int piece_row, int piece_col){
    
    cls();

    // Controllo che il pezzo che sto spostando non scopra il rè ad uno scacco
    // Controllo se sto fancendo uno spostamento "attraversando" illeagalmente un altro pezzo (unica eccezzione cavallo).
    make_move(dest_row, dest_col, board.grid[piece_row][piece_col]);

    print_board(board.grid);

}

int controlled_input_integer(){
    int temp;
    cin >> temp;
    while (cin.fail() || temp < 1 || temp > 8)
    {
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << " Puoi solo inserire numeri interi da 1 a 8.\n";
        cout << " Ritenta.\n";
        cin >> temp;
    }
    return temp;
}

int controlled_input_char(){
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
    return INVALID;
}

/**
 * LOGICA DI CONTROLLO PER I TURNI:
 * 1) Controllo se ho selezionato un pezzo del colore corretto. OK
 * 2) Controllo se il proprio re è sotto scacco -> posso muovere solo i pezzi che possono "coprire" o "annullare" lo scacco.
 * 3) Controllo se la mossa che ho inserito è valida per quel pezzo. OK
 * 4) Controllo se la mossa che ho inserito scopra il proprio re ad uno scacco.
*/

int white_turn(){

    do{
        cout << " <BIANCO> Inserisci il pezzo da spostare. \n";
        cout << " <BIANCO> Inserisci la RIGA ( NUMERO 0 -> 7 ) ( -1 per forfait ) : ";
        piece_row = controlled_input_integer();
        if(piece_row == INVALID){
            cout << " HA VINTO IL NERO PER FORFAIT! ";
            return 0;
        }
        cout << " <BIANCO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
        piece_col = controlled_input_char();
    }while(board.grid[piece_row-1][piece_col].color != white);

    print_board_with_moveset(board.grid[piece_row-1][piece_col]);

    do{
        cout << " <BIANCO> Inserisci la nuova posizione del pezzo da spostare. \n";
        cout << " <BIANCO> Inserisci la RIGA ( NUMERO 0 -> 7 ) : ";
        dest_row = controlled_input_integer();
        cout << " <BIANCO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
        dest_col = controlled_input_char();
    }while(board.grid[dest_row-1][dest_col].color == white || board.grid[dest_row-1][dest_col].name == " king " || !valid_move(dest_row-1, dest_col, board.grid[piece_row-1][piece_col]));

    game_turn(white, dest_row-1, dest_col, piece_row-1, piece_col);
    board.turn = 1;
    return 1;
}

int black_turn(){

    do{
        cout << " <NERO> Inserisci il pezzo da spostare. \n";
        cout << " <NERO> Inserisci la RIGA ( NUMERO 0 -> 7 ) ( -1 per forfait ) : ";
        piece_row = controlled_input_integer();
        if(piece_row == INVALID){
            cout << " HA VINTO IL BIANCO PER FORFAIT! ";
            return 0;
        }
        cout << " <NERO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
        piece_col = controlled_input_char();
    }while(board.grid[piece_row-1][piece_col].color != black);

    print_board_with_moveset(board.grid[piece_row-1][piece_col]);

    do{
        cout << " <NERO> Inserisci la nuova posizione del pezzo da spostare. \n";
        cout << " <NERO> Inserisci la RIGA ( NUMERO 0 -> 7 ) : ";
        dest_row = controlled_input_integer();
        cout << " <NERO> Inserisci la COLONNA ( CARATTERE A -> H ) : ";
        dest_col = controlled_input_char();
    }while(board.grid[dest_row-1][dest_col].color == black || board.grid[dest_row-1][dest_col].name == " king " || !valid_move(dest_row-1, dest_col, board.grid[piece_row-1][piece_col]));

    game_turn(black, dest_row-1, dest_col, piece_row-1, piece_col);
    board.turn = 0;
    return 1;

}

int main()
{
    init_board();
    print_board(board.grid);

    while(1){

        if(board.turn == 0){

            if(king_under_check(white)){
                cout << " IL RE E' SOTTO SCACCO! DIFENDILO! " << endl;
            }
            if(white_turn() == 0){
                return 0;
            }

        }else{

            if(king_under_check(black)){
                cout << " IL RE E' SOTTO SCACCO! DIFENDILO! " << endl;
            }
            if(black_turn() == 0){
                return 0;
            }

        }
        
    }    

    return 0;
}