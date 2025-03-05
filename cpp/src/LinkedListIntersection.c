#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next;
};

void create(struct node **head, int value) {

	if ((*head) == NULL) {
		printf("\nNew Node Head");
		(*head) = (struct node *)malloc(sizeof(struct node));
		(*head)->data = value;
		(*head)->next = NULL;
		return;
	}

	struct node *newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = value;
	newnode->next = NULL;

	struct node *temp;
	temp = (*head);

	while(temp->next!=NULL)
		temp = temp->next;

	temp->next = newnode;

	return;

}

void display(struct node *head) {
	struct node *temp = head;
	while(temp!=NULL) {
		printf("%d\t",temp->data);
		temp = temp->next;
	}
}

int main(int argc, char const *argv[])
{
	int input;
	int flag = 1;
	int res, x;
	int value;
	struct node *head = NULL;
	struct node *bagalkot = NULL;
	struct node *junction = NULL;
	struct node *newtemp = NULL;
	struct node *temp = NULL;
	struct node *t = NULL;
	int fcount = 0;
	int scount = 0;

	while(flag == 1) {
		
		printf("\nList 1\nCreate - 1\nDisplay - 2\nExit - 0 :\t");
		scanf("%d", &input);
		int dd = 0;
		switch(input) {
			case 0: flag = 0;
					break;

			case 1: for(dd=10;dd<=100;dd+=10)
			   		create(&head, dd);
			   		break;

			case 2: display(head);
					break;

		    default: printf("\nInvalid Choice");
		    		 break;
		}
	}

	flag = 1;

		while(flag == 1) {
		
		printf("\nList 2\nCreate - 1\nDisplay - 2\nExit - 0 :\t");
		scanf("%d", &input);
		int dd = 0;
		switch(input) {
			case 0: flag = 0;
					break;

			case 1: for(dd=30;dd<=70;dd+=10)
			   		create(&bagalkot, dd);
			   		break;

			case 2: display(bagalkot);
					break;

		    default: printf("\nInvalid Choice");
		    		 break;
		}
	}

	//display(head);

	printf("\n");

	//display(bagalkot);

	junction = head;

	while(junction->next->next->next!=NULL)
		junction = junction->next;

	newtemp = bagalkot;

	while(newtemp->next!=NULL)
		newtemp = newtemp->next;

	newtemp->next = junction;

	display(bagalkot);

	printf("\n");

	display(head);

	printf("\n");

	findJunction(head, bagalkot);

	return 0;
}

void findJunction(struct node *list1, struct node *list2) {
	int fcount = 0, scount = 0, res = 0;
	struct node *temp, *extra = NULL;
	temp = list1;

	while(temp!=NULL) {
		temp = temp->next;
		fcount = fcount + 1;
	}

	temp = list2;

	while(temp!=NULL) {
		temp = temp->next;
		scount = scount + 1;
	}

	res = abs((fcount - scount));

	if(fcount > scount) {
		temp = list1;
		extra = list2;
	}
	else {
		temp = list2;
		extra = list1;
	}

	fcount = 0;
	while(fcount!=res && temp!=NULL) {
		temp = temp->next;
		fcount = fcount + 1;
	}

	while(temp!=NULL || extra!=NULL) {
		if(temp == extra) {
			printf("\nIntersection / Junction point is: %d\t%d\n\n", temp->data, extra->data);
			break;
		}

		temp = temp->next;
		extra = extra->next;
	}
}