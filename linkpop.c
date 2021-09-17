/* Linked list with push and pop
 * September 16, 2021 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node_t;

/* Print the linked list */
void print_list(node_t *h) {
	node_t *current;

	for (current = h; current != NULL; current = current->next) {
		printf("%x = %d\n", &current->val, current->val);
	}
}

/* New push function, inserts at beginning instead of end */
int push(node_t **h, int val) {
	/* This **h is a double pointer */
	if (*h == NULL) {
		return 1;
	}

	node_t *new;
	new = (node_t *)malloc(sizeof(node_t));
	if (!new) {
		return 1;
	}

	new->val = val;
	new->next = *h;
	/* append to the beginning, so make the old head the next of the new node */
	*h = new;
	return 0;
}

/* Remove from beginning of list, and return stored value */
int pop(node_t **h) {
	int ret = -1;
	node_t *next = NULL;

	if (*h == NULL) {
		return ret;
	}
	next = (*h)->next;
	ret = (*h)->val;
	free(*h);
	*h = next;

	return ret;
}

int main(void) {
	int p;
	node_t *head = NULL;
	head = (node_t *)malloc(sizeof(node_t));
	if (!head) {
		fprintf(stderr, "Could not allocate space for first node\n");
		return 1;
	}
	head->val = 64;

	head->next = (node_t *)malloc(sizeof(node_t));
	if (head->next == NULL) {
		fprintf(stderr, "Could not allocate space for second node\n");
		free(head);
		return 1;
	}
	head->next->val = 42;
	head->next->next = NULL;

	printf("Here's the current list:\n");
	print_list(head);

	if (push(&head, 11) == 1) {
		fprintf(stderr, "Could not push to linked list\n");
		return 1;
	}
	if (push(&head, 22) == 1) {
		fprintf(stderr, "Could not push to linked list\n");
		return 1;
	}
	
	printf("After two pushes:\n");
	print_list(head);

	p = pop(&head);
	printf("Popped value %d\n", p);
	p = pop(&head);
	printf("Popped value %d\n", p);

	free(head->next);
	free(head);

	return 0;
}
