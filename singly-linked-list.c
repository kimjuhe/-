/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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
	printf("-----------------[2019038023] [������]-----------------");


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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

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
	if(h->first==NULL||((p->key)>key)){ //key�� ù��° node�տ� ���� �ϰų� ���� node�� ���� ��
		node->link = h->first; //node�� ����带 ����Ű�� �Ѵ�.
		h->first = node; //����带 node�� �ٲ�
	}

	else { //�ƴϸ�(�߰��̳� �������� �� ��)
		while(p->link != NULL) { //������ node���� �ݺ�
			w=p; //w�� p�� ����
			p=p->link; //p�� ���� node�� ����Ŵ
			if((p->key)>key){ //p�� ����Ű�� node�� ���� key���� ũ��
				node->link=w->link; /*p�� �տ� node�� �־���*/
				w->link = node;
				return 0;
			}
		}
		/*������ ��忡 ���� �� ���*/
		node->link=NULL; //������ node�̹Ƿ� link���� NULL�� �ִ´�.
		p->link = node; //������ �ִ� ������ node�� link�� node�� ����Ű���� ��
	}

	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* p; //key�� ���� ���� ����ų node
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node�� �ڵ��Ҵ�
	node->key = key; //���ο� node�� key�� �� �Է�
	node->link=NULL; //node�� link�� NULL�� �Է�

	p = h->first; //p�� ����带 ����Ű����

	while(p->link != NULL) {
		p = p->link; //������ node�� ����ų������ �ݺ�
	}

	node->link=NULL; //������ ��忡 node�� �̾��ش�.
	p->link = node;

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* p; /*����带 ���� ������� ��ũ�� ����Ǿ��ִ� ���� �ٲ���*/
	p = h->first;
	(h->first)=(p->link);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode*trail;
	listNode* p;

	p = h->first;
	if(p->key==key){ //key�� ������� ���
		(h->first)=(p->link); //���� �տ� �ִ� ��带 ����
	}
	else{
	while((p->link)!=NULL){ //������ ������ �ݺ��Ѵ�.
		if((p->key)==key){ //key�� ���� ���� ã����
			trail->link=p->link; //p�� ���ֱ� ���� p�� link�� trail�� ����
			return 0;
		}
		trail=p; //trail�� p�� �ְ�
		p=p->link; //p�� ���� ��带 ����Ű����
	}
	if((p->key)==key){ //������ ���� key�� ������
				trail->link=p->link; //������ ��带 �����ش�.
				return 0;
			}
	printf("��ġ�ϴ� ���� �����ϴ�.");
	}
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode*trail;
	listNode* p;

	p = h->first; //p�� ����带 ����Ű���Ѵ�.

	while(p->link!=NULL){ //������ ������ �ݺ�
		trail=p;
		p=p->link;
	}

	trail->link=p->link; //������ ����� link(NULL)�� trail�� link�� �ٲ۴�.

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* middle,* trail,* lead;
	middle = NULL; //middle�� NULL�� �ʱ�ȭ
	lead=h->first; //lead�� ����带 ����Ŵ
	while(lead != NULL){ //lead�� NULL�� �ƴҶ�����  ����Ʈ�� �������� �ٲ���
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

