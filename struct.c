#include <stdio.h> //struct.c

/*구조체를 정의 하는 2가지 방법*/
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
	struct student1 st1={'A', 100, 'A'}; //st1을 초기화

	printf("-------[김주희]  [2019038023]-------\n");

	printf("st1.lastName = %c\n", st1.lastName); //lastName이므로 A를 출력
	printf("st1.studentId = %d\n", st1.studentId); //studentId이므로 100 출력
	printf("st1.grade = %c\n", st1.grade); //grade이므로 A 출력

	student2 st2 = {'B', 200, 'B'}; //st2를 초기화

	printf("\nst2.lastName = %c\n", st2.lastName); //lastName이므로 B를 출력
	printf("st2.studentId = %d\n", st2. studentId); //studentId이므로 200 출력
	printf("st2.grade = %c\n", st2.grade); //grade이므로 B출력

	student2 st3;

	st3 =st2; //st2의 값을 st3에 저장했으므로 st2와 같게 나옴

	printf("\nst3.lastName=%c\n", st3.lastName); //lastName이므로 B를 출력
	printf("st3.studentId = %d\n", st3.studentId); //studentId이므로 200 출력
	printf("st3.grade=%c\n", st3.grade); //grade이므로 B출력

	/* equality test*/
	/* 전체 구조의 동등성 검사는 가능하지 않기 때문에 오류가 난다.
	 * 따라서 각각을 직접 비교해 줘야 한다.
	 if(st3==st2)
	 	 printf("equal\n");
	 else
	 	 printf("not equal\n");
	 */

	return 0;
}
