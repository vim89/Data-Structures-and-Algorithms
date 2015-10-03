#include<stdio.h>

const int FULL = 10;
int mystack[10];
int auxstack[10];
int stop = -1;
int atop = -1;

void push(int stack[], int value, int *top) {
	
	if((*top) >= FULL) {
		printf("\nStack Full");
		return;
	}

	(*top) = (*top) + 1;
	stack[(*top)] = value;
}

int pop(int stack[], int *top) {
	if((*top) < 0){
		printf("\nStack Empty");
		return;
	}

	int x = stack[(*top)];
	(*top) = (*top) - 1;
	return x;
}

sortStackRecursion() {
	
	//Base Condition - Input stack is empty means Output is in auxillary stack
	if(stop<0)
		return;
	//If this is first iteration - push top element to auxillary stack
	if(atop<0) {
		int x = pop(mystack, &stop);
		push(auxstack, x, &atop);
		sortStackRecursion();
	}
	/* If top element of input stack is greater than top element of output stack - simply pop 
	the top element of input stack & push it to output stack.. Then, call recursive function */

	else if(mystack[stop] > auxstack[atop]) {
		push(auxstack, pop(mystack, &stop), &atop);
		sortStackRecursion();
	}
	/* If top element of input stack is smaller than top element of output stack then, pop top element
	of input stack & store in temporary variable x & pop top element of output stack & push it to input stack first & then, 
	push x to input stack.. Then call recursive function */	
	else {
		int x = pop(mystack, &stop);
		push(mystack, pop(auxstack, &atop), &stop);
		push(mystack, x, &stop);
		sortStackRecursion();
	}
}

int main(int argc, char const *argv[])
{	
	push(mystack, 30, &stop);
	push(mystack, -5, &stop);
	push(mystack, 18, &stop);
	push(mystack, 14, &stop);
	push(mystack, -3, &stop);
	push(mystack, 24, &stop);
	push(mystack, -4, &stop);
	push(mystack, 20, &stop);
	push(mystack, 16, &stop);
	push(mystack, -2, &stop);


	int i = stop;

	printf("\nStack Items: ");
	for(i = stop; i>=0; --i)
		printf("%d\t",mystack[i]);
	printf("\n");

	sortStackRecursion();

	printf("\nSorted Stack: ");
	for(i = atop; i>=0; i--)
		printf("%d\t",auxstack[i]);
	printf("\n");
	
	return 0;
}


/** Output:
vitthal@in:~/Desktop/DataStructures$ gcc SortStackUsingRecursion.c
vitthal@in:~/Desktop/DataStructures$ ./a.out

Stack Items: -2	16	20	-4	24	-3	14	18	-5	30	

Sorted Stack: 30	24	20	18	16	14	-2	-3	-4	-5
*/