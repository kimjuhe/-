/*
 * circularQ.c
 *
 */


#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	printf("-----2019038023 김주희------");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()
{
	element item;
	printf("Input element = ");
	fflush(stdout);
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if(cQ->rear==cQ->front) //rear와 front가 같은지 확인한 후에 -1을 return(아무것도 들어가있지않아 같은것이므로)
		return -1;
	else
		return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if(((cQ->rear)+1)%MAX_QUEUE_SIZE==cQ->front) //real이 가리키는 곳 +1(한칸비어있으므로)과 front가 같으면 -1을 반환
		return -1;
	else
		return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{

	if(((cQ->rear)+1)%MAX_QUEUE_SIZE==(cQ->front)){ //real이 가리키는 곳 +1(한칸비어있으므로)과 front가 같으면
		if(isFull(cQ)==-1)	//isFull을 호출
			printf("원형큐가 꽉 찼습니다.");
	}

	else{
		cQ->rear=((cQ->rear)+1)%MAX_QUEUE_SIZE; /*rear이 가리키는 곳 다음에 사용자가 입력한 수를 넣는다.*/
		cQ->queue[cQ->rear]= item;
	}
	return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(cQ->rear==cQ->front) //rear와 front가 같으면
		{
			if(isEmpty(cQ)==-1) 
			printf("빈 원형큐 입니다.");
		}
	else
	{
		cQ->front=((cQ->front)+1)%MAX_QUEUE_SIZE; //front+1(맨뒤에 위치해있으면 1로)을 해준다.
		cQ->queue[cQ->front]; //front를 한칸앞으로이동해 지워준다.
	}
	return 0;
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
