#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

#define MAX_VERTEX 20 /* you can change value 20 */

typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;

typedef struct VertexHead {
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;

typedef struct Graph {
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;

typedef struct queue *queuePointer;

typedef struct{
	int vertex;
	queuePointer link;
} queue;


short int index[MAX_VERTEX];

short int visited[MAX_VERTEX];

/* 함수 리스트 */
void createGraph(Graph *v); /* empty graph creation */
void destroyGraph(Graph *v); /* deallocating all allocated memory */
void insertVertex(Graph *v,int vernum); /* vertex insertion */
int deleteVertex(Graph *v,int vernum); /* vertex deletion */
void delete(Graph *v, int vernum); /*연결리스트의 vertex를 지움*/
void insertEdge(Graph *v, int a, int b); /* new edge creation between two vertices */
void insert(Graph *v, int key1, int key2);/*연결리스트를 이을 함수*/
void deleteEdge(Graph *v, int a, int b); /* edge removal */
int deleteEd(Graph *v, int key1, int key2); /*연결리스트를 지울 함수*/
void depthFS(Graph *v, int key); /* depth first search using stack */
void breathFS(Graph *v, int key); /* breadth first search using queue */
void addq(int key); /*큐 추가*/
int deleteq(); /*큐 삭제*/
void printGraph(Graph *v); /* printing graph with vertices and edges */

int main()
{
	char command;
	int key; //vertex를 입력받을 변수
	int key1, key2; //Edge를 이을 vertex두개를 입력받을 변수
	Graph* list=NULL;
	printf("-----------------[2019038023] [김주희]-----------------\n");


	do{
		printf("----------------------------------------------------------------\n");
		printf("                           Graph                                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Create Graph    = z         Print           = p \n");
		printf(" Insert Vertex   = i         Delete Vertex   = d \n");
		printf(" Insert Edge     = n         Delete Edge     = e \n");
		printf(" depthFS         = f         breadthFS       = t \n");
		printf(" destroy Graph   = r         Quit            = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			createGraph(list);
			break;
		case 'p': case 'P':
			printGraph(list);
			break;
		case 'i': case 'I':
			printf("Vertex number = ");
			fflush(stdout);
			scanf("%d", &key);
			insertVertex(list, key);
			break;
		case 'd': case 'D':
			printf("Vertex number = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteVertex(list, key);
			break;
		case 'n': case 'N':
			printf("Vertex number( ex) 1 2 ) = ");
			fflush(stdout);
			scanf("%d %d", &key1, &key2);
			insertEdge(list, key1, key2);
			break;
		case 'e': case 'E':
			printf("Vertex number( ex) 1 2 ) = ");
			fflush(stdout);
			scanf("%d %d", &key1, &key2);
			deleteEdge(list, key1, key2);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			depthFS(list, key);
			break;
		case 't': case 'T':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			breathFS(list, key);
			break;
		case 'r': case 'R':
			destroyGraph(list);
			break;
		case 'q': case 'Q':
			destroyGraph(list);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void createGraph(Graph *v){
	v=(Graph*)malloc(sizeof(VertexHead)); //그래프 자동할당
	(v->vlist)= (VertexHead *)malloc(sizeof(VertexHead)*MAX_VERTEX); //vlist 자동할당

	for(int i=0; i<MAX_VERTEX; i++){ /*vlist를 초기화 해줌*/
		v->vlist[i].head=NULL;
		index[i]=0;
	}

}

void destroyGraph(Graph *v){
	free(v);

}

void insertVertex(Graph *v,int vernum){
	Vertex* p; //key1과 같은 값을 가리킬 Vertex
	p=v->vlist[vernum-1].head;
	if(vernum>(MAX_VERTEX)||vernum<1){ //범위 안의 것을 입력했는지 확인
		printf("vertex가 존재하지 않습니다.\n");
		return ;
	}
	if(index[vernum-1]==0){ //vertex생성됐다고 체크
		index[vernum-1]=1;
	}
	else{ //이미 존재할 경우
		printf("이미 존재하는 vertex입니다.");
		return ;
	}
}

int deleteVertex(Graph *v,int vernum){
	Vertex* p; //key1과 같은 값을 가리킬 Vertex
	Vertex* w; //key1과 같은 값을 가진  Vertex의 앞 노드
	p=v->vlist[vernum-1].head;

	if(vernum>(MAX_VERTEX)||vernum<1){ //범위 안의 것을 입력했는지 확인
			printf("vertex가 범위내에 있지않습니다.\n");
			return 0;
	}

	if(index[vernum-1]==1){ //존재하는 vertex일 경우 이어지는 list를 모두 지워준다.
		index[vernum-1]=0;
		while(p!=NULL){
			w=p;
			p=p->link;
			free(w);
		}
		delete(v, vernum); //Edge들을 지워준다.
	}
	else{ //이미 존재할 경우
		printf("존재하지 않는 vertex입니다.");
		return 0;
	}
}

void delete(Graph *v, int vernum){
	Vertex* p; //key1과 같은 값을 가리킬 Vertex
	Vertex* w; //key1과 같은 값을 가진  Vertex의 앞 노드

	for(int i=0; i<MAX_VERTEX; i++){
		if(i!=vernum-1){ //해당 vertex를 빼고 edge들을 지워준다.
			p=v->vlist[i].head;
			while(p!=NULL){ //옆으로 옮겨주면서
				w=p;
				p=p->link;
				if(p->num==vernum){ //지울 vertex와 같은 값이나오면 지움
					w->link=p->link;
					break;
				}
			}
		}
	}

}

void insertEdge(Graph *v, int a, int b){
	Vertex* p; //연결되어있는지 아닌지 확인할  Vertex
	p=v->vlist[a-1].head;

	if(index[a-1]==1&&index[b-1]==1){
		while(p!=NULL){
			if(p->num==b){ //연결되어있는지 아닌지 확인
				printf("이미 연결되어 있습니다.");
				return ;
			}
			p=p->link;
		}
		insert(v, a, b); /*리스트 추가해 주는 함수 호출*/
		insert(v, b, a);
	}
	else{ //vertex가 없을 경우
		printf("vertex가 존재하지 않습니다.");
		return ;
	}
}

void insert(Graph *v, int key1, int key2){
	Vertex* node = (Vertex*)malloc(sizeof(Vertex)); //Vertex를 자동할당
	Vertex* p; //key1과 같은 값을 가리킬 Vertex
	Vertex* w; //key1과 같은 값을 가진  Vertex의 앞 노드

	p = v->vlist[key1-1].head; //p는 첫번째 vertex를 가리키게 함
	w=p; //w에 p를 복사

	node->num=key2;
	node->link=NULL;

	if(v->vlist[key1-1].head==NULL||((p->num)>key2)){ //head가 비어져있거나 head 바로 뒤에 들어가야 할 경우
		node->link = v->vlist[key1-1].head; //node는 헤드노드를 가르키게 한다.
		v->vlist[key1-1].head = node; //헤드노드를 node로 바꿈
	}

	else { //아니면(중간이나 마지막에 들어갈 때)
			while(p->link != NULL) { //마지막 node까지 반복
				w=p; //w에 p를 복사
				p=p->link; //p는 다음 node를 가리킴
				if((p->num)>key2){ //p가 가리키는 node의 값이 key보다 크면
					node->link=w->link; /*p의 앞에 node를 넣어줌*/
					w->link = node;
					return ;
				}
			}
			/*마지막 노드에 들어가야 될 경우*/
			node->link=NULL; //마지막 node이므로 link에는 NULL을 넣는다.
			p->link = node; //기존에 있던 마지막 node의 link는 node를 가리키도록 함
		}

}

void deleteEdge(Graph *v, int a, int b){
	Vertex* p; //key1과 같은 값을 가리킬 Vertex
	p=v->vlist[a-1].head;

	if(index[a-1]==1&&index[b-1]==1){ //vertex가 둘다 존재하고 있는지 확인
		while(p!=NULL){
			if(p->num==b){ //a와 b가 연결되어있을 경우 삭제
				deleteEd(v, a, b);
				deleteEd(v, b, a);
				return ;
			}
			p=p->link;
		}
		printf("연결되어 있지 않습니다.\n"); //연결되어있지 않은 경우
	}
	else{ //vertex가 없는 경우
		printf("vertex가 존재하지 않습니다.\n");
		return ;
	}
}

int deleteEd(Graph *v, int key1, int key2){ //리스트의 노드를 삭제할 함수
	Vertex*trail;
	Vertex* p;

	p = v->vlist[key1-1].head;
	if(p->num==key2){ //key가 헤드노드일 경우
		(v->vlist[key1-1].head)=(p->link); //제일 앞에 있는 노드를 제거
		return 0;
		}
	else{
		while((p->link)!=NULL){ //마지막 노드까지 반복한다.
			if((p->num)==key2){ //key와 같은 값을 찾으면
				trail->link=p->link; //p를 없애기 위해 p의 link를 trail로 복사
				return 0;
			}
			trail=p; //trail에 p를 넣고
			p=p->link; //p는 다음 노드를 가르키게함
		}
		if((p->num)==key2){ //마지막 노드와 key2가 같으면
			trail->link=p->link; //마지막 노드를 없애준다.
			return 0;
		}
	}
}

void depthFS(Graph *v, int key){
	Vertex* p;

	visited[key-1]=1;
	printf("%d  ", key);
	for(p=v->vlist[key-1].head; p; p=p->link)
		if(!visited[p->num-1])
			depthFS(v, p->num);

}

void breathFS(Graph *v, int key){
	Vertex* p;

	queuePointer front, rear;
	front = rear= NULL; //큐초기화

	printf("%d  ", key);
	visited[key-1]=1;
	//addq(&front, &rear, v);

	while(front){
		v=deleteq(front);
		for(p=v->vlist[key-1].head; p; p=p->link){
			if(!visited[p->num-1]){
				printf("%d  ", p->num);
				//addq(&front, &rear, p->num);
				visited[p->num-1]=1;
			}
		}
	}

}

void addq(int key){} /*큐 추가*/
int deleteq(){} /*큐 삭제*/

void printGraph(Graph *v){
	Vertex* p;
	if(v==NULL){
		printf("프린트 할 것이 없습니다.");
	}

	for(int i=0; i<MAX_VERTEX; i++){
		if(index[i]==1){
			p=v->vlist[i].head;
			printf("%d :", i+1);
			while(p!=NULL){
				printf("%d  ", (p->num)+1);
				p=p->link;
			}
			printf("\n");
		}
	}
}






