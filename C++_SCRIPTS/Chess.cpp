#include <iostream>
#define INVALID -1;
using namespace std;


public bool[][] moveset(int row, int col){
 
    if(row == 0 || row == 7){
        switch (col)
        {
        // TORRE    
        case 0:
            
            bool moveset[17][17];
            for(int col = 0; col < 18; col++){
                for(int row = 0; row < 18; row++){
                    if(row == 8 || col == 8){
                        moveset[col][row] = true;
                    }else{
                        moveset[col][row] = false;
                    }
                }
            } 
            return moveset;

        // CAVALLO
        case 1:
            
            bool moveset[17][17];
            for(int col = 0; col < 18; col++){
                for(int row = 0; row < 18; row++){
                    // todo;
                }
            } 
            return moveset;

        // ALFIERE
        case 2:
            /* code */
            break;

        // RE
        case 3:
            /* code */
            break;

        // REGINA
        case 4:
            /* code */
            break;

        default:
            break;
        }

    }else{

        // PEDINA
        bool moveset[17][17];
        for(int col = 0; col < 18; col++){
            for(int row = 0; row < 18; row++){
                if((row == 7 || row == 6) && col == 8){
                    moveset[col][row] = true;
                }else{
                    moveset[col][row] = false;
                }
            }
        } 
        return moveset;        

    }
}

class Board{
    public:
        int grid[8][8];
        int turn;
};

class Piece{
    public:
        string name;
        bool moveset[8][8];
};

int main()
{
    cout << "ciao";
    return 0;
}