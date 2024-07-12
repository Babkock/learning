/* Hash table
 * January 13, 2022 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_t {
	char *key;
	char *value;
	struct list_t *next;
} list;

typedef struct hashTable_t {
	unsigned int size;
	list **array;
	/* each cell of this array is a pointer to the first node of a
	 * linked list */
} hashTable;

static hashTable *ht_create(unsigned int size) {
	hashTable *ht;
	if (size < 1)
		return NULL;

	if (!(ht = (hashTable *)malloc(sizeof(hashTable)))) {
		fprintf(stderr, "Could not create hash table\n");
		return NULL;
	}

	ht->array = (list **)malloc(size * sizeof(list));
	if (!ht->array) {
		fprintf(stderr, "Could not create first list in hash table\n");
		return NULL;
	}

	memset(ht->array, 0, size * sizeof(list));
	ht->size = size;
	return ht;
}

/* free the items in a hashTable. free each individual row and column */
static void ht_free(hashTable *ht) {
	list *tmp;

	if (!ht)
		return;

	for (unsigned int i = 0; i < ht->size; ++i) {
		if (ht->array[i] != NULL) {
			/* traverse the list and free nodes */
			while (ht->array[i] != NULL) {
				tmp = ht->array[i]->next;
				free(ht->array[i]->key);
				free(ht->array[i]->value);
				free(ht->array[i]);
				ht->array[i] = tmp;
			}
			free(ht->array[i]);
		}
	}
	free(ht->array);
	free(ht);
}

static unsigned int hash(const char *key, unsigned int size) {
	unsigned int hash = 0, i = 0;

	while (key && key[i]) {
		hash = (hash + key[i]) % size;
		++i;
	}
	return hash;
}

static void node_handle(hashTable *ht, list *node) {
	unsigned int i = hash(node->key, ht->size);
	list *tmp = ht->array[i];

	if (ht->array[i] != NULL) {
		tmp = ht->array[i];
		while (tmp != NULL) {
			if (strcmp(tmp->key, node->key) == 0)
				break;
			tmp = tmp->next;
		}
		if (tmp == NULL) {
			node->next = ht->array[i];
			ht->array[i] = node;
		}
		else {
			free(tmp->value);
			tmp->value = strdup(node->value);
			free(node->value);
			free(node->key);
			free(node);
		}
	}
	else {
		node->next = NULL;
		ht->array[i] = node;
	}
}

static int ht_put(hashTable *ht, const char *key, const char *value) {
	list *node;

	if (!ht) {
		fprintf(stderr, "Hashtable does not exist\n");
		return 1;
	}

	if (!(node = malloc(sizeof(list)))) {
		fprintf(stderr, "Could not allocate node\n");
		return 1;
	}

	node->key = strdup(key);
	node->value = strdup(value);
	node_handle(ht, node);

	return 0;
}

static char *ht_get(hashTable *ht, const char *key) {
	char *key_cp;
	unsigned int i;
	list *tmp;

	if (!ht) {
		return NULL;
	}
	key_cp = strdup(key);
	i = hash(key, ht->size);
	tmp = ht->array[i];

	while (tmp != NULL) {
		if (strcmp(tmp->key, key_cp) == 0) {
			break;
		}
		tmp = tmp->next;
	}
	free(key_cp);

	if (tmp == NULL) {
		return NULL;
	}
	return tmp->value;
}

int main(void) {
	hashTable *ht;
	if (!(ht = ht_create(1))) {
		fprintf(stderr, "Could not create hash table\n");
		return 1;
	}

	if (ht_put(ht, "hello", "world") == 0) { /* push two rows */
		if (ht_put(ht, "foo", "bar") == 0) {
			printf("\"foo\" = %s\n", ht_get(ht, "foo"));
			/* get second row by key "foo" */
		}
		printf("\"hello\" = %s\n", ht_get(ht, "hello"));
		/* get first row by key "hello" */
		ht_free(ht);
		return 0;
	}

	return 1;
}

