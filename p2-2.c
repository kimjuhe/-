#include <stdio.h> //p2-2.c

void print1 (int *ptr, int rows);

int main()
{
	int one[]={0, 1, 2, 3, 4}; //배열 one에  0,1,2,3,4를 넣는다.

	printf("-------[김주희]  [2019038023]-------\n\n");

	printf("one       = %p\n", one);
	printf("&one      = %p\n", &one);
	printf("&one[0]   = %p\n", &one[0]); /*one의 값, one의 주소, one[0]의 주소가 같다.*/

	print1(&one[0], 5); //함수 print1 호출

	return 0;
}

void print1 (int *ptr, int rows)
{
	int i;
	printf("Address \t Contents\n");
	for(i=0;i<rows; i++)
		printf("%p \t %5d\n", ptr +i, *(ptr+i)); //ptr이 1씩 증가할 때마다 주소는 4씩 (배열one이 정수형 이므로)증가한다.
	printf("\n");
}
