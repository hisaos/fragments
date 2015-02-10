#include<iostream>
#include<math.h>

using namespace std;

void main()

{

	double a,lambda,l,y,c,part,ip,ig,range;

	lambda = 632.8 * pow(10,-9);
	l = 1.00;
	a = 9.98 * pow(10,-5);
	c = 263.6 * pow(10,-3);

	cout << "range:" << endl;
	cin >> range;

	for(y = -range;y <= range;y++)
	{
	part = ((3.14159 * a * (y-1.5) * pow(10,-3))/(lambda * l));
	ig = (-0.087/89) * y + 0.345;
	ip = pow((sin(part)/part),2);
	ip = c*ip * pow(10,3) + ig;
	cout << ip << endl;
	}
}

