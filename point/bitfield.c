/* Objects and bit fields
 * July 3, 2022 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned short month;
	unsigned short day;
	unsigned short year;
} DateBig;

typedef struct {
	unsigned short month : 4;
	unsigned short day : 5;
	unsigned short year;
} DateSmall;

const char *months[] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

void print_big_date(DateBig *date) {
	printf("%s %d, %d\n\n", months[(date->month)-1], date->day, date->year);
}

void print_date(DateSmall *date) {
	printf("%s %d, %d\n\n", months[(date->month)-1], date->day, date->year);
}

int make_big_date(DateBig *out) {
	unsigned int m, d, y;
	printf("Making big date\n");
	printf("Enter month: ");
	scanf("%d", &m);
	if (m < 1 || m > 12) {
		fprintf(stderr, "Month must be between 1-12\n");
		return 1;
	}
	printf("Enter day: ");
	scanf("%d", &d);
	if (d < 1 || d > 31) {
		fprintf(stderr, "Day must be between 1-31\n");
		return 1;
	}
	printf("Enter year (four digits): ");
	scanf("%d", &y);
	if (y < 1900 || y > 2100) {
		fprintf(stderr, "That\'s not a real year\n");
		return 1;
	}
	out->month = m;
	out->day = d;
	out->year = y;
	return 0;
}

int make_date(DateSmall *out) {
	unsigned int m, d, y;
	printf("Making small date\n");
	printf("Enter month: ");
	scanf("%d", &m);
	if (m < 1 || m > 12) {
		fprintf(stderr, "Month must be between 1-12\n");
		return 1;
	}
	printf("Enter day: ");
	scanf("%d", &d);
	if (d < 1 || d > 31) {
		fprintf(stderr, "Day must be between 1-31\n");
		return 1;
	}
	printf("Enter year (four digits): ");
	scanf("%d", &y);
	if (y < 1900 || y > 2100) {
		fprintf(stderr, "That\'s not a real year\n");
		return 1;
	}
	out->month = m;
	out->day = d;
	out->year = y;
	return 0;
}

/* compare the size of DateBig to the size of DateSmall */
int main(void) {
	int r;
	DateBig *b = (DateBig *)malloc(sizeof(DateBig));
	DateSmall *s = (DateSmall *)malloc(sizeof(DateSmall));

	if ((r = make_big_date(b))) {
		fprintf(stderr, "Could not make big date\n");
		return r;
	}
	printf("Size of DateBig: %ld\n", sizeof(DateBig));
	printf("You entered: ");
	print_big_date(b);
	free(b);

	if ((r = make_date(s))) {
		fprintf(stderr, "Could not make small date\n");
		return r;
	}
	printf("Size of DateSmall: %ld\n", sizeof(DateSmall));
	printf("You entered: ");
	print_date(s);
	free(s);

	return 0;
}

