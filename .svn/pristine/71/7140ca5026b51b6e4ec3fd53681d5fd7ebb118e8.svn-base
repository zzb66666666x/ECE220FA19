#include <stdio.h>
#include <stdlib.h>


typedef struct node_t
{
    int data;
    struct node_t *next;
} node;

void remove_duplicates(node * head);
int del_node(node * node_delete, node * head);
int free_all(node * head);

/* Fucnction to append nodes to the Linked list. */
void append(node **head, int data)
{   
    node *temp, *n;

    temp = (node *)malloc(sizeof(node));
    temp->data=data;
    temp->next=NULL;
	//n is a pointer to the input node
    n = *head;

    if(*head==NULL)
    {//if the input node is the last one, in this case, the linked list is empty because the head is originally NULL
        *head=temp;
    }
    else
    {//the input node is not the last one, then   
        while(n->next !=NULL)
		{  
	    n=n->next;
		//update the node pointer n to point to the next until the next node is the end 
		}
	//append the temp node at the end: insert the temp node at the end
	n->next=temp;
    }
}


void printList(node *head)
{
    node *n = head;
 
    while(n != NULL)
    {
	    printf("%d ",n->data);
	    n = n->next;
    }
    printf("\n");
}


int main()
{
    node* head = NULL;

    append(&head,10);
    append(&head,10);
    append(&head,20);
    append(&head,30);
    append(&head,30);
    append(&head,30);
    append(&head,40);
    append(&head,50);
    append(&head,60);

    printf("Before:\n");
    printList(head);

    remove_duplicates(head);
    
    printf("After:\n");
    printList(head);

    /* free linked list here */
	int check;
	check = free_all(head);
	if (check==0){
		printf("failed to free the memory");
	}
    return 0;
}

void remove_duplicates(node * head)
{
    /* add your code here */
	int cur_data = head -> data;
	int check;
	//pick out the data of the first one and carry on
	node * ptr = head;
	node * next_node;
	while ((ptr->next) != NULL)
	{
		next_node = ptr->next;
		if ((next_node->data)==cur_data){
			check = del_node(next_node,head);
			if (check == 0){
				printf("delete error!\n");
				return;
			}
			if (((ptr->next)!=NULL)&&(((ptr->next)->data) != cur_data)){
				ptr = ptr->next;
			}
		}
		else{
			cur_data = next_node->data;
			ptr = ptr->next;
		}
	}
	return;
}

int del_node(node * node_delete, node * head)
{
	node * find = head;
	while((find->next) != node_delete)
	{
		if ((find->next)==NULL){
			printf("delete error!\n");
			return 0;
		}
		find = find->next;
	}
	find->next = node_delete->next;
	free(node_delete);
	return 1;
}

int free_all(node * head)
{
	node * temp = head;
	node * next_temp;
	while ((temp->next) != NULL)
	{
		next_temp = temp->next;
		free(temp);
		temp = next_temp;
	}
	free(temp);
	return 1;
}







