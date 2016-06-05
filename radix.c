/* 
* Ray Che
* COEN 12

*  This program takes an input of non-negative numbers and uses a radix sort algorithm to sort the input in numerical order. 
*/ 

// Include header files
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "deque.h"

// This is the main function of the program. It takes in an input of numbers and calls functions from deque.c as it inserts into the deque and proceeds to sort through the numbers using radix sorting. This function is divided into sections for the purposes of determining the run time of each section. */
int main(void){

	/* SECTION 1 O(1) */

	// Calls createDeque to create a deque that is pointed to by list. This deque is the main deque used to hold the numbers
	DEQUE *list=createDeque(); 
	assert(list!=NULL);  

	// Creates an array of deques that will function as the bins for sorting 
	DEQUE *bins[10]; 
	assert(bins!=NULL); 


	/* SECTION 2 O(n) */

	int i, numinput; 
	
	// Calls createDeque to create a deque for each of the bins
	for(i=0; i<11; i++){
		bins[i]=createDeque(); 
	}

	/* SECTION 3 O(n) */

	int maxval=0; 

	// Takes in an input of numbers until a user enters an invalid value (i.e. an alpha character)
	while(scanf("%d",&numinput)==1){
		// Compares the input with the maximum value from the current list of inputs and updates if the input is greater
		if(numinput>maxval){
			maxval=numinput; 
		}
		
		// Adds to the end of the deque
		addLast(list, numinput); 
		
	}	

	int nitems=numItems(list); 

	printf("Number of items: %d\n", nitems); 
	printf("Max value: %d\n", maxval); 	

	/* SECTION 4 O(n^4) */
	
	int count, j, k, l, m, pos, num;
	int place=1; // For each decimal place 
	int maxdigits=ceil(log10(maxval+1)/log10(10)); // Max amount of digits present in the list determined from the maximum input value

	// Radix sorting loop. Runs for maxdigits times, as it only needs to iterate for the max number of digits present
	for(k=0; k<maxdigits; k++){
		// Loop removes each number from the list and sorts them into bins for each decimal place
		for(j=0; j<nitems; j++){
 			num=removeFirst(list);   
			pos=(num%(place*10))/place;
			addLast(bins[pos], num);  			
		}
		// Loop retrieves numbers in order from each bin and inserts them back into the official list
		for(l=0; l<10; l++){
			count=numItems(bins[l]); 

			for(m=0; m<count; m++){	
				num=removeFirst(bins[l]);
			 	addLast(list, num); 
			}
		} 
		
		// Increments for each decimal place (ones, tens, hundreds, etc.)
		place=place*10; 
	}

	/* SECTION 5 O(n) */

	int n; 

	// Traverses the list, removing each item and printing the values in order
	for(n=0; n<nitems; n++){
		printf("%d\t", removeFirst(list));
	} 

	/* SECTION 6 O(n) */	
	
	int x; 

	// Frees the memory allocated for each of the bins
	for (x=0; x<10; x++){
		destroyDeque(bins[x]); 
	}
	
	// Frees the memory allocated for the list
	destroyDeque(list); 
	
	return 0; 
}
