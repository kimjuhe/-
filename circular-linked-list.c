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
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
	printf("---------------[������] [2019038023]---------------\n");

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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){

	listNode* p = h->rlink;

	listNode* prev = NULL; //������ ��带 ����Ŵ
	while(p != h) {
		prev = p;
		p = p->rlink;
		free(prev); //prev�� ����
	}
	free(h); //������ h�� ����

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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) //���� �߰��� ����Ʈ�� �ϳ��� ���� ���
	{
		h->rlink = h->llink = node; //������� ��ũ���� �߰��� ����Ʈ�� ����Ű���Ѵ�.
		node->llink = node->rlink = h; //���ο� ����� ��ũ���� ����带 ����Ű���Ѵ�.
		return 1;
	}

	listNode* n = h->rlink;
	while((n->rlink != NULL) && (n->rlink != h)) { //������ ��带 ����ų�� ���� �ݺ�
		n = n->rlink;
	}
	n->rlink = h ->llink = node;
	node->llink = n;
	node->rlink = h;

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	if (h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;
	listNode* trail = NULL;

	if(n->rlink == h) { //��尡 �ϳ��ִ� ���
		h->rlink = h->llink = h;
		free(n);
		return 0;
	}

	while(n->rlink != h) { //������ ��� ���� �̵�
		trail = n;
		n = n->rlink;
	}

	trail->rlink = h; //n�� ���� �ǰ� �� �տ� �ִ� ��带 ������ �̾���
	n->rlink->llink=trail;
	free(n);

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->rlink == h) //�߰��� ��尡 �ϳ��� ���� ���
	{
		h->rlink = h->llink = node;
		node->llink = node->rlink = h;
	}

	node->rlink = h->rlink; //����� ��ũ���� ä���ش�.
	node->llink = h;

	listNode *p = h->rlink;
	p->llink = node; //�߰��Ҹ���Ʈ�� ������ ������ �����̿� �־��ش�.
	h->rlink = node;

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	if (h == NULL) //�ƹ��͵� ������
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->rlink; //ù��带 ����Ų��.
	h->rlink = n->rlink; /*ù��带 ���ش�.*/
	n->rlink->llink=h;

	free(n);

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

	if(h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = NULL;
	listNode *middle = NULL;

	h->llink = n; //�������� ���ġ�ϹǷ� ������� llink�� n�� �־���

	while(n != h){ //������ ������ �ݺ�
		trail = middle; //ó�������� ������ �ٲ���
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;
	h->llink->rlink = h;

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if(h->rlink == h) //�߰��� ��尡 ���� ���
	{
		h->rlink = h->llink = node;
		node->llink = node->rlink = h;
		return 0;
	}

	listNode* n = h->rlink;

	while(n != h) { //������ ������ �ݺ�
		if(n->key >= key) { //���ų� ��ū ��带 ã����
			if(n == h->rlink) { //���� �׷� ��尡 ù��° ����̸�
				insertFirst(h, key); //�Լ�ȣ��
			} else { // �߰��̰ų� �������� ���
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	// ������ ����� ���
	insertLast(h, key);

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	if (h == NULL) //����尡 ������� ���
		{
			printf("nothing to delete.\n");
			return 1;
		}

		listNode* n = h->rlink;

		while(n != h) { //������ ������ �ݺ�
			if(n->key == key) { //������ ��带 ã����
				if(n == h->rlink) { // ù ���° ����� ���
					deleteFirst(h);
				} else if (n->rlink == h){ // ������ ����� ���
					deleteLast(h);
				} else { // �߰��� ���
					n->llink->rlink = n->rlink;
					n->rlink->llink = n->llink;
					free(n);
				}
				return 1;
			}

			n = n->rlink;
		}

		/* ã�� �� �Ѱ�� */
		printf("cannot find the node for key = %d\n", key);
		return 1;

	return 0;
}


