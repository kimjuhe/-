/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("-----------------[2019038023] [김주희]-----------------\n");


	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

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
	if(h->first==NULL||((p->key)>key)){ //key가 첫번째 node앞에 들어가야 하거나 기존 node가 없을 때
		node->link = h->first; //node는 헤드노드를 가르키게 한다.
		h->first = node; //헤드노드를 node로 바꿈
	}

	else { //아니면(중간이나 마지막에 들어갈 때)
		while(p->link != NULL) { //마지막 node까지 반복
			w=p; //w에 p를 복사
			p=p->link; //p는 다음 node를 가리킴
			if((p->key)>key){ //p가 가리키는 node의 값이 key보다 크면
				node->link=w->link; /*p의 앞에 node를 넣어줌*/
				w->link = node;
				return 0;
			}
		}
		/*마지막 노드에 들어가야 될 경우*/
		node->link=NULL; //마지막 node이므로 link에는 NULL을 넣는다.
		p->link = node; //기존에 있던 마지막 node의 link는 node를 가리키도록 함
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* p; //key와 같은 값을 가리킬 node
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node를 자동할당
	node->key = key; //새로운 node의 key에 값 입력
	node->link=NULL; //node의 link에 NULL을 입력

	p = h->first; //p는 헤드노드를 가리키게함

	while(p->link != NULL) {
		p = p->link; //마지막 node를 가리킬때까지 반복
	}

	node->link=NULL; //마지막 노드에 node를 이어준다.
	p->link = node;

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p; /*헤드노드를 기존 헤드노드의 링크에 연결되어있는 노드로 바꿔줌*/
	p = h->first;
	(h->first)=(p->link);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode*trail;
	listNode* p;

	p = h->first;
	if(p->key==key){ //key가 헤드노드일 경우
		(h->first)=(p->link); //제일 앞에 있는 노드를 제거
	}
	else{
	while((p->link)!=NULL){ //마지막 노드까지 반복한다.
		if((p->key)==key){ //key와 같은 값을 찾으면
			trail->link=p->link; //p를 없애기 위해 p의 link를 trail로 복사
			return 0;
		}
		trail=p; //trail에 p를 넣고
		p=p->link; //p는 다음 노드를 가르키게함
	}
	if((p->key)==key){ //마지막 노드와 key가 같으면
				trail->link=p->link; //마지막 노드를 없애준다.
				return 0;
			}
	printf("일치하는 값이 없습니다.");
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode*trail;
	listNode* p;

	p = h->first; //p는 헤드노드를 가리키게한다.

	while(p->link!=NULL){ //마지막 노드까지 반복
		trail=p;
		p=p->link;
	}

	trail->link=p->link; //마지막 노드의 link(NULL)을 trail의 link로 바꾼다.

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* middle,* trail,* lead;
	middle = NULL; //middle을 NULL로 초기화
	lead=h->first; //lead는 헤드노드를 가리킴
	while(lead != NULL){ //lead가 NULL이 아닐때까지  리스트를 역순으로 바꿔줌
		trail=middle;
		middle=lead;
		lead=lead->link;
		middle->link=trail;
	}
	h->first = middle;

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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

