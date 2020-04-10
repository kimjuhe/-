#include <stdio.h> //p2-1.c

#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main()
{
	for(i=0; i<MAX_SIZE; i++) //0~100���� ������ �迭�� ���� ���ڸ� �ִ´�.
		input[i]=i;

	printf("address of input = %p\n", input); //input�� �ּҸ� ���

	answer = sum(input, MAX_SIZE); //answer�� sum�� ��ȯ���� �ִ´�.
	printf("The sum is: %f\n", answer); //answer�� ����Ѵ�.
}

float sum(float list[], int n) //list�� call by reference, n�� call by value�̴�.
{

  printf("value of list = %p\n", list); //list�� ���� ���(=input�� �ּ�)(input�� �ּҸ� ������ list�� �־� input�� �����Ѵ�.)
  printf("address of list = %p\n\n", &list); //list�� �ּҸ� ���

	int i;
	float tempsum = 0; //���� �� ������ �ʱ�ȭ�Ѵ�.
	for(i=0; i<n; i++)
		tempsum += list[i]; //tempsum�� list[0]~list[99]���� ���Ѵ�.
	return tempsum; //tempsum�� ��ȯ�Ѵ�.
}
