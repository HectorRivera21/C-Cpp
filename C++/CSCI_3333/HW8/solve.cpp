#include "vertex.h"
#include "solve.h"


string solve(string maze){
    int row = 0, col = 0;
    
    for(char x : maze){
        if(x == ' ')
        {
            
        }

        if(x == '\n'){
            row++;
            col = 0;
        }else{
            col++;
        }
    }

}