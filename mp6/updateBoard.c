/* Intro:
 * This file provides services for the main function.
 * The function "countLiveNeighbor()" counts the alive neighbors for a specific postion. 
 * The function "updateBoard" first make a copy of the board to record what should be changed,
 * 		then it will modify the original board after the iteration according to the record.
 * The function "aliveStable" checks if the system is all dead or remains unchaned for one step.
 * 		This function was realized by executing the updateBoard() once to check if the board will change.
 * The function "countLiveNeighbor()" implements the judgement of the border conditions.
 */

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
{
	int array[8] = {0};	
	int index = row*boardColSize+col;
	int num = 0;
	int pos1,pos2,pos3,pos4,pos6,pos7,pos8,pos9;
	pos1 = index-1-boardColSize;				/* Initialize the positions for a 3x3 square */
	pos2 = index-boardColSize;
	pos3 = index+1-boardColSize;
	pos4 = index-1;
	pos6 = index+1;
	pos7 = index-1+boardColSize;
	pos8 = index+boardColSize;
	pos9 = index+1+boardColSize;
	if (row == 0){
		if (col == 0){							/* upper left */
			array[0] = board[pos6];
			array[1] = board[pos8];
			array[2] = board[pos9];		
		}
		else if(col == boardColSize-1){			/* upper right */
			array[0] = board[pos4];
			array[1] = board[pos7];
			array[2] = board[pos8];
		}
		else{									/* upper middle */
			array[0] = board[pos4];
			array[1] = board[pos6];
			array[2] = board[pos7];
			array[3] = board[pos8];
			array[4] = board[pos9];
		}	
	}
	else if(row == boardRowSize-1){				/* bottom */
		if (col == 0){							/* buttom left */
			array[0] = board[pos2];
			array[1] = board[pos3];
			array[2] = board[pos6];	
		}
		else if(col == boardColSize-1){			/* buttom right */
			array[0] = board[pos1];
			array[1] = board[pos2];
			array[2] = board[pos4];	
		}
		else{									/* bottom middle */
			array[0] = board[pos1];
			array[1] = board[pos2];
			array[2] = board[pos3];
			array[3] = board[pos4];
			array[4] = board[pos6];
		}	
	}
	else{
		if (col == 0){							/* middle of the rows && left edge*/
			array[0] = board[pos2];
			array[1] = board[pos3];
			array[2] = board[pos6];
			array[3] = board[pos8];
			array[4] = board[pos9];
		}
		else if(col == boardColSize-1){			/* right edge */
			array[0] = board[pos1];
			array[1] = board[pos2];
			array[2] = board[pos4];
			array[3] = board[pos7];
			array[4] = board[pos8];
		}
		else{									/* true middle */
			array[0] = board[pos1];
			array[1] = board[pos2];
			array[2] = board[pos3];
			array[3] = board[pos4];
			array[4] = board[pos6];
			array[5] = board[pos7];
			array[6] = board[pos8];
			array[7] = board[pos9];
		}	
	}
	for (int i = 0; i<8; i++){					/* begin to count */
		if (array[i] == 1){
			num++;
		}
	}
	return num;
}



/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) 
{
	int num;
	int index;
	int size = boardRowSize*boardColSize;
	int temp[size];											/* make an copy of the current board */
	for (int i = 0; i < boardRowSize; i++){
		for (int j = 0; j < boardColSize; j++){				/* calculate the num and then initialize the temp */
			num = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
			index = i*boardColSize+j;
			temp[index] = board[index];
			if (board[index] == 0){
				if(num == 3){
					temp[index] = 1;						/* reproduction */	
				}
			}
			else if (board[index] == 1){
				if (num < 2){
					temp[index] = 0;						/* die of loneliness */
				}
				else if((num == 2) || (num == 3)){
					temp[index] = 1;						/* doesn't change */
				}
				else if(num > 3){
					temp[index] = 0;						/* too much population */
				}
			}
		}
	}
	for (int i = 0; i < size; i++){
		board[i] = temp[i];
	}
}



/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize)
{
	int size = boardRowSize*boardColSize;
	int table[size];
	int compare[size];	
	int index;
	int change = 0;											/* no change: value should be 0		has changes: value should be 1 */
	int allZero = 1;										/* all zero elements: value should be 1 */
	int ans;
	for (int i = 0; i < boardRowSize; i++){
		for (int j = 0; j < boardColSize; j++){
			index = i*boardColSize+j;
			table[index] = board[index];
			compare[index] = board[index];
			if (table[index] != 0){
				allZero = 0;								/* detect non-zero elements: allZero = 0 (false) */
			}
 		}
	}
	updateBoard(compare,boardRowSize,boardColSize);			/* update the copy of the board */
	for (int k = 0; k<size; k++){
		if (table[k] != compare[k]){
			change = 1;										/* there are changes */
		}
	}
	if ((change == 0) || allZero){ans = 1;}
	else if(change){ans = 0;}
	return ans;
}

				
				
			

