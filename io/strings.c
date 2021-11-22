#include <stdio.h>

void printString(const char *str) {
	while (*str != '\0') {
		putchar(*str);
		str++;
	}
	return;
}

int main(void) {
	char *stringa[] = { "hello world\n" };
	char stringb[50];
	char *stringc = "goodbye world\n";

	printf("Enter a string: ");
	fgets(stringb, sizeof(stringb), stdin);	
	
	// NOTICE THE FUCKING ASTERISK!
	//           ____
	//          |    |
	//          |    |
	//          |    |
	//          |    |
	//          |    |
	//          |    |
	//     _____|    |_____
	//     \              /
	//      \            /
	//       \          /
	//        \        /
	//         \      /
	//          \    /
	//           \  /
	//            \/
	printString(*stringa);
	printString(stringb);
	printString(stringc);

	printf("%s", *stringa);
	printf("%s", stringb);
	printf("%s", stringc);

	return 0;
}
