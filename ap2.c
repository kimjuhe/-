#include <stdio.h> //ap2.c
#include <stdlib.h>

int main()
{
	int list[5];
	int *plist[5];

	list[0] = 10;
	list[1] = 11;

	plist[0] = (int*)malloc(sizeof(int)); //���� �Ҵ�

	printf("-------[������]  [2019038023]-------\n");

	printf("list[0]         \t= %d\n", list[0]); //list[0]�� �� ���
	printf("address of list \t= %p\n", list); //list��  �ּ�(=list[0]�� �ּ�) ���
	printf("address of list[0] \t= %p\n", &list[0]); //list[0]��  �ּ�(=list�� �ּ�) ���
	printf("address of list + 0 \t= %p\n", list+0); //list�� �ּҿ� 0�� ���� ��(=list[0]�� �ּ�) ���
	printf("address of list + 1 \t= %p\n", list+1); //list�� �ּҿ� 1X4(byte)�� ���� ��(=list[1]�� �ּ�) ���
	printf("address of list + 2 \t= %p\n", list+2); //list�� �ּҿ� 2X4(byte)�� ���� ��(=list[2]�� �ּ�) ���
	printf("address of list + 3 \t= %p\n", list+3); //list�� �ּҿ� 3X4(byte)�� ���� ��(=list[3]�� �ּ�) ���
	printf("address of list + 4 \t= %p\n", list+4); //list�� �ּҿ� 4X4(byte)�� ���� ��(=list[4]�� �ּ�) ���
	printf("address of list[4] \t= %p\n", &list[4]); //list[4]�� �ּ�(= list+4�� �ּ�) ���

	free(plist[0]); //�޸� ����
}
