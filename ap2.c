#include <stdio.h> //ap2.c
#include <stdlib.h>

int main()
{
	int list[5];
	int *plist[5];

	list[0] = 10;
	list[1] = 11;

	plist[0] = (int*)malloc(sizeof(int)); //동적 할당

	printf("-------[김주희]  [2019038023]-------\n");

	printf("list[0]         \t= %d\n", list[0]); //list[0]의 값 출력
	printf("address of list \t= %p\n", list); //list의  주소(=list[0]의 주소) 출력
	printf("address of list[0] \t= %p\n", &list[0]); //list[0]의  주소(=list의 주소) 출력
	printf("address of list + 0 \t= %p\n", list+0); //list의 주소에 0을 더한 값(=list[0]의 주소) 출력
	printf("address of list + 1 \t= %p\n", list+1); //list의 주소에 1X4(byte)를 더한 값(=list[1]의 주소) 출력
	printf("address of list + 2 \t= %p\n", list+2); //list의 주소에 2X4(byte)를 더한 값(=list[2]의 주소) 출력
	printf("address of list + 3 \t= %p\n", list+3); //list의 주소에 3X4(byte)를 더한 값(=list[3]의 주소) 출력
	printf("address of list + 4 \t= %p\n", list+4); //list의 주소에 4X4(byte)를 더한 값(=list[4]의 주소) 출력
	printf("address of list[4] \t= %p\n", &list[4]); //list[4]의 주소(= list+4의 주소) 출력

	free(plist[0]); //메모리 해제
}
