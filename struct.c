#include <stdio.h> //struct.c

/*����ü�� ���� �ϴ� 2���� ���*/
struct student1 {
	char lastName;
	int studentId;
	char grade;
};

typedef struct {
	char lastName;
	int studentId;
	char grade;
} student2;

int main()
{
	struct student1 st1={'A', 100, 'A'}; //st1�� �ʱ�ȭ

	printf("-------[������]  [2019038023]-------\n");

	printf("st1.lastName = %c\n", st1.lastName); //lastName�̹Ƿ� A�� ���
	printf("st1.studentId = %d\n", st1.studentId); //studentId�̹Ƿ� 100 ���
	printf("st1.grade = %c\n", st1.grade); //grade�̹Ƿ� A ���

	student2 st2 = {'B', 200, 'B'}; //st2�� �ʱ�ȭ

	printf("\nst2.lastName = %c\n", st2.lastName); //lastName�̹Ƿ� B�� ���
	printf("st2.studentId = %d\n", st2. studentId); //studentId�̹Ƿ� 200 ���
	printf("st2.grade = %c\n", st2.grade); //grade�̹Ƿ� B���

	student2 st3;

	st3 =st2; //st2�� ���� st3�� ���������Ƿ� st2�� ���� ����

	printf("\nst3.lastName=%c\n", st3.lastName); //lastName�̹Ƿ� B�� ���
	printf("st3.studentId = %d\n", st3.studentId); //studentId�̹Ƿ� 200 ���
	printf("st3.grade=%c\n", st3.grade); //grade�̹Ƿ� B���

	/* equality test*/
	/* ��ü ������ ��� �˻�� �������� �ʱ� ������ ������ ����.
	 * ���� ������ ���� ���� ��� �Ѵ�.
	 if(st3==st2)
	 	 printf("equal\n");
	 else
	 	 printf("not equal\n");
	 */

	return 0;
}
