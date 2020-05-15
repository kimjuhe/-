/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("---------------[김주희] [2019038023]---------------\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	listNode* p = h->rlink;

	listNode* prev = NULL; //해제할 노드를 가리킴
	while(p != h) {
		prev = p;
		p = p->rlink;
		free(prev); //prev를 해제
	}
	free(h); //마지막 h를 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) //만약 추가된 리스트가 하나도 없을 경우
	{
		h->rlink = h->llink = node; //헤드노드의 링크들은 추가된 리스트를 가리키게한다.
		node->llink = node->rlink = h; //새로운 노드의 링크들은 헤드노드를 가리키게한다.
		return 1;
	}

	listNode* n = h->rlink;
	while((n->rlink != NULL) && (n->rlink != h)) { //마지막 노드를 가리킬때 까지 반복
		n = n->rlink;
	}
	n->rlink = h ->llink = node;
	node->llink = n;
	node->rlink = h;

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;
	listNode* trail = NULL;

	if(n->rlink == h) { //노드가 하나있는 경우
		h->rlink = h->llink = h;
		free(n);
		return 0;
	}

	while(n->rlink != h) { //마지막 노드 까지 이동
		trail = n;
		n = n->rlink;
	}

	trail->rlink = h; //n이 삭제 되고 그 앞에 있는 노드를 헤드노드와 이어줌
	n->rlink->llink=trail;
	free(n);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->rlink == h) //추가된 노드가 하나도 없을 경우
	{
		h->rlink = h->llink = node;
		node->llink = node->rlink = h;
	}

	node->rlink = h->rlink; //노드의 링크들을 채워준다.
	node->llink = h;

	listNode *p = h->rlink;
	p->llink = node; //추가할리스트를 헤드노드와 기존의 노드사이에 넣어준다.
	h->rlink = node;

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL) //아무것도 없을때
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->rlink; //첫노드를 가리킨다.
	h->rlink = n->rlink; /*첫노드를 뺴준다.*/
	n->rlink->llink=h;

	free(n);

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	if(h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = NULL;
	listNode *middle = NULL;

	h->llink = n; //역순으로 재배치하므로 헤드노드의 llink에 n을 넣어줌

	while(n != h){ //마지막 노드까지 반복
		trail = middle; //처음노드부터 순서를 바꿔줌
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;
	h->llink->rlink = h;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if(h->rlink == h) //추가된 노드가 없을 경우
	{
		h->rlink = h->llink = node;
		node->llink = node->rlink = h;
		return 0;
	}

	listNode* n = h->rlink;

	while(n != h) { //마지막 노드까지 반복
		if(n->key >= key) { //같거나 더큰 노드를 찾으면
			if(n == h->rlink) { //만약 그런 노드가 첫번째 노드이면
				insertFirst(h, key); //함수호출
			} else { // 중간이거나 마지막인 경우
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	// 마지막 노드인 경우
	insertLast(h, key);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h == NULL) //헤드노드가 비어있을 경우
		{
			printf("nothing to delete.\n");
			return 1;
		}

		listNode* n = h->rlink;

		while(n != h) { //마지막 노드까지 반복
			if(n->key == key) { //삭제할 노드를 찾으면
				if(n == h->rlink) { // 첫 노드째 노드인 경우
					deleteFirst(h);
				} else if (n->rlink == h){ // 마지막 노드인 경우
					deleteLast(h);
				} else { // 중간인 경우
					n->llink->rlink = n->rlink;
					n->rlink->llink = n->llink;
					free(n);
				}
				return 1;
			}

			n = n->rlink;
		}

		/* 찾지 못 한경우 */
		printf("cannot find the node for key = %d\n", key);
		return 1;

	return 0;
}


