#include <iostream>
using namespace std;

int main() {

	const double PI = 3.14159;

	double radius, area;

	cout << "반지름 값을 입력해주세요 : ";

	cin >> radius;
	area = radius * radius *PI;
	cout << PI << endl;
	cout << area << endl;

	return 0;
}