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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode *temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;

	*h=temp;
	return 1;
}

int freeList(headNode* h){

	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) { //headnode���� ������ node���� �������ش�.
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* p; //key�� ���� ���� ����ų node
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node�� �ڵ��Ҵ�
	node->key = key; //���ο� node�� key�� �� �Է�
	node->rlink=NULL; //node�� link�� NULL�� �Է�

	p = h->first; //p�� ����带 ����Ű����

	while(p->rlink != NULL) {
		p = p->rlink; //������ node�� ����ų������ �ݺ�
	}

	node->rlink=NULL; //������ node�̹Ƿ� rlink���� NULL�� �ִ´�.
	node->llink=p;
	p->rlink = node; //������ �ִ� ������ node�� rlink�� node�� ����Ű���� ��

	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode*trail;
	listNode* p;

	p = h->first; //p�� ����带 ����Ű���Ѵ�.

	while(p->rlink!=NULL){ //������ ������ �ݺ�
		trail=p;
		p=p->rlink;
	}

	trail->rlink=p->rlink; //������ ����� link(NULL)�� trail�� link�� �ٲ۴�.


	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->rlink=h->first; //ù��° node�� �־���ϹǷ� rlink�� headnode�� ����Ű���ϰ�
	node->llink=NULL; //ù����node�̴� llink�� null�� �Ѵ�.
	h->first=node; //�׸��� headnode�� �ٲ��ش�.

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	listNode* p; /*����带 ���� ������� ��ũ�� ����Ǿ��ִ� ���� �ٲ���*/
	p = h->first; //p�� �������� headnode�� ����Ű���Ѵ�.
	(h->first)=(p->rlink); //headnode�� ���� node�� �ٲ��ش�.

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode* middle,* trail,* lead;
	middle = NULL; //middle�� NULL�� �ʱ�ȭ
	lead=h->first; //lead�� ����带 ����Ŵ
	while(lead != NULL){ //lead�� NULL�� ������  ����Ʈ�� �������� �ٲ���
		trail=middle;
		middle=lead;
		lead=lead->rlink;
		middle->rlink=trail;
		middle->llink=lead;
	}
	h->first = middle;

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* p; //key�� ���� ���� ����ų node
	listNode* w; //key�� ���� ���� ���� node�� �� ���
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node�� �ڵ��Ҵ�
	node->key = key; //���ο� node�� key�� �� �Է�

	p = h->first; //p�� ����带 ����Ű�� ��
	w=p; //w�� p�� ����
	if(h->first==NULL){ //���� node�� ���� ��
		node->rlink = NULL; //node�� ���ʿ����� ����Ʈ�� �����Ƿ� NULL�� ����Ű�� �Ѵ�.
		node->llink=NULL;
		h->first = node; //����带 node�� �ٲ�
	}

	else if(((p->key)>key))//key�� ù��° node�տ� ���� �� ��
	{
		node->rlink=p;
		node->llink=NULL;
		h->first=node;
	}
	else { //�ƴϸ�(�߰��̳� �������� �� ��)
		while(p->rlink != NULL) { //������ node���� �ݺ�
			w=p; //w�� p�� ����
			p=p->rlink; //p�� ���� node�� ����Ŵ
			if((p->key)>key){ //p�� ����Ű�� node�� ���� key���� ũ��
				node->llink=w; /*p�� �տ� node�� �־���*/
				node->rlink=w->rlink;
				w->rlink->llink=node;
				w->rlink=node;
				return 0;
			}
		}
		/*������ ��忡 ���� �� ���*/
		node->rlink=NULL; //������ node�̹Ƿ� rlink���� NULL�� �ִ´�.
		node->llink=p;
		p->rlink = node; //������ �ִ� ������ node�� rlink�� node�� ����Ű���� ��
	}

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode*trail;
	listNode* p;

	p = h->first;
	if(p->key==key){ //key�� ������� ���.
		(h->first)=(p->rlink); //headnode�� ���� node�� �ٲ��ش�.
	}
	else{
	while((p->rlink)!=NULL){ //������ ������ �ݺ��Ѵ�.
		if((p->key)==key){ //key�� ���� ���� ã����
			p->llink->rlink=p->rlink; //p�� ���ֱ� ���� p�� rlink�� ����node�� rlink�� ����
			p->rlink->llink=p->llink; //p�� ���ֱ� ���� p�� llink�� ������node�� llink�� ����
			return 0;
		}
		trail=p; //trail�� p�� �ְ�
		p=p->rlink; //p�� ���� ��带 ����Ű����
	}
	if((p->key)==key){ //������ ���� key�� ������
				trail->rlink=p->rlink; //������ ��带 �����ش�.
				return 0;
			}
	printf("��ġ�ϴ� ���� �����ϴ�.");
	}

	return 1;
}


