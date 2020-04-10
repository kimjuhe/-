#include <stdio.h> //struct.c

struct student {
	char lastName[13]; /*13 byte*/
	int studentId; /*4 byte*/
	short grade; /*2 byte*/
};

int main()
{
	struct student pst;

	printf("-------[김주희]  [2019038023]-------\n");

	printf("size of student = %ld\n", sizeof(struct student)); //패딩을 시켰기 때문에 (13+3)+4+(2+2)해서 24가 나온다.
	printf("size of int = %ld\n", sizeof(int)); //int의 크기
	printf("size of short = %ld\n", sizeof(short)); //short의 크기

	return 0;
}
