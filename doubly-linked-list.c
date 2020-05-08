/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode *temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;

	*h=temp;
	return 1;
}

int freeList(headNode* h){

	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) { //headnode부터 마지막 node까지 해제해준다.
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* p; //key와 같은 값을 가리킬 node
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node를 자동할당
	node->key = key; //새로운 node의 key에 값 입력
	node->rlink=NULL; //node의 link에 NULL을 입력

	p = h->first; //p는 헤드노드를 가리키게함

	while(p->rlink != NULL) {
		p = p->rlink; //마지막 node를 가리킬때까지 반복
	}

	node->rlink=NULL; //마지막 node이므로 rlink에는 NULL을 넣는다.
	node->llink=p;
	p->rlink = node; //기존에 있던 마지막 node의 rlink는 node를 가리키도록 함

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode*trail;
	listNode* p;

	p = h->first; //p는 헤드노드를 가리키게한다.

	while(p->rlink!=NULL){ //마지막 노드까지 반복
		trail=p;
		p=p->rlink;
	}

	trail->rlink=p->rlink; //마지막 노드의 link(NULL)을 trail의 link로 바꾼다.


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->rlink=h->first; //첫번째 node에 넣어야하므로 rlink는 headnode를 가르키게하고
	node->llink=NULL; //첫번재node이니 llink는 null로 한다.
	h->first=node; //그리고 headnode를 바꿔준다.

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* p; /*헤드노드를 기존 헤드노드의 링크에 연결되어있는 노드로 바꿔줌*/
	p = h->first; //p가 지워야할 headnode를 가르키게한다.
	(h->first)=(p->rlink); //headnode를 다음 node로 바꿔준다.

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* middle,* trail,* lead;
	middle = NULL; //middle을 NULL로 초기화
	lead=h->first; //lead는 헤드노드를 가리킴
	while(lead != NULL){ //lead가 NULL일 때까지  리스트를 역순으로 바꿔줌
		trail=middle;
		middle=lead;
		lead=lead->rlink;
		middle->rlink=trail;
		middle->llink=lead;
	}
	h->first = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* p; //key와 같은 값을 가리킬 node
	listNode* w; //key의 같은 값을 가진 node의 앞 노드
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node를 자동할당
	node->key = key; //새로운 node의 key에 값 입력

	p = h->first; //p는 헤드노드를 가리키게 함
	w=p; //w에 p를 복사
	if(h->first==NULL){ //기존 node가 없을 때
		node->rlink = NULL; //node의 왼쪽오른쪽 리스트가 없으므로 NULL를 가르키게 한다.
		node->llink=NULL;
		h->first = node; //헤드노드를 node로 바꿈
	}

	else if(((p->key)>key))//key가 첫번째 node앞에 들어가야 할 때
	{
		node->rlink=p;
		node->llink=NULL;
		h->first=node;
	}
	else { //아니면(중간이나 마지막에 들어갈 때)
		while(p->rlink != NULL) { //마지막 node까지 반복
			w=p; //w에 p를 복사
			p=p->rlink; //p는 다음 node를 가리킴
			if((p->key)>key){ //p가 가리키는 node의 값이 key보다 크면
				node->llink=w; /*p의 앞에 node를 넣어줌*/
				node->rlink=w->rlink;
				w->rlink->llink=node;
				w->rlink=node;
				return 0;
			}
		}
		/*마지막 노드에 들어가야 될 경우*/
		node->rlink=NULL; //마지막 node이므로 rlink에는 NULL을 넣는다.
		node->llink=p;
		p->rlink = node; //기존에 있던 마지막 node의 rlink는 node를 가리키도록 함
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode*trail;
	listNode* p;

	p = h->first;
	if(p->key==key){ //key가 헤드노드일 경우.
		(h->first)=(p->rlink); //headnode를 다음 node로 바꿔준다.
	}
	else{
	while((p->rlink)!=NULL){ //마지막 노드까지 반복한다.
		if((p->key)==key){ //key와 같은 값을 찾으면
			p->llink->rlink=p->rlink; //p를 없애기 위해 p의 rlink를 왼쪽node의 rlink로 복사
			p->rlink->llink=p->llink; //p를 없애기 위해 p의 llink를 오른쪽node의 llink로 복사
			return 0;
		}
		trail=p; //trail에 p를 넣고
		p=p->rlink; //p는 다음 노드를 가르키게함
	}
	if((p->key)==key){ //마지막 노드와 key가 같으면
				trail->rlink=p->rlink; //마지막 노드를 없애준다.
				return 0;
			}
	printf("일치하는 값이 없습니다.");
	}

	return 1;
}


