/* Linked list
 * September 15, 2021 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node_t;

/* Print the linked list starting at *head */
void print_list(node_t *head) {
	node_t *current = head;

	while (current != NULL) {
		printf("%x = %d\n", &current->val, current->val); // address of value
		current = current->next; // advance to next node in list
	}
}

int main(void) {
	node_t *head = NULL;
	head = (node_t *)malloc(sizeof(node_t));
	if (head == NULL) {
		return 1;
	}

	head->val = 80;

	head->next = (node_t *)malloc(sizeof(node_t));
	if (head->next == NULL) {
		return 1;
	}
	head->next->val = 90;

	print_list(head);
	free(head->next);
	free(head);
	return 0;
}

