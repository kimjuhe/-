#include <stdio.h> //p2-2.c

void print1 (int *ptr, int rows);

int main()
{
	int one[]={0, 1, 2, 3, 4}; //�迭 one��  0,1,2,3,4�� �ִ´�.

	printf("-------[������]  [2019038023]-------\n\n");

	printf("one       = %p\n", one);
	printf("&one      = %p\n", &one);
	printf("&one[0]   = %p\n", &one[0]); /*one�� ��, one�� �ּ�, one[0]�� �ּҰ� ����.*/

	print1(&one[0], 5); //�Լ� print1 ȣ��

	return 0;
}

void print1 (int *ptr, int rows)
{
	int i;
	printf("Address \t Contents\n");
	for(i=0;i<rows; i++)
		printf("%p \t %5d\n", ptr +i, *(ptr+i)); //ptr�� 1�� ������ ������ �ּҴ� 4�� (�迭one�� ������ �̹Ƿ�)�����Ѵ�.
	printf("\n");
}
