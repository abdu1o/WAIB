#include "Global.h"
#include "Enums/Enums.h"
#include "Move.h"

class Level1 : public Move
{
private:

    // level board
    vector<vector<Block>> level_board;
    int _rows; 
    int _cols; 

    bool CheckPos(int row, int col) 
    {
        return row >= 0 && row < rows_ && col >= 0 && col < cols_;
    }

public:
    
}
