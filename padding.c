#include <stdio.h> //struct.c

struct student {
	char lastName[13]; /*13 byte*/
	int studentId; /*4 byte*/
	short grade; /*2 byte*/
};

int main()
{
	struct student pst;

	printf("-------[������]  [2019038023]-------\n");

	printf("size of student = %ld\n", sizeof(struct student)); //�е��� ���ױ� ������ (13+3)+4+(2+2)�ؼ� 24�� ���´�.
	printf("size of int = %ld\n", sizeof(int)); //int�� ũ��
	printf("size of short = %ld\n", sizeof(short)); //short�� ũ��

	return 0;
}
