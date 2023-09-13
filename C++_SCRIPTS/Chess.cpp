#include <iostream>
#define INVALID -1;
using namespace std;


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
                        moveset[col][row] = true;
                    }else{
                        moveset[col][row] = false;
                    }
                }
            } 
            return moveset;
        }else{

            for(int col = 0; col < 17; col++){
                for(int row = 0; row < 17; row++){
                    moveset[col][row] = false;
                }
            }
            return moveset; 

        }
                

    }

}

void print_moveset(bool** mat){
    for(int col = 0; col < 17; col++){
        for(int row = 0; row < 17; row++){
            printf("%d ", mat[row][col]);
            if(row == 16){
                printf("\n");
            }
        }
    } 
}

class Piece{
    public:
        string name;
        bool** moveset;
};

class Board{
    public:
        Piece grid[8][8];
        int turn;
};

int main()
{
    
    Piece king;
    king.name = "king";
    king.moveset = moveset(0,3);

    Piece player_1[16];
    player_1[0] = king;
    //printf("%s\n", player_1[0].name);
    print_moveset(player_1[0].moveset);
    
    
    return 0;

}