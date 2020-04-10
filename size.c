#include<stdio.h>
#include<stdlib.h>

void main()
{
	int **x;

	printf("-------[김주희]  [2019038023]-------\n");
	printf("sizeof(x) = %lu\n", sizeof(x));
	printf("sizeof(*x) = %lu\n", sizeof(*x)); /*x, *x는 주소를 저장하기 때문에 4바이트가 나왔다.(32비트라서 4바이트)*/
	printf("sizeof(**x) = %lu\n", sizeof(**x)); //정수형을 저장하는 변수이기 때문에 4바이트가 나왔다.
}
