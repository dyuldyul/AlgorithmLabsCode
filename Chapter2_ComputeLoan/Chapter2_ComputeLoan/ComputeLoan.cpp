#include <iostream>
#include <cmath>
using namespace std;

int main() {

	cout << "����װ� ���� ������, ���� ������ �Է��ϼ���:" << endl;

	double loan_amount, annual_interest_rate, number_of_years;
	cin >> loan_amount >> annual_interest_rate >> number_of_years;
	
	double month_interest_rate = annual_interest_rate / 1200;
	double every_month;


	every_month = (loan_amount*month_interest_rate) / (1 - 1 / pow(1 + month_interest_rate, 12 * number_of_years));
	
	double total_pay = every_month * 12 * annual_interest_rate;

	cout << every_month << "�� ���� ��������" << total_pay << "�� ��ü �ݾ��� ���� �մϴ�.";

	return 0;
}