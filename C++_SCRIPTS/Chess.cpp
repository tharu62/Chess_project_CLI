#include <iostream>
using namespace std;


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