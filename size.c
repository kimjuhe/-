#include<stdio.h>
#include<stdlib.h>

void main()
{
	int **x;

	printf("-------[������]  [2019038023]-------\n");
	printf("sizeof(x) = %lu\n", sizeof(x));
	printf("sizeof(*x) = %lu\n", sizeof(*x)); /*x, *x�� �ּҸ� �����ϱ� ������ 4����Ʈ�� ���Դ�.(32��Ʈ�� 4����Ʈ)*/
	printf("sizeof(**x) = %lu\n", sizeof(**x)); //�������� �����ϴ� �����̱� ������ 4����Ʈ�� ���Դ�.
}
