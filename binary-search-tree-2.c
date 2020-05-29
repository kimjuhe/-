/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("---------------[김주희] [2019038023]---------------\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;){
		for(; node; node=node->left) //오른쪽 노드로 옮겨주며 계속 반복
			push(node);
		node=pop(); //팝해준 값을 node에 넣어준다.
		if(!node) break; //node가 null이 아닐 경우 반복 종료
		printf("[%d] ", node->key);
		node=node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(!ptr) return;
	enQueue(ptr);
	for(;;){ //계속 반복
		ptr=deQueue();
		if(ptr){ //ptr이 null이면 출력
		printf("[%d] ", ptr->key);
		if(ptr->left) //ptr의 left가 null이 아니면
			enQueue(ptr->left);
		if(ptr->right) //ptr의 right가 null이 아니면
			enQueue(ptr->right);
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* tree=head->left;
	Node* chtree;
	Node* trail;

	while (tree) {
		if(key == tree->key && tree->left == NULL && tree->right == NULL){ //key와 node의 key가 같을 경우
			if(trail->right==tree)
				trail->right=NULL;
			else
				trail->left=NULL;
			free(tree);
			return 0;
		}

		else if(key == tree->key && (tree->left != NULL && tree->right == NULL)){ //key와 node의 key가 같고 오른쪽 노드가 비어있을때
			chtree = tree->left;
			while (chtree) { //chtree가 null이 아닐때 까지
			if (chtree->right ==NULL) break;//chtree의 right가 null이면 멈춤
			trail=chtree;
			chtree = chtree->right;
			}
			tree->key=chtree->key; //지워될 트리와 바꿔준다.
			trail->right=NULL; //바꿔준 트리를 지운다.

		}
		else if(key == tree->key && (tree->left == NULL && tree->right != NULL)){ //key와 node의 key가 같고 왼쪽 노드가 비어있을때
			chtree = tree->right;
			while (chtree) {
			if (chtree->left ==NULL) break;//chtree의 left가 null이면 멈춤
			trail=chtree;
			chtree = chtree->left;
			}
			tree->key=chtree->key;//지워될 트리와 바꿔준다.
			trail->left=NULL;//바꿔준 트리를 지운다.
		}
		else if(key == tree->key && (tree->left != NULL && tree->right != NULL)){ //key와 node의 key가 같고 왼쪽,오른쪽 노두 모드 비어있지 않을때
			chtree = tree->right;
			while (chtree) {
			if (chtree->left ==NULL) break;//chtree의 left가 null이면 멈춤
			trail=chtree;
			chtree = chtree->left;
			}
			tree->key=chtree->key;//지워될 트리와 바꿔준다.
			trail->left=NULL;//바꿔준 트리를 지운다.
		}
		if (key < tree->key){ //key가 node보다 작을 경우
			trail=tree;
			tree = tree->left;
		}
		else{ //key가 node보다 클 경우
			trail=tree;
			tree = tree->right;
		}
	}

	return 0;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if(top==-1){ //pop할게 없을 경우
		return NULL;
	}
	return stack[top--];
}

void push(Node* aNode)
{
	if(top >= MAX_STACK_SIZE-1){ //넣으 공간이 없을 경우
		printf("Stack is full.\n");
		return;
	}
	stack[++top]=aNode;
}



Node* deQueue()
{
	if (front==rear){ //지울게 없을 경우
		return NULL;
	}
	front = (front+1) % MAX_QUEUE_SIZE;
	return queue[front];

}

void enQueue(Node* aNode)
{
	rear=(rear+1)%MAX_QUEUE_SIZE;
	if(front==rear){ //넣을 공간이 없을 경우
		printf("queue is full.");
		return ;
	}
	queue[rear]=aNode;
}





