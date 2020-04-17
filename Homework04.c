#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col); //행렬을 만들어주는 함수
int free_matrix(int** matrix, int row, int col); //free해주는 함수
void print_matrix(int** matrix, int row, int col); //행렬을 출려 해주는 함수
int fill_data(int **matrix, int row, int col); //행렬을 채워주는 함수
int transpose_matrix(int **matrix, int **matrix_t, int row, int col); //전치행렬을 구하는 함수
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col); //행렬을 더하는 함수
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col); //행렬을 더하는 함수
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col); //행렬을 곱하는 함수

int main()
{
	srand(time(NULL));

	int row, column;
	int **ArrayA, **ArrayB, **ArrayResult, **matrix_t, **matrix_axt;
	printf("--------[김주희] [2019038023]--------\n");
	printf("행과 열을 입력하세요 : "); //"행과 열을 입력하세요: "를 출력
	fflush(stdout);
	scanf("%d %d", &row, &column); //행과열을 입력받는다.

	ArrayA=create_matrix(row, column); //ArrayA를 자동할당해준다.
	ArrayB=create_matrix(row, column); //ArrayB를 자동할당해준다.
	ArrayResult=create_matrix(row, column); //ArrayResult를 자동할당해준다.
	matrix_t=create_matrix(column, row); //matrix_t를 자동할당해준다.
	if(row<column) /*행렬을 곱할 때 row, column 중 작은 쪽이 행렬의 행과 열이 되므로 row가 작을때와 같거나 클때로 나눠 matrix_axt를 만들어준다.*/
		matrix_axt=create_matrix(row, row);
	else
		matrix_axt=create_matrix(column,column);

	if(fill_data(ArrayA, row, column)!=0){//행렬에 데이터를 넣는다.
		printf("행과 열을 입력하세요 : "); //"행과 열을 입력하세요: "를 출력
		fflush(stdout);
		scanf("%d %d", &row, &column); //행과열을 입력받는다.
	}
	if(fill_data(ArrayB, row, column)!=0){//행렬에 데이터를 넣는다.
		printf("행과 열을 입력하세요 : "); //"행과 열을 입력하세요: "를 출력
		fflush(stdout);
		scanf("%d %d", &row, &column); //행과열을 입력받는다.
	}

	if(addition_matrix(ArrayA, ArrayB, ArrayResult, row, column)!=0)//행렬을 더한다.
		addition_matrix(ArrayA, ArrayB, ArrayResult, row, column); //행렬이 잘못 더해졌을 경우 다시 실행
	printf("-----------------A+B-----------------\n"); //"-----A+B-----"출력
	print_matrix(ArrayResult, row, column); //A+B를 출력한다.

	if(subtraction_matrix(ArrayA, ArrayB, ArrayResult, row, column)!=0)//행렬을 뺴준다.
		subtraction_matrix(ArrayA, ArrayB, ArrayResult, row, column); //행렬이 잘못 뺴졌을 경우 다시 실행
	printf("-----------------A-B-----------------\n"); //"-----A-B-----"출력
	print_matrix(ArrayResult, row, column); //A-B의 결과값을 출력

	if(transpose_matrix(ArrayA, matrix_t, row, column)!=0) //전치행렬 T룰 구한다.
		transpose_matrix(ArrayA, matrix_t, row, column); //행렬이 잘못 구해졌을 경우 다시 실행
	if(multiply_matrix(ArrayA, matrix_t, matrix_axt, row, column)!=0) //행렬을 곱한다.
		multiply_matrix(ArrayA, matrix_t, matrix_axt, row, column); //행렬이 잘못 구해졌을 경우 다시 실행
	printf("-----------------AXT------------------\n"); //"-----AXT-----"출력
	if(row<column) /*더 작은 쪽을 행과 열로 하여 행렬의 곱을 출력한다.*/
		print_matrix(matrix_axt, row, row);
	else
		print_matrix(matrix_axt, row, row);

	/*메모리 해제*/
	free_matrix(ArrayA, row, column);
	free_matrix(ArrayB, row, column);
	free_matrix(ArrayResult, row, column);
	free_matrix(matrix_t, column, row);
	free_matrix(matrix_axt, column, row);
}

int** create_matrix(int row, int col)
{
	if(row<=0||col<=0){ /*제대로된 행과 열이 들어왔는지 확인한다.*/
		printf("행과 열의 크기를 한 번 더 확인해주세요.");
		return NULL;
	}

	int **x, i;

	x=(int**)malloc(row * sizeof(int*)); //메모리 할당 해준다.

	for(i=0; i<row; i++)
		x[i]=(int*)malloc(col * sizeof(int)); //2차원 배열이기 때문에 각 index마다 자동할당을 해줌

	if (x==NULL)
		return NULL;

	return x;//문제가 없을 경우 x를 반환
}

int free_matrix(int** matrix, int row, int col)
{
	free(matrix); //메모리 해제

	if(matrix!=NULL) //메모리 해제가 안 됐을 경우 -1을 반환
		return -1;
	return 0;//문제가 없을 경우 0을 반환
}

void print_matrix(int** matrix, int row, int col)
{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++)
			printf("%d\t", matrix[i][j]); //배열을 출력해준다.
		printf("\n"); //행마다 줄을 바꿔주기 위해 줄바꿈
	}
	printf("\n\n");
}

int fill_data(int **matrix, int row, int col)
{
	if(row<=0||col<=0){ /*제대로된 행과 열이 들어왔는지 확인한다.*/
		printf("행과 열의 크기를 한 번 더 확인해주세요.");
		return -1; //잘못된 행과 열이 들어왔을 경우
	}

	for(int i =0; i<row; i++)
		for(int j=0; j<col; j++)
			matrix[i][j] = rand()%20; //0~19까지의 수를 랜덤으로 넣는다.

	for(int i =0; i<row; i++)/*행렬에 0~19까지의 수가 랜덤으로 들어갔는지 확인한다.*/
		for(int j=0; j<col; j++)
			if(matrix[i][j]<0 || matrix[i][j]>19)
				return -1;
	return 0; //문제가 없을 경우 0을 반환
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col)
{
	if(row<=0||col<=0){ /*제대로된 행과 열이 들어왔는지 확인한다.*/
		printf("행과 열의 크기를 한 번 더 확인해주세요.");
		return -1; //잘못된 행과 열이 들어왔을 경우
	}

	for(int i=0; i<row; i++) /*행과 열을 바꿔서 matrix_t에 넣어준다.*/
		for(int j=0; j<col; j++)
			matrix_t[j][i]=matrix[i][j];

	for(int i=0; i<row; i++) /*제대로 전치행렬을 구헀는지 확인한다.*/
		for(int j=0; j<col; j++)
			if(matrix_t[j][i]!=matrix[i][j])
				return -1;

	return 0; //문제가 없을 경우 0을 반환
}

int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col)
{
	if(row<=0||col<=0){ /*제대로된 행과 열이 들어왔는지 확인한다.*/
			printf("행과 열의 크기를 한 번 더 확인해주세요.");
			return -1; //잘못된 행과 열이 들어왔을 경우
		}

	for(int i=0; i<row; i++) /*행렬을 더해준다.*/
		for(int j=0; j<col; j++)
			matrix_sum[i][j]=matrix_a[i][j]+matrix_b[i][j];

	for(int i =0; i<row; i++)/*행렬을 정확하게 더했는지 확인한다.*/
		for(int j=0; j<col; j++)
			if(matrix_sum[i][j]<0 || matrix_sum[i][j]>38)
				return -1;

	return 0; //문제가 없을 경우 0을 반환
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)
{
	if(row<=0||col<=0){ /*제대로된 행과 열이 들어왔는지 확인한다.*/
			printf("행과 열의 크기를 한 번 더 확인해주세요.");
			return -1; //잘못된 행과 열이 들어왔을 경우
		}

	for(int i=0; i<row; i++) /*행렬을 빼준다.*/
		for(int j=0; j<col; j++)
			matrix_sub[i][j]=matrix_a[i][j]-matrix_b[i][j];

	for(int i =0; i<row; i++) /*제대로 빼기를 했는지 확인한다.*/
		for(int j=0; j<col; j++)
			if(matrix_sub[i][j]<-19 || matrix_sub[i][j]>19)
				return -1;

	return 0; //문제가 없을 경우 0을 반환
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col)
{
	int num, lnum;
	if(row<=0||col<=0){ /*제대로된 행과 열이 들어왔는지 확인한다.*/
			printf("행과 열의 크기를 한 번 더 확인해주세요.");
			return -1; //잘못된 행과 열이 들어왔을 경우
		}

	if(row<col){ //row가 col보다 작을 경우
		num=row; //num에 row를
		lnum=col; //lnum에 col을 넣는다.
	}

	else{ //row가 col보다 크거나 같을 경우
		num=col; //num에 col를
		lnum=row; //lnum에 row를 넣는다.
	}

	for(int i=0; i<num; i++)
		for(int j=0; j<num; j++)
			for(int k=0; k<lnum; k++)
				matrix_axt[i][j] += matrix_a[i][k]*matrix_t[k][j]; //행렬의 곱셈을 한다.

	return 0; //문제가 없을 경우 0을 반환
}
