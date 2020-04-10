#include <stdio.h> //p2-1.c

#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main()
{
	for(i=0; i<MAX_SIZE; i++) //0~100까지 각각의 배열에 각각 숫자를 넣는다.
		input[i]=i;

	printf("address of input = %p\n", input); //input의 주소를 출력

	answer = sum(input, MAX_SIZE); //answer에 sum의 반환값을 넣는다.
	printf("The sum is: %f\n", answer); //answer을 출력한다.
}

float sum(float list[], int n) //list는 call by reference, n은 call by value이다.
{

  printf("value of list = %p\n", list); //list의 값을 출력(=input의 주소)(input의 주소를 복사해 list에 넣어 input에 접근한다.)
  printf("address of list = %p\n\n", &list); //list의 주소를 출력

	int i;
	float tempsum = 0; //합을 할 변수를 초기화한다.
	for(i=0; i<n; i++)
		tempsum += list[i]; //tempsum에 list[0]~list[99]까지 더한다.
	return tempsum; //tempsum을 반환한다.
}
