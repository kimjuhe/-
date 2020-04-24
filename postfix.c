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

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

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
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	static int icp[]={10, 0, 0, 0, 4, 5, 6, 7, 8, 9};
	static int isp[]={0, 0, 0, 0, 4, 5, 6, 7, 8, 9};
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	char symbol;
	precedence token;
	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		token=getToken(*exp); //���ڸ� �ϳ��� �д´�.
		symbol=*exp;
		if(token==operand) //�ǿ����ڴ� �ٷ� postFixExp�� ����
			charCat(&symbol);
		else if(token==rparen) //)�� ������
		{
			while(getToken(postfixStack[postfixStackTop])!=lparen){ //'('������
				x=postfixPop(); //pop�� ���ش�.
				charCat(&x); //postfixExp�� �߰�
			}
			token=postfixPop(); //'('�� �����ش�.
		}
		else{
			while(isp[getToken(postfixStack[postfixStackTop])]>=icp[token]){ //�켱������ ������
				x=postfixPop();   //pop�� ���ش�.
				charCat(&x); //postfixExp�� �߰�
			}
			postfixPush(symbol); //�����ڸ� push���ش�.
		}
		exp++; //���� ���ڸ� ����Ŵ
	}
	while((x=postfixPop())!='\0')
		charCat(&x); //������ �����ڵ��� postfixExp�� �߰��Ѵ�.

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
	while (*exp != '\0'){//����� ���ö����� �ݺ�
		if(token==operand) //operand�̸�
			evalPush(symbol-'0'); //����-48���� �ִ´�.
		else{
			op2=evalPop(); //pop���Ѵ�. (������ ���Լ����̹Ƿ� op2�� ���� pop)
			op1=evalPop(); //pop�� �Ѵ�.
			switch(token){ /*������ �ش�Ǵ� ���꿡 ���� ���*/
				case plus: evalPush(op1+op2); break;
				case minus: evalPush(op1-op2); break;
				case times: evalPush(op1*op2); break;
				case divide: evalPush(op1/op2); break;
			}
		}
		exp++; /*exp�� ������Ű�� token�� �־��ش�.*/
		symbol=*exp;
		token=getToken(symbol);
	}
	evalResult=evalPop(); //������� evalResult�� �ִ´�.
}


int main()
{
	char command;

	printf("-----2019038023 ������-----\n");
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
