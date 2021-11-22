/* Output effects example by Tanner Babcock
 * June 22, 2010 */
#include <stdio.h>
#define _ fx(0);

void fx(int x) {
	printf("\E[%dm", x);
}

void hello() {
	printf("Hello World ");
}

int main() {
	fx(1);
	hello();
	printf("with intensity.\n");
	_
	fx(4);
	hello();
	printf("underlined.\n");
	_
	fx(7);
	hello();
	printf("in negative.\n");
	_
	fx(31);
	hello();
	printf("in red.\n");
	_
	fx(32);
	hello();
	printf("in green.\n");
	_
	fx(35);
	hello();
	printf("in pink.\n");
	_
	fx(36);
	hello();
	printf("in cyan.\n");
	_
	hello();
	printf("without effects.\n");
	return 0;
}
