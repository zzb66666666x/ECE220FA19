#include <stdio.h>
#include <stdlib.h>


typedef struct node_t
{
    int data;
    struct node_t *next;
} node;

void reverse(node** head);
int free_all(node * head);
void find_prev(node * head, node * cur, node ** prev);

/* Fucnction to append nodes to the Linked list. */
void append(node **head, int data)
{   
    node *temp,*n;

    temp = (node *)malloc(sizeof(node));
    temp->data=data;
    temp->next=NULL;

    n = *head;

    if(*head==NULL)
    {   
        *head=temp;
    }
    else
    {  
        while(n->next !=NULL)
	{  
	    n=n->next;
	}
	
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

    append(&head,20);
    append(&head,10);
    append(&head,90);
    append(&head,100);
    append(&head,80);
    append(&head,0);
    append(&head,4);
    append(&head,60);
    append(&head,05);

    printf("Before:\n");
    printList(head);

    /* call your function here */
	reverse(&head);

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

void reverse(node** head)
{
    /* add your code here */
	node * find;
	node * end;
	node * end_temp;
	end = *head;
	while ((end->next)!=NULL)
	{
		end = end->next;
	}
	node ** prev;
//this prev has to be a double pointer!!!!!
	prev = &end;
	end_temp = end;
	find = end;
	while (*prev != *head)
	{//while the pointer doesn't points to the same node
		find_prev(*head, find, prev);
		(find->next) = *prev;
		find = *prev;
	}
	find->next = NULL;
	//make the head points to the end
	//To change the value of pointer head, we have to access the memory of head and change its value!
	*head = end_temp;
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

void find_prev(node * head, node * cur, node ** prev)
{
//I want to modify the value of the *prev in the previous function, so it has to be a double pointer because what we want to change is a pointer!
	node * temp;
	temp = head;
	while ((temp->next)!=cur)
	{
		temp = temp->next;
	}
	*prev = temp;
	return;
}
