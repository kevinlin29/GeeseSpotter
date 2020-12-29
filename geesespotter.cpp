//
// Created by Kevin Lin on 2020-10-25.
/*
 * check each possible case
 * edges and walls
 */
//

#include "geesespotter_lib.h"

char * createBoard(std::size_t xdim, std::size_t ydim){
    char *arr = new char[xdim*ydim];
    for(int i = 0 ; i < xdim*ydim; i++){
        arr[i] = 0x00;
    }
    return arr;
}
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    int arr[ydim+2][xdim+2], count = 0;
    for(int i = 1; i < ydim+1; i++){
        for(int j = 1; j < xdim+1; j++){
            arr[i][j] = board[count];
            count++;
        }
    }
    int direction[3] = {0,1,-1};
    for(int i = 1; i < ydim+1; i++){
        for(int j = 1; j < xdim+1; j++){
            if(arr[i][j] == 0){
                for ( int a = 0; a < 3; a++ )
                    for ( int b = 0; b < 3; b++ )
                        if ( arr[i+direction[a]][j+direction[b]] == 9 )
                            arr[i][j] += 1;
            }
        }
    }
    count = 0;
    for(int i = 1; i < ydim+1; i++){
        for(int j = 1; j < xdim+1; j++){
            board[count] = arr[i][j];
            count++;
        }
    }
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    for(int i = 0 ; i < xdim*ydim; i++){
        board[i] += 0x20;
    }
}
void cleanBoard(char * board){
    delete[] board;
    board = nullptr;
}
void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    for( int i = 0; i < xdim*ydim; i++){
        //next line
        if((i % xdim) == 0 && i != 0){
            std::cout<<std::endl;
        }
        if(board[i] & markedBit()){
            std::cout<< 'M';
        }else if(board[i] & hiddenBit()){
            std::cout<< '*';
        }else{
            std::cout<< (int) board[i];
        }
    }
    std::cout<<std::endl;
}
int revSurround(char * board, std::size_t xdim, std::size_t xloc, std::size_t yloc){
    int loc = xdim*yloc + xloc;
    if((board[loc] & markedBit())==markedBit()){
        return 1;
    }
    board[loc] = board[loc]&valueMask();
    return 0;

}
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int loc = xdim * (yloc) + xloc;
    if ((board[loc] & markedBit()) == markedBit()) {
        return 1;
    } else if ((board[loc] & valueMask()) == board[loc]) {
        return 2;
    } else if ((board[loc] & valueMask()) == 9) {
        board[loc] = board[loc] & valueMask();
        return 9;
    }
    //if value revealed is 0, then expand towards the sides
    board[loc] = board[loc] & valueMask();
    if (board[loc] == 0) {
        if ((xloc != 0))
            revSurround(board, xdim,  xloc - 1, yloc);
        if ((xloc != (xdim - 1)))
            revSurround(board, xdim, xloc + 1, yloc);
        if (yloc != 0)
            revSurround(board, xdim,  xloc, yloc - 1);
        if (yloc != (ydim - 1))
            revSurround(board, xdim,  xloc, yloc + 1);
        if ((xloc != 0) && (yloc != 0))
            revSurround(board, xdim,xloc - 1, yloc - 1);
        if ((xloc != 0) && (yloc != (ydim - 1)))
            revSurround(board, xdim, xloc - 1, yloc + 1);
        if ((xloc != (xdim - 1)) && (yloc != (ydim - 1)))
            revSurround(board, xdim, xloc + 1, yloc + 1);
        if ((xloc != (xdim - 1)) && (yloc != 0))
            revSurround(board, xdim, xloc + 1, yloc - 1);
    }
    return 0;
}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int loc = xdim*(yloc) + xloc;
    if((board[loc] & 0x0F) == board[loc])
        return 2;
    if((board[loc] & markedBit()) != markedBit()){
        board[loc] += markedBit();
    }else{
        board[loc] -= markedBit();
    }
    return 0;
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    for(int i =0; i< xdim*ydim; i++){
        if (((board[i] & valueMask())!= 9 ) && ((board[i]&valueMask())!= board[i])){
            return false;
        }
    }
    return true;
}



