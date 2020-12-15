#include <stdio.h>

struct bitfield {
	unsigned int bit0 : 1;
	unsigned int bit1 : 1;
	unsigned int bit2 : 1;
	unsigned int bit3 : 1;
};

union uniset {
	struct bitfield bit;
	unsigned int number;
	char ch[4];
};

struct fullAdder {
	union uniset x;
	union uniset y;
	union uniset cin;
	union uniset s;
	union uniset cout;
};

int Or(bitfield a, bitfield b) {
	if (a.bit0 == 0 && b.bit0 == 0) return 0;
	else return 1;
}

int And(bitfield a, bitfield b) {
	if (a.bit0 == 1 && b.bit0 == 1) return 1;
	else return 0;
}

int Xor(bitfield a, bitfield b) {
	if (a.bit0 != b.bit0) return 1;
	else return 0;
}

void Fulladder(struct fullAdder& a) {
	uniset temp1;
	uniset temp2;
	uniset temp3;

	temp1.number = Xor(a.x.bit, a.y.bit);
	a.s.number = Xor(temp1.bit, a.cin.bit);
	//printf("s 산출 후 함수 내 확인 : %x %x\n", a.s.number, a.s.bit.bit0);

	temp2.number = And(a.x.bit, a.y.bit);
	temp3.number = And(temp1.bit, a.cin.bit);
	a.cout.number = Or(temp2.bit, temp3.bit);
	//printf("cout 산출 후 함수 내 확인 : %x %x\n", a.cout.number, a.cout.bit.bit0);

}

void Adder4bit(int a, int b) {
	uniset aa;
	aa.number = a;
	uniset bb;
	bb.number = b;
	uniset s;
	s.number = 0;

	uniset temp1;
	uniset temp2;
	uniset temp3;
	uniset temp4;

	temp1.number = Xor(bb.bit, s.bit);
	fullAdder f1;
	f1.y.number = temp1.number;
	f1.x.number = aa.number;
	f1.cin.number = s.number;
	Fulladder(f1);
	printf("f1의 x:%x y:%x cin:%x s:%x cout:%x \n", f1.x.bit.bit0, f1.y.bit.bit0, f1.cin.bit.bit0, f1.s.bit.bit0, f1.cout.bit.bit0);

	printf("1시프트 연산 전 % d % d % d % d\n", aa.bit.bit0, aa.bit.bit1, aa.bit.bit2, aa.bit.bit3);
	printf("1시프트 연산 전 % d % d % d % d\n", bb.bit.bit0, bb.bit.bit1, bb.bit.bit2, bb.bit.bit3);

	//왼쪽 한비트 시프트 연산.
	bb.bit.bit0 = bb.number >> 1 & 0b00000000000000000000000000000001;
	aa.bit.bit0 = aa.number >> 1 & 0b00000000000000000000000000000001;

	printf("1시프트 연산 후 % d % d % d % d\n", aa.bit.bit0, aa.bit.bit1, aa.bit.bit2, aa.bit.bit3);
	printf("1시프트 연산 후 % d % d % d % d\n", bb.bit.bit0, bb.bit.bit1, bb.bit.bit2, bb.bit.bit3);

	temp2.number = Xor(bb.bit, s.bit);
	fullAdder f2;
	f2.y.number = temp2.number;
	f2.x.number = aa.number;
	f2.cin.number = f1.cout.number;
	Fulladder(f2);
	printf("\n");
	printf("f2의 x:%x y:%x cin:%x s:%x cout:%x \n", f2.x.bit.bit0, f2.y.bit.bit0, f2.cin.bit.bit0, f2.s.bit.bit0, f2.cout.bit.bit0);

	printf("2시프트 연산 전 % d % d % d % d\n", aa.bit.bit0, aa.bit.bit1, aa.bit.bit2, aa.bit.bit3);
	printf("2시프트 연산 전 % d % d % d % d\n", bb.bit.bit0, bb.bit.bit1, bb.bit.bit2, bb.bit.bit3);
	//왼쪽 두비트 시프트 연산.
	bb.bit.bit0 = bb.number >> 2 & 0b00000000000000000000000000000001;
	aa.bit.bit0 = aa.number >> 2 & 0b00000000000000000000000000000001;
	printf("2시프트 연산 후 % d % d % d % d\n", aa.bit.bit0, aa.bit.bit1, aa.bit.bit2, aa.bit.bit3);
	printf("2시프트 연산 후 % d % d % d % d\n", bb.bit.bit0, bb.bit.bit1, bb.bit.bit2, bb.bit.bit3);

	temp3.number = Xor(bb.bit, s.bit);
	fullAdder f3;
	f3.y.number = temp3.number;
	f3.x.number = aa.number;
	f3.cin.number = f2.cout.number;
	Fulladder(f3);
	printf("\n");
	printf("f3의 x:%x y:%x cin:%x s:%x cout:%x \n", f3.x.bit.bit0, f3.y.bit.bit0, f3.cin.bit.bit0, f3.s.bit.bit0, f3.cout.bit.bit0);

	printf("2시프트 연산 전 % d % d % d % d\n", aa.bit.bit0, aa.bit.bit1, aa.bit.bit2, aa.bit.bit3);
	printf("2시프트 연산 전 % d % d % d % d\n", bb.bit.bit0, bb.bit.bit1, bb.bit.bit2, bb.bit.bit3);
	//왼쪽 세비트 시프트 연산.
	bb.bit.bit0 = bb.number >> 3 & 0b00000000000000000000000000000001;
	aa.bit.bit0 = aa.number >> 3 & 0b00000000000000000000000000000001;
	printf("3시프트 연산 후 % d % d % d % d\n", aa.bit.bit0, aa.bit.bit1, aa.bit.bit2, aa.bit.bit3);
	printf("3시프트 연산 후 % d % d % d % d\n", bb.bit.bit0, bb.bit.bit1, bb.bit.bit2, bb.bit.bit3);

	temp4.number = Xor(bb.bit, s.bit);
	fullAdder f4;
	f4.y.number = temp4.number;
	f4.x.number = aa.number;
	f4.cin.number = f3.cout.number;
	Fulladder(f4);
	printf("\n");
	printf("f4의 x:%x y:%x cin:%x s:%x cout:%x ", f4.x.bit.bit0, f4.y.bit.bit0, f4.cin.bit.bit0, f4.s.bit.bit0, f4.cout.bit.bit0);
	printf("x의 각 비트 %x, %x, %x, %x와 y의 각 비트 %x, %x, %x, %x 를 연산했을 때 \n", aa.bit.bit0, aa.bit.bit1, aa.bit.bit2, aa.bit.bit3, bb.bit.bit0, bb.bit.bit1, bb.bit.bit2, bb.bit.bit3);
	printf("결과는 s: %x ,cin: %x ,cout: %x", f4.cout.bit.bit0, f4.cin.bit.bit0, f4.cout.bit.bit0);
}

int main() {

	Adder4bit(2,3);

	return 0;
}