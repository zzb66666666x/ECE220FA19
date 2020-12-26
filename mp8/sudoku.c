#include "sudoku.h"

/*-------------------------------------------------------------------------------------------------
   Start here to work on your MP
  -------------------------------------------------------------------------------------------------*/
/* Intro
This is where the major service functions get implememted.
The algorithm is recursion and back-tracking.

Brief description of algorithm:
bool solve_sudoku(int sudoku[9][9]) {  
	int i, j;  
 	if (all cells are assigned by numbers) {    
 		return true;   
	}  
 	else {     
		find a non-filled cell (i, j);    				//find one blank to be filled
	}     
 	for (int num = 1; num <= 9; num++) {   				//try 1-9
  		if (cell (i, j) can be filled with num) {		//if can be filled   
     		sudoku[i][j] <- num;      					//store value to the array
  			if (solve_sudoku(sudoku)) { 				//see if the problem get solved: yes--return; no--
        		return True;       						//if the program doesn't enter here, it means that 
			}      
 			sudoku[i][j] <- non-filled;    
		}   
	}  
	return False;  										//cannot solve the problem
}

functions:
is_val_valid: use is_val_in_row, is_val_in_col, is_val_in_3x3_zone to check if the value is possible.
solve_sudoku: implement the recursion to try solving the sudoku.
print_sudoku: print out the sudoku
parse_sudoku: read the sudoku from stream.
*/

/* You are free to declare any private functions if needed. */

/* Function: is_val_in_row
   Return true if "val" already existed in ith row of array sudoku. */
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  /* BEG TODO */
  for (int index = 0; index < 9; index++)
	{
		if (sudoku[i][index] == val){			//check if there are some repeated elements
			return 1;
		} 
	}
  return 0;
  /* END TODO */
}

/* Function: is_val_in_col
   Return true if "val" already existed in jth column of array sudoku. */
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  /* BEG TODO */
  for (int index = 0; index < 9; index++)
	{
		if (sudoku[index][j] == val){			//check if there are some repeated elements
			return 1;
		}
	}
  return 0;
  /* END TODO */
}

/* Function: is_val_in_3x3_zone
   Return true if val already existed in the 3x3 zone corresponding to (i, j) */
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  /* BEG TODO */
	int blocki;
	int blockj;								//If the i is 7, then (7-(7%3))/3 == 2, in the last row of blocks.
	blocki = (i-(i % 3))/3;
	blockj = (j-(j % 3))/3;
	int starti;								//locate the block that should be checked
	int startj;
	starti = 3*blocki;						
	startj = 3*blockj;
	for (int index1 = 0; index1 < 3; index1++)
	{
		for (int index2 = 0; index2 < 3; index2++)
		{
			if (sudoku[starti+index1][startj+index2] == val){
				return 1;					//find repeated elements, return True
			}
		}
	}
  return 0;
  /* END TODO */
}

/* Function: is_val_valid
   Return true if the val is can be filled in the given entry. */
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  /* BEG TODO */
	int flag1;								//whether repeated in one row
	int flag2;								//whether repeated in one col
	int flag3;								//whether repeated in 3x3 block
	flag1 = is_val_in_row(val,i,sudoku);
	flag2 = is_val_in_col(val,j,sudoku);
	flag3 = is_val_in_3x3_zone(val,i,j,sudoku);
	if (flag1 || flag2 || flag3){
		return 0;							//invalid value
	}
	else{
		return 1;							//valid value
	}
  /* END TODO */
}

/* Procedure: solve_sudoku
   Solve the given sudoku instance. */
int solve_sudoku(int sudoku[9][9]) {
	
  /* BEG TODO. */
	int i,j;
	int hasBlank = 0;
	for (int temp1 = 0; temp1 < 9; temp1++)
	{
		for (int temp2 = 0; temp2 < 9; temp2++)
		{
			if (sudoku[temp1][temp2] == 0){			//find a blank space
				i = temp1;
				j = temp2;
				hasBlank = 1;						
				break;								//one blank is sufficient to halt the loop
			}
		}
		if (hasBlank){
			break;
		}
	}
	if (hasBlank == 0){
		return 1;
	}
	else{
		for (int num = 1; num <= 9; num++)
		{
			if (is_val_valid(num,i,j,sudoku)){
				sudoku[i][j] = num;
				if (solve_sudoku(sudoku)){			//recall the function
					return 1;						//begin to close the recursion function
				}
				sudoku[i][j] = 0;					//fail to find the approriate number, try another
			}
		}
		return 0;
	}
  /* END TODO. */
}

/* Procedure: print_sudoku */
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

/* Procedure: parse_sudoku */
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





