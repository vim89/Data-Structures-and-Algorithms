#include<stdio.h>
const int FULL = 5;
int TOS = -1;

int main(void)
{
	/* code */
	int stack1[5];
	int stack2[5];
	int TOP = -1;
	int i=0;

	printf("\nInput:\t\t");
	for (i = 0; i < FULL; ++i) {
		push(stack1, i+1);
		printf("%d\t", i+1);
	}

	printf("\nStack Output:\t");
	display(stack1, TOS);


	TOP = TOS;
	TOS = -1;

	for (i = 0; i < FULL; ++i) {
		push(stack2, pop(stack1, &TOP));
	}

	printf("\nQueue Output:\t");
	display(stack2, TOS);

	printf("\n");

	return 0;
}

void push(int stack[], int x) {
	if (TOS==FULL) {
		printf("\nStack FULL");
		return;
	}

	stack[++TOS] = x;
	return;
}

int pop(int stack[], int *TOP) {
	int x;
	if(*TOP<0) {
		printf("\nStack Empty");
		return;
	}

	x = stack[*TOP];
	(*TOP) = (*TOP) - 1;
	return x;
}

void display(int stack[], int TOP) {
	int i;
	for (i = TOP; i > -1; --i) {
		printf("%d\t",stack[i]);
	}
}