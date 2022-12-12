/* Function pointers
 * August 17, 2021 */
#include <stdio.h>
#define MAX 5

typedef struct {
	char *name;
	int red;
	int green;
	int blue;
} Color;

Color Colors[MAX];

void eachColor(void (*fp)(Color *c)) {
	int i;
	for (i = 0; i < MAX; i++) {
		// this runs the function pointed to by the first argument to this function
		(*fp)(&Colors[i]);
	}
}

void printColor(Color *c) {
	if (c->name)
		printf("%s = %i,%i,%i\n", c->name, c->red, c->green, c->blue);
}

void hexColor(Color *c) {
	if (c->name)
		printf("%s = '%02x%02x%02x'\n", c->name, c->red, c->green, c->blue);
}

int main(void) {
	Colors[0] = (Color){ .name = "red", .red = 255, .green = 10, .blue = 15 };
	Colors[1] = (Color){ .name = "cyan", .red = 0, .green = 240, .blue = 255 };
	Colors[2] = (Color){ .name = "black", .red = 0, .green = 0, .blue = 0 };
	Colors[3] = (Color){ .name = "green", .red = 0, .green = 255, .blue = 0 };
	Colors[4] = (Color){ .name = "yellow", .red = 255, .green = 255, .blue = 0 };
	eachColor(printColor);
	eachColor(hexColor);
	return 0;
}

