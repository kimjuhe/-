#include <stdio.h> //ap1.c
#include <stdlib.h>

int main()
{
	int list[5];
	int *plist[5]={NULL,};

	plist[0]=(int*)malloc(sizeof(int)); //동적메모리 할당

	list[0]=1;
	list[1]=100;

	*plist[0]=200;

	printf("-------[김주희]  [2019038023]-------\n");

	printf("value of list[0] = %d\n", list[0]); //list[0]의 값을 출력
	printf("address of list[0]       = %p\n", &list[0]);
	printf("value of list            = %p\n", list);
	printf("address of list (&list)  = %p\n", &list); /*list[0], list의 값, 주소는 같다.*/

	printf("-----------------------------------\n\n");
	printf("value of list[1]    = %d\n", list[1]); //list[1]의 값 출력
	printf("address of list[1]  = %p\n", &list[1]); //list[1]의 주소 출력
	printf("value of *(list+1)  = %d\n", *(list+1)); //list[1]의 값(list의 주소에 +4를 한 값) 출력
	printf("address of list+1   = %p\n", list+1); //list[1]의 주소(list의 주소에 +4한 주소) 출력

	printf("-----------------------------------\n\n");

	printf("value of *plist[0] = %d\n", *plist[0]); //plist[0]의 값 출력
	printf("&plist[0]          = %p\n", &plist[0]);
	printf("&plist             = %p\n", &plist);
	printf("plist              = %p\n", plist); /*(stack에의 주소) plist[0],  plist의 주소와 값은 같다.*/
	printf("plist[0]           = %p\n", plist[0]);
	printf("plist[1]           = %p\n", plist[0]);
	printf("plist[2]           = %p\n", plist[0]);
	printf("plist[3]           = %p\n", plist[0]);
	printf("plist[4]           = %p\n", plist[0]); /*동적할당을 할 때 heap에서의 주소 */

	free(plist[0]);
}
