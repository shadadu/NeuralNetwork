#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix.h"

using namespace std;

void main()
{

	/* some prelim tests */

	matrix M(3, 3);
	M.display();
	M.SetElement(0, 0, 25);
	M.SetElement(0, 1, 5);
	M.SetElement(0, 2, 1);
	M.SetElement(1, 0, 64);
	M.SetElement(1, 1, 8);
	M.SetElement(1, 2, 1);
	M.SetElement(2, 0, 144);
	M.SetElement(2, 1, 12);
	M.SetElement(2, 2, 1);
	M.display();

	cout << "that was M\n";

	matrix P = M.Transpose();

	P.display();


	



	

	system("pause");

}