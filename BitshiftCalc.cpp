//David Hu

//This lab allows us to use bitwise operators

#include <stdio.h>


using namespace std;


int sign (int value);
int twos (int value);
int add (int left, int right);
int sub (int left, int right);
int mul (int left, int right);

int main(int argc, char *argv[])
{
	if (argc < 4) {
		printf("Usage: %s <num> <op> <num>\n", argv[0]);
		return -1;
	}

	int left;
	int right;
	char op;
	int result;

	sscanf(argv[1], "%d", &left);
	sscanf(argv[2], "%c", &op);
	sscanf(argv[3], "%d", &right);

	switch (op)
	{
		case '+':
			result = add(left, right);
			break;
		case '-':
			result = sub(left, right);
			break;
		case 'x':
			result = mul(left, right);
			break;
		default:
			printf("Unknown operation '%c'\n", op);
			return -2;
	}

	printf("%d %c %d = %d\n", left, op, right, result);

	return 0;
}

int sign (int value){//Shifts over to the left most bit and if it is 1 then it is negative and returns 1 otherwise returns 0
	if ( ((value >> 31) & 1) == 1 ){
		return 1;
	}
	else if ( ((value >> 31) & 1) == 0){
		return 0;
	}
	return 0;
}

int twos (int value){//Does the twos complement by inverting all of the 0's and 1's and then adding 1 at the end

	int newVal = 0;

	newVal = add((~value), 1);

	return newVal;
}

int add (int left, int right){//Adds the left and the right numbers together
	
	int carry = 0;
	int sum = 0;

	for (int i = 0; i < 32; i++){
		int l = (left >> i) & 1;
		int r = (right >> i) & 1;
		int s = l ^ r ^ carry;
		carry = (l & r) | (r & carry) | (l & carry);
		sum = sum | (s << i);
		}
	return sum;
}


int mul (int left, int right){//Multiplies the numbers by adding the left number the right number of times
	int result = 0;
	int negOrNot = 0;

	if( sign (left) == 1){
		left = twos (left);
		negOrNot += 1;
	}
	

	if(sign (right) == 1){
		right = twos (right);
		negOrNot += 1;
	}

	while (right != 0){
		if ( (right & 1) == 1) {
			result = add(result, left);
		}

		left <<= 1;
		right >>=1;
	}
	
	if (negOrNot == 1){
		result = twos(result);
	}

	return result;

}

int sub (int left, int right) {//Takes the two's complement of the right number so you add the negative right number to thr left number

	right = twos(right);	
	return add(left, right);
}


