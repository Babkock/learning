/* Hash map
 * January 13, 2022 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *key;
	int value;
} item;

item *linear_search(item *items, size_t size, const char *key) {
	for (size_t i = 0; i < size; i++) {
		if (strcmp(items[i].key, key) == 0) {
			return &items[i];
		}
	}
	return NULL;
}

int main(void) {
	item items[] = {
		{"one", 10},
		{"two", 20},
		{"three", 30},
		{"four", 40},
		{"five", 50}
	};
	size_t total = (sizeof(items) / sizeof(item));
	char query[10];
	
	printf("Enter a key to look up: ");
	scanf("%s", query);
	
	item *found = linear_search(items, total, query);
	
	if (!found) {
		fprintf(stderr, "String not found in linear search\n");
		return 1;
	}
	printf("Value of \"%s\" is %d\n", query, found->value);
	return 0;
}

