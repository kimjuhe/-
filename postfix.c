/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}


void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    fflush(stdout);
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}

}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	static int icp[]={10, 0, 0, 0, 4, 5, 6, 7, 8, 9};
	static int isp[]={0, 0, 0, 0, 4, 5, 6, 7, 8, 9};
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	char symbol;
	precedence token;
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		token=getToken(*exp); //문자를 하나씩 읽는다.
		symbol=*exp;
		if(token==operand) //피연산자는 바로 postFixExp에 저장
			charCat(&symbol);
		else if(token==rparen) //)가 나오면
		{
			while(getToken(postfixStack[postfixStackTop])!=lparen){ //'('전까지
				x=postfixPop(); //pop을 해준다.
				charCat(&x); //postfixExp에 추가
			}
			token=postfixPop(); //'('을 없애준다.
		}
		else{
			while(isp[getToken(postfixStack[postfixStackTop])]>=icp[token]){ //우선순위가 높을시
				x=postfixPop();   //pop을 해준다.
				charCat(&x); //postfixExp에 추가
			}
			postfixPush(symbol); //연산자를 push해준다.
		}
		exp++; //다음 문자를 가리킴
	}
	while((x=postfixPop())!='\0')
		charCat(&x); //나머지 연산자들을 postfixExp에 추가한다.

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	precedence token;
	char *exp=postfixExp;
	char symbol;
	int op1, op2;
	symbol=*exp;
	token= getToken(symbol);
	while (*exp != '\0'){//빈곳이 나올때까지 반복
		if(token==operand) //operand이면
			evalPush(symbol-'0'); //문자-48을해 넣는다.
		else{
			op2=evalPop(); //pop을한다. (스택은 후입선출이므로 op2에 먼저 pop)
			op1=evalPop(); //pop을 한다.
			switch(token){ /*각각에 해당되는 연산에 따라 계산*/
				case plus: evalPush(op1+op2); break;
				case minus: evalPush(op1-op2); break;
				case times: evalPush(op1*op2); break;
				case divide: evalPush(op1/op2); break;
			}
		}
		exp++; /*exp를 증가시키고 token에 넣어준다.*/
		symbol=*exp;
		token=getToken(symbol);
	}
	evalResult=evalPop(); //결과값을 evalResult에 넣는다.
}


int main()
{
	char command;

	printf("-----2019038023 김주희-----\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;


}
