#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col); //����� ������ִ� �Լ�
int free_matrix(int** matrix, int row, int col); //free���ִ� �Լ�
void print_matrix(int** matrix, int row, int col); //����� ��� ���ִ� �Լ�
int fill_data(int **matrix, int row, int col); //����� ä���ִ� �Լ�
int transpose_matrix(int **matrix, int **matrix_t, int row, int col); //��ġ����� ���ϴ� �Լ�
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col); //����� ���ϴ� �Լ�
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col); //����� ���ϴ� �Լ�
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col); //����� ���ϴ� �Լ�

int main()
{
	srand(time(NULL));

	int row, column;
	int **ArrayA, **ArrayB, **ArrayResult, **matrix_t, **matrix_axt;
	printf("--------[������] [2019038023]--------\n");
	printf("��� ���� �Է��ϼ��� : "); //"��� ���� �Է��ϼ���: "�� ���
	fflush(stdout);
	scanf("%d %d", &row, &column); //������� �Է¹޴´�.

	ArrayA=create_matrix(row, column); //ArrayA�� �ڵ��Ҵ����ش�.
	ArrayB=create_matrix(row, column); //ArrayB�� �ڵ��Ҵ����ش�.
	ArrayResult=create_matrix(row, column); //ArrayResult�� �ڵ��Ҵ����ش�.
	matrix_t=create_matrix(column, row); //matrix_t�� �ڵ��Ҵ����ش�.
	if(row<column) /*����� ���� �� row, column �� ���� ���� ����� ��� ���� �ǹǷ� row�� �������� ���ų� Ŭ���� ���� matrix_axt�� ������ش�.*/
		matrix_axt=create_matrix(row, row);
	else
		matrix_axt=create_matrix(column,column);

	if(fill_data(ArrayA, row, column)!=0){//��Ŀ� �����͸� �ִ´�.
		printf("��� ���� �Է��ϼ��� : "); //"��� ���� �Է��ϼ���: "�� ���
		fflush(stdout);
		scanf("%d %d", &row, &column); //������� �Է¹޴´�.
	}
	if(fill_data(ArrayB, row, column)!=0){//��Ŀ� �����͸� �ִ´�.
		printf("��� ���� �Է��ϼ��� : "); //"��� ���� �Է��ϼ���: "�� ���
		fflush(stdout);
		scanf("%d %d", &row, &column); //������� �Է¹޴´�.
	}

	if(addition_matrix(ArrayA, ArrayB, ArrayResult, row, column)!=0)//����� ���Ѵ�.
		addition_matrix(ArrayA, ArrayB, ArrayResult, row, column); //����� �߸� �������� ��� �ٽ� ����
	printf("-----------------A+B-----------------\n"); //"-----A+B-----"���
	print_matrix(ArrayResult, row, column); //A+B�� ����Ѵ�.

	if(subtraction_matrix(ArrayA, ArrayB, ArrayResult, row, column)!=0)//����� ���ش�.
		subtraction_matrix(ArrayA, ArrayB, ArrayResult, row, column); //����� �߸� ������ ��� �ٽ� ����
	printf("-----------------A-B-----------------\n"); //"-----A-B-----"���
	print_matrix(ArrayResult, row, column); //A-B�� ������� ���

	if(transpose_matrix(ArrayA, matrix_t, row, column)!=0) //��ġ��� T�� ���Ѵ�.
		transpose_matrix(ArrayA, matrix_t, row, column); //����� �߸� �������� ��� �ٽ� ����
	if(multiply_matrix(ArrayA, matrix_t, matrix_axt, row, column)!=0) //����� ���Ѵ�.
		multiply_matrix(ArrayA, matrix_t, matrix_axt, row, column); //����� �߸� �������� ��� �ٽ� ����
	printf("-----------------AXT------------------\n"); //"-----AXT-----"���
	if(row<column) /*�� ���� ���� ��� ���� �Ͽ� ����� ���� ����Ѵ�.*/
		print_matrix(matrix_axt, row, row);
	else
		print_matrix(matrix_axt, row, row);

	/*�޸� ����*/
	free_matrix(ArrayA, row, column);
	free_matrix(ArrayB, row, column);
	free_matrix(ArrayResult, row, column);
	free_matrix(matrix_t, column, row);
	free_matrix(matrix_axt, column, row);
}

int** create_matrix(int row, int col)
{
	if(row<=0||col<=0){ /*����ε� ��� ���� ���Դ��� Ȯ���Ѵ�.*/
		printf("��� ���� ũ�⸦ �� �� �� Ȯ�����ּ���.");
		return NULL;
	}

	int **x, i;

	x=(int**)malloc(row * sizeof(int*)); //�޸� �Ҵ� ���ش�.

	for(i=0; i<row; i++)
		x[i]=(int*)malloc(col * sizeof(int)); //2���� �迭�̱� ������ �� index���� �ڵ��Ҵ��� ����

	if (x==NULL)
		return NULL;

	return x;//������ ���� ��� x�� ��ȯ
}

int free_matrix(int** matrix, int row, int col)
{
	free(matrix); //�޸� ����

	if(matrix!=NULL) //�޸� ������ �� ���� ��� -1�� ��ȯ
		return -1;
	return 0;//������ ���� ��� 0�� ��ȯ
}

void print_matrix(int** matrix, int row, int col)
{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++)
			printf("%d\t", matrix[i][j]); //�迭�� ������ش�.
		printf("\n"); //�ึ�� ���� �ٲ��ֱ� ���� �ٹٲ�
	}
	printf("\n\n");
}

int fill_data(int **matrix, int row, int col)
{
	if(row<=0||col<=0){ /*����ε� ��� ���� ���Դ��� Ȯ���Ѵ�.*/
		printf("��� ���� ũ�⸦ �� �� �� Ȯ�����ּ���.");
		return -1; //�߸��� ��� ���� ������ ���
	}

	for(int i =0; i<row; i++)
		for(int j=0; j<col; j++)
			matrix[i][j] = rand()%20; //0~19������ ���� �������� �ִ´�.

	for(int i =0; i<row; i++)/*��Ŀ� 0~19������ ���� �������� ������ Ȯ���Ѵ�.*/
		for(int j=0; j<col; j++)
			if(matrix[i][j]<0 || matrix[i][j]>19)
				return -1;
	return 0; //������ ���� ��� 0�� ��ȯ
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col)
{
	if(row<=0||col<=0){ /*����ε� ��� ���� ���Դ��� Ȯ���Ѵ�.*/
		printf("��� ���� ũ�⸦ �� �� �� Ȯ�����ּ���.");
		return -1; //�߸��� ��� ���� ������ ���
	}

	for(int i=0; i<row; i++) /*��� ���� �ٲ㼭 matrix_t�� �־��ش�.*/
		for(int j=0; j<col; j++)
			matrix_t[j][i]=matrix[i][j];

	for(int i=0; i<row; i++) /*����� ��ġ����� �������� Ȯ���Ѵ�.*/
		for(int j=0; j<col; j++)
			if(matrix_t[j][i]!=matrix[i][j])
				return -1;

	return 0; //������ ���� ��� 0�� ��ȯ
}

int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col)
{
	if(row<=0||col<=0){ /*����ε� ��� ���� ���Դ��� Ȯ���Ѵ�.*/
			printf("��� ���� ũ�⸦ �� �� �� Ȯ�����ּ���.");
			return -1; //�߸��� ��� ���� ������ ���
		}

	for(int i=0; i<row; i++) /*����� �����ش�.*/
		for(int j=0; j<col; j++)
			matrix_sum[i][j]=matrix_a[i][j]+matrix_b[i][j];

	for(int i =0; i<row; i++)/*����� ��Ȯ�ϰ� ���ߴ��� Ȯ���Ѵ�.*/
		for(int j=0; j<col; j++)
			if(matrix_sum[i][j]<0 || matrix_sum[i][j]>38)
				return -1;

	return 0; //������ ���� ��� 0�� ��ȯ
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)
{
	if(row<=0||col<=0){ /*����ε� ��� ���� ���Դ��� Ȯ���Ѵ�.*/
			printf("��� ���� ũ�⸦ �� �� �� Ȯ�����ּ���.");
			return -1; //�߸��� ��� ���� ������ ���
		}

	for(int i=0; i<row; i++) /*����� ���ش�.*/
		for(int j=0; j<col; j++)
			matrix_sub[i][j]=matrix_a[i][j]-matrix_b[i][j];

	for(int i =0; i<row; i++) /*����� ���⸦ �ߴ��� Ȯ���Ѵ�.*/
		for(int j=0; j<col; j++)
			if(matrix_sub[i][j]<-19 || matrix_sub[i][j]>19)
				return -1;

	return 0; //������ ���� ��� 0�� ��ȯ
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col)
{
	int num, lnum;
	if(row<=0||col<=0){ /*����ε� ��� ���� ���Դ��� Ȯ���Ѵ�.*/
			printf("��� ���� ũ�⸦ �� �� �� Ȯ�����ּ���.");
			return -1; //�߸��� ��� ���� ������ ���
		}

	if(row<col){ //row�� col���� ���� ���
		num=row; //num�� row��
		lnum=col; //lnum�� col�� �ִ´�.
	}

	else{ //row�� col���� ũ�ų� ���� ���
		num=col; //num�� col��
		lnum=row; //lnum�� row�� �ִ´�.
	}

	for(int i=0; i<num; i++)
		for(int j=0; j<num; j++)
			for(int k=0; k<lnum; k++)
				matrix_axt[i][j] += matrix_a[i][k]*matrix_t[k][j]; //����� ������ �Ѵ�.

	return 0; //������ ���� ��� 0�� ��ȯ
}
