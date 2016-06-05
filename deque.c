/* 
* Ray Che
* COEN 12

* This program contains several functions that handle the creation ofdeque, adding and removing items from the deque, returning an item within the deque, and the deque's destruction. 

*/

// Include header files. "deque.h" is a local header file
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "deque.h"

// Define NODE and DEQUE for easier programming
#define NODE struct node
#define DEQUE struct deque

// Declare contents of node structure
NODE{
	int data;
	NODE *next;
	NODE *prev; 
};

// Declare contents of deque structure
DEQUE {
	int count; 
	NODE *head;  
};  

/* This function handles the allocation of the deque and it's inital "dummy" node and returns a pointer to the deque. This function has a run time of O(1).*/
DEQUE *createDeque(void){
 	DEQUE *dp=malloc(sizeof(DEQUE));
	assert(dp!=NULL); 

	NODE *dummy=malloc(sizeof(NODE));  
	assert(dummy!=NULL); 
	
	// Establishes doubly circular list with dummy node as head
	dp->head=dummy;  
	dp->head->next=dummy; 
	dp->head->prev=dummy; 
	
	// Initialize count of nodes to zero
	dp->count=0; 

	return dp; 
}

/* This function handles the destruction of the deque. This function has a run time of O(n). */
void destroyDeque(DEQUE *dp){
	assert(dp!=NULL); 

	NODE *dummy=dp->head; 
	NODE *np=dummy->next; 

	// Traverse the linked list, freeing all nodes in order starting from dummy->next and dummy last
	while(np!=dummy){
		free(np); 
		np=np->next; 
	}

	free(dummy); 

	return; 
}

/* This function returns the number of items in the linked list (excluding the dummy). This function has a run time of O(1). */
int numItems(DEQUE *dp){
	assert(dp!=NULL); 

	return dp->count; 
}

/* This function creates a node and inserts that node at the beginning of the linked list (after the dummy). This function has a run time of O(1). */
void addFirst(DEQUE *dp, int x){
	assert(dp!=NULL);
 
	// Creates pointers to dummy node and the node after it (aka the "official" first node)
	NODE *dummy, *temp; 
	dummy=dp->head; 
	temp=dummy->next; 

	// Allocates space for new node and assigns the received data value
	NODE *np=malloc(sizeof(NODE));
	assert(np!=NULL); 
	np->data=x;  

	// Inserts the node at the beginning of the linked list (after the dummy), changing pointers to maintain its circular property
	dummy->next=np; 
	np->prev=dummy; 
	np->next=temp;  
	temp->prev=np;  

	dp->count++;   

	return; 
}

/* This function creates a node and inserts that node at the end of the linked list (before the dummy). This function has a run time of O(1). */
void addLast(DEQUE *dp, int x){
	assert(dp!=NULL); 

	// Creates pointers to dummy node and the node before it (aka the "official" last node)
	NODE *dummy, *temp;
	dummy=dp->head; 
	temp=dummy->prev; 

	// Allocates space for new node and assigns the received data value
	NODE *np=malloc(sizeof(NODE)); 
	assert(np!=NULL);   
	np->data=x; 

	// Inserts the node at the end of the linked list (before the dummy), changing pointers to maintain its circular property
	dummy->prev=np;
	np->prev=temp;  
	np->next=dummy;
	temp->next=np;      

	dp->count++;  	

	return; 
}

/* This function removes the first node (after the dummy) from the linked list and returns the value that was in that node. This function has a run time of O(1). */
int removeFirst(DEQUE *dp){
	assert(dp!=NULL); 

	// Creates pointers to dummy node and the node after it (aka the "official" first node)
	NODE *temp, *dummy; 
	dummy=dp->head; 
	temp=dummy->next;

	// Captures data before deletion
	int data=temp->data;

	// Changes pointers to maintain doubly-circular property before deletion
	dummy->next=dummy->next->next;  
	dummy->next->next->prev=dummy->next; 
	
	free(temp); 

	dp->count--;  

	return data; 
}

/* This function removes the last node (before the dummy) from the linked list and returns the value that was in that node. This function has a run time of O(1). */
int removeLast(DEQUE *dp){
	assert(dp!=NULL); 

	// Creates pointers to dummy node and the node before it (aka the "official" last node)
	NODE *temp, *dummy;
	dummy=dp->head;  
	temp=dummy->prev; 

	// Captures data before deletion
	int data=temp->data; 

	// Changes pointers to maintain doubly-circular property before deletion
	dummy->prev=dummy->prev->prev;
	dummy->prev->prev->next=dummy;  

	free(temp); 

	dp->count--; 

	return data; 
}

/* This function simply returns the data contained in the first node in the linked list (after the dummy). This function has a run time of O(1). */
int getFirst(DEQUE *dp){\
	assert(dp!=NULL);

	NODE *dummy=dp->head;  

	return dummy->next->data; 
}

/* This function simply returns the data contained in the last node in the linked list (before the dummy). This function has a run time of O(1). */
int getLast(DEQUE *dp){
	assert(dp!=NULL); 

	NODE *dummy=dp->head; 

	return dummy->prev->data; 
}
