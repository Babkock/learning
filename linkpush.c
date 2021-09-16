/* Push and pop linked list
 * September 15, 2021 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node_t;

void print_list(node_t *h) {
	node_t *current = h;

	while (current != NULL) {
		printf("%x = %d\n", &current->val, current->val); // print address of value and value
		current = current->next; // advance to next item
	}
}

/* Push a node to the end of the list with value val */
void push(node_t *head, int v) {
	node_t *current = head;
	while (current->next != NULL)
		current = current->next;

	/* Allocate space for newly added node */
	current->next = (node_t *)malloc(sizeof(node_t));
	current->next->val = v;
	current->next->next = NULL;
}

int main(void) {
	node_t *head = NULL;
	head = (node_t *)malloc(sizeof(node_t));
	head->val = 1;

	head->next = (node_t *)malloc(sizeof(node_t));
	head->next->val = 2;
	head->next->next = NULL;

	printf("Here's the current list: \n");
	print_list(head);
	
	push(head, 5);
	printf("Updated linked list: \n");
	print_list(head);

	return 0;
}

