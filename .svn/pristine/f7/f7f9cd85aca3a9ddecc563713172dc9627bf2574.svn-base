#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* Intro
 * This program implements the depth first search by recursively calling the solveMazeDFS()
 * The algorithm is as follows:
 *	1. If (col, row) outside bounds of the maze return false 
 *	2. if (col, row) is not an empty cell return false 
 * 	3. if (col, row) is the end of the maze return true 
 *	4. set (col, row) as part of the solution path in the maze 
 *	5. if (solveMaze(left of (col, row) ) == true) return true 
 *	6. if (solveMaze(right of (col, row) ) == true) return true 
 *	7. if (solveMaze(up of (col, row) ) == true) return true 
 *	8. if (solveMaze(down of (col, row) ) == true) return true 
 *	9. unmark (col, row) as part of solution and mark as visited 10. return false
 *
 * Note about creating the 2D array and assign it to maze->cells:
 * first: create and double pointer and transform void * from malloc to char **, ie. there will be pointers which point to these pointers(stored in heap)
 * The elements here have size: sizeof(char *) because in the future, this memory will be filled with char * pointers, ie. each row of 2D array
 *
 * second: for loop (array[row] = malloc(sizeof(char)*width)), this helps to give specific size of one row, each element in the previous section of memory
 * will then know about the unit size of memory block that it's pointing to
 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
	FILE * fp = fopen(fileName,"r");
	char buffer[100];
	char * temp_buffer = buffer;
	int width,height;
	fscanf(fp,"%d %d\n",&width,&height);					//get width and height
	maze_t * maze = (maze_t *)malloc(sizeof(maze_t));		//give heap
	maze->width = width;
	maze->height = height;
	char ** array = (char **)malloc(sizeof(char *)*height);	//allocate heap space for the 2D array
	for (int i = 0; i < height; i++)
	{
		array[i] = 	(char *)malloc(sizeof(int)*width);		//initialize each pointer to each row
	}	
	maze->cells = array;									//cells points to that 2D array
	//read the rest of the maze
	for (int i = 0; i < height; i++)
	{//each row
		temp_buffer = buffer;
		fgets(buffer,100,fp);								//get things into buffer with size 100 units
		for(int j = 0; j < width; j++)
		{
			if (*temp_buffer == '\n'){
				break;
			}
			if (*temp_buffer == 'S'){						//find start, record position
				maze->startRow = i;
				maze->startColumn = j;
//printf("the starting row is %d\n",i);
//printf("the srarting col is %d\n",j);
			}
			if (*temp_buffer == 'E'){						//find end, record position
				maze->endRow = i;
				maze->endColumn = j;
//printf("the ending row is %d\n",i);
//printf("the ending col is %d\n",j);
			}
			array[i][j] = *temp_buffer;						//store characters
//printf("%c",maze->cells[i][j]);
			temp_buffer++;
		}
//printf("\n");
	}
	fclose(fp);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	//first free the cells
	int height = maze->height;
	for (int i = 0; i < height; i++)
	{//free each row
		free(maze->cells[i]);								//free each row
	}		
	free(maze->cells);							
	free(maze);												//free maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
	int width = maze->width;
	int height = maze->height;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%c",maze->cells[i][j]);					//print out the maze
		}
		printf("\n");
	}	
}

/*
 * solveMazeDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
	//call: solveMazeDFS(maze, maze->startColumn, maze->startRow)
	int width,height;
	static int firstCall = 1;
	width = maze->width;
	height = maze->height;
	if ((col<0)||(col>width-1)||(row<0)||(row>height-1)){
		return 0;											//out of bound
	}
	if ((maze->cells[row][col] != ' ')&&(firstCall == 0)&&(maze->cells[row][col] != 'E')){	//not empty except first call and 'E'
//printf("exit\n");
		return 0;
	}
	if (maze->cells[row][col] == 'E'){
		return 1;
	}
	if (firstCall == 0){									//not first call: set it to '.'
		maze->cells[row][col] = '.';
	}
	firstCall = 0;
//printf("I have change the cells[%d][%d] into %c\n",row,col,maze->cells[row][col]);
	if (solveMazeDFS(maze,col-1,row)){						//left
		return 1;
	}
	if (solveMazeDFS(maze,col+1,row)){						//right
		return 1;
	}
	if (solveMazeDFS(maze,col,row-1)){						//up
		return 1;
	}
	if (solveMazeDFS(maze,col,row+1)){						//down
		return 1;
	}
	if (maze->cells[row][col] != 'S'){	
		maze->cells[row][col] = '~';						//don't change the 'S' to '~'
	}
    return 0;
}
