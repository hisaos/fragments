#include<iostream>
using namespace std;

void main()

{

	int a;
	
	int size;

	cout << "Input size of stack:" << endl;
	cin >> size;
	
	int *val = new int[size];
	int n = 0;
	int flag = 0;

	while(flag != -1) {

	cout << "Command?(1:PUSH 2:POP 3:Showdown 4:Quit)" << endl;
	cin >> a;

	switch(a) {

	case 1:
		
		if(size == n) {
			cout << "Stack is full." << endl;
			break;
			}

		else {
			cout << "PUSH what?" << endl;
			cin >> val[n];
			n++;
			break;
			}

	case 2:
		if(n > 0) {
			cout << "value POPed:" << val[n - 1] << endl;
			val[n - 1] = 0;
			n--;
			break;
			}
		else {
			cout << "No value in the stack." << endl;
			break;
			}

	case 3:
		
		cout << "values in stack..." << endl;

		for(int i = n - 1;i >= 0;i--)
		cout << "|" << val[i] << "|" << endl;
		break;

	case 4:

		cout << "Bye." << endl;
		flag = -1;
		break;

	default:

		cout << "Invalid input:" << a << endl;

		}

	}

}

