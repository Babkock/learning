#include <stdio.h>

typedef struct {
	char name[70];
	int age;
	double gpa;
} Student;

void getStudent(Student *s) {
	printf("Enter name: ");
	scanf(" %[^\n]", s->name);
	printf("Enter age: ");
	scanf("%d", &s->age);
	printf("Enter GPA: ");
	scanf("%lf", &s->gpa);
}

void printStudent(Student *s) {
	printf("Name: %s\n", s->name);
	printf("Age: %d\n", s->age);
	printf("GPA: %.2f\n", s->gpa);
}

int main(void) {
	Student bill, jeff;
	getStudent(&bill);
	printf("\n");
	printStudent(&bill);
	printf("\n");
	getStudent(&jeff);
	printf("\n");
	printStudent(&jeff);
	return 0;
}
