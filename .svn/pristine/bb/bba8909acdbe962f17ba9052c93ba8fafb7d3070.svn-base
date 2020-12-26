#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>

//Intro:
//This program implements the link list for fast calculation of sparse matrix.
//Sparse matrix maybe large with a lot of zeros which is a waste of calculation resource.
//With the help of linked list, we can only save the nonzero elements and operate on them.
//The whole test only takes less than 3 seconds now which is so much faster!
//Speaking about details: my program first reads input by file IO, then the linked list will be built.
//After that, it's then possible to do matrix calculation.

void node_init(sp_tuples * mat_t,sp_tuples_node * node,int row,int col,double value);

sp_tuples * load_tuples(char* input_file)
{
	FILE *fp = fopen(input_file,"r");
	if (fp == NULL){
		printf("file open error\n");
		return NULL;
	}
	int i,j;
	double val;
	int dim_m,dim_n;
	fscanf(fp,"%d %d\n",&dim_m,&dim_n);
	sp_tuples * spm = (sp_tuples *)malloc(sizeof(sp_tuples));		//Create then sparse matrix
	spm->m = dim_m;
	spm->n = dim_n;
	spm->nz = 0;
	spm->tuples_head = NULL;										//Initialize the matrix
	while (fscanf(fp,"%d %d %lf\n",&i,&j,&val) != -1)
	{
		set_tuples(spm,i,j,val);									//make use of set_tuples
	}
	fclose(fp);
    return spm;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
	sp_tuples_node * temp = mat_t->tuples_head;
	//int m = mat_t->m;
	int n = mat_t->n;
	int index = n*row+col;
	int temp_index;
	while (temp != NULL)
	{
		temp_index = n*(temp->row)+(temp->col);						//calcualte the index by n*row + col
		if (index == temp_index){
			return (temp->value);
		}
		temp = temp->next;											//check next node
	}
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	int set = 0;
	//int m = mat_t->m;
	int n = mat_t->n;
	int index = n*row+col;
	int temp_index,head_index,next_temp_index;
	sp_tuples_node * temp = mat_t->tuples_head;
	sp_tuples_node * delete;
	if (value != 0){												//check input (0?)
		if (mat_t->tuples_head == NULL){							//first node
			sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
			mat_t->tuples_head = node;		
			node->next = NULL;
			node_init(mat_t,node,row,col,value);
			temp = mat_t->tuples_head;
			set = 1;
		}
		head_index = n*((mat_t->tuples_head)->row)+((mat_t->tuples_head)->col);
		if (index < head_index){									//the node should be in the front of original head element
			sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
			node->next = mat_t->tuples_head;
			mat_t->tuples_head = node;
			node_init(mat_t,node,row,col,value);
			set = 1;
		}
		while ((set == 0)&&(temp->next != NULL))					//use while loop to move the right place to insert the node
		{
			temp_index =  n*(temp->row)+(temp->col);
			next_temp_index = n*((temp->next)->row)+((temp->next)->col);
			if (index == temp_index){
				node_init(mat_t,temp,row,col,value);
				(mat_t->nz)--;
				set = 1;
			}
			else if ((index > temp_index)&&(index >= next_temp_index)){
				temp = temp->next;									//move to the end of linked list
			}
			else if ((index > temp_index)&&(index < next_temp_index)){
				sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
				node->next = temp->next;							//right place, assign memory for new node
				temp->next = node;
				node_init(mat_t,node,row,col,value);
				set = 1;
			}
		}
		temp_index = n*(temp->row)+(temp->col);
		if ((set == 0)&&(index > temp_index)){						//insert at the end and the next of it is NULL
			sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
			node->next = NULL;
			temp->next = node;
			node_init(mat_t,node,row,col,value);
			set = 1;
		}
		else if ((set == 0)&&(index == temp_index)){				//update the last element
			node_init(mat_t,temp,row,col,value);
			(mat_t->nz)--;
			set = 1;
		}
	}
	else{
		if (mat_t->tuples_head == NULL){							//zero value input
			printf("error: cannot delete the node because the list is empty\n");	
			return;
		}
		else{														
			head_index = n*((mat_t->tuples_head)->row)+((mat_t->tuples_head)->col);
			if (index == head_index){								//replace the head node
				(mat_t->tuples_head) = (mat_t->tuples_head)->next;
				free(mat_t->tuples_head);
				(mat_t->nz)--;
				set = 1;
			}
			while ((set == 0)&&((temp->next) != NULL))				//check if there is some node which should be set to zero
			{
				next_temp_index = n*((temp->next)->row)+((temp->next)->col);
				if (next_temp_index == index){
					delete = temp->next;
					temp->next = (temp->next)->next;
					free(delete);
					(mat_t->nz)--;
					set = 1;
				}
				temp = temp->next;
			}
		}
	}
    return;
}

void node_init(sp_tuples * mat_t,sp_tuples_node * node,int row,int col,double value)
{
	(mat_t->nz)++;													//helper function
	node->row = row;
	node->col = col;
	node->value = value;
	return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE * fp = fopen(file_name,"w");
	sp_tuples_node * temp = mat_t->tuples_head;
	int m = mat_t->m;
	int n = mat_t->n;
	int row,col;
	double value;
	fprintf(fp,"%d %d\n",m,n);
	while ((temp) != NULL)											//store the temp into file
	{
		row = temp->row;
		col = temp->col;
		value = temp->value;	
		fprintf(fp,"%d %d %lf\n",row,col,value);					//print out the result (into file)
		temp = temp->next;
	}
	fclose(fp);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
	int A_m,A_n;													//variables needed
	int B_m,B_n;
	A_m = matA->m;
	A_n = matA->n;
	B_m = matB->m;
	B_n = matB->n;
	double valueA,valueB;
	int rowA,colA,rowB,colB;
	double ans;
	if ((A_m == B_m)&&(A_n == B_n)){								//check the size of addition
		sp_tuples * retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
		sp_tuples_node * nodeA = matA->tuples_head;
		sp_tuples_node * nodeB = matB->tuples_head;
		retmat->nz = 0;
		retmat->m = A_m;
		retmat->n = A_n;
		retmat->tuples_head = NULL;
		while (nodeA != NULL)										//traverse elements in matA
		{
			valueA = nodeA->value;
			rowA = nodeA->row;
			colA = nodeA->col;
			set_tuples(retmat,rowA,colA,valueA);					//store information to retmat(also initialization)
			nodeA = nodeA->next;
		}
		while (nodeB != NULL)										
		{
			valueB = nodeB->value;
			rowB = nodeB->row;
			colB = nodeB->col;
			ans = gv_tuples(retmat,rowB,colB);						//read value of matrix B
			ans = ans + valueB;										//addition
			set_tuples(retmat,rowB,colB,ans);						//store the result into retmat
			nodeB = nodeB->next;
		}

		return retmat;	
	}
	return NULL;													//different matrix size
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{
	int A_m,A_n;
	int B_m,B_n;
	A_m = matA->m;
	A_n = matA->n;
	B_m = matB->m;
	B_n = matB->n;
	double valueA,valueB;
	double mult_ans;
	int rowA,colA,rowB,colB;
	if (A_n == B_m){												//check if it's possible to multiply
		sp_tuples * retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
		sp_tuples_node * nodeA = matA->tuples_head;					//pointers initialization
		sp_tuples_node * nodeB = matB->tuples_head;
		retmat->nz = 0;
		retmat->m = A_m;
		retmat->n = B_n;
		retmat->tuples_head = NULL;
		for (;nodeA != NULL; nodeA = nodeA->next)					//traverse elements in A
		{
			rowA = nodeA->row;
			colA = nodeA->col;
			valueA = nodeA->value;									
			//if colA == rowB, then get the result of multiplication and add it to the retmat's corresponding position
			//the ans position should be (rowA,colB)
			for (nodeB = matB->tuples_head;nodeB != NULL; nodeB = nodeB->next)
			{
				rowB = nodeB->row;
				colB = nodeB->col;
				valueB = nodeB->value;
				if (colA == rowB){									
					mult_ans = gv_tuples(retmat,rowA,colB);
					mult_ans = mult_ans + valueA * valueB;
					set_tuples(retmat,rowA,colB,mult_ans);			//store back the result
				}
			}
		}
		return retmat;
	}
    return NULL;
}


	
void destroy_tuples(sp_tuples * mat_t)
{
	sp_tuples_node * temp;
	sp_tuples_node * next_temp = mat_t->tuples_head;
	while (next_temp != NULL)
	{
		temp = next_temp;
		next_temp = next_temp->next;								//first store the next one and then free the current one
		free(temp);
	}
	free(mat_t);													//finally free the matrix
    return;
}  






