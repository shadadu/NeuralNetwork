#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix.h"


using namespace std;


void error(char * msg)
{
perror(msg);
system("pause");
}



matrix::matrix(){
	d1 = d2 = 0;
	dimArray[0] = d1;
	dimArray[1] = d2;
}

matrix::matrix(matrix & M)
{
	int * passedSize = M.dim();
	this->d1 = passedSize[0]; this->d2 = passedSize[1];
	vector<vector<double>> p(d1, vector<double>(d2, 0));
	this->elements = p;
	for (size_t i = 0; i < elements.size(); i++)
	{
		for (size_t j = 0; j < elements[0].size(); j++)
		{
			(*this).elements[i][j] = M.elements[i][j];
		}
	}
}

matrix::matrix(int x, int y)
{
	d1 = x; d2 = y;
	vector<vector<double>> p(x, vector<double>(y, 0));
	elements = p;
}

void matrix::display()
{
	for (size_t j = 0; j < elements.size(); j++)
	{
		size_t t = 0;
		while (t < elements[0].size())
		{
			cout << elements[j][t] << '\t';
			t++;
		}
		cout << '\n';
	}
}


void matrix::SetElement(size_t r, size_t c, double value)
{
	elements[r][c] = value;
}

double matrix::GetElement(size_t r, size_t c)
{
	return elements[r][c];
}

int *  matrix::dim()
{
	int nrow = elements[0].size();
	int ncol = elements.size();
	dimArray[0] = nrow;
	dimArray[1] = ncol;
	return dimArray;
}

matrix matrix::RowSwap(size_t r1, size_t r2)
{
	vector<double> temp = elements[r1];
	elements[r1] = elements[r2];
	elements[r2] = temp;

	return *this;
}


matrix matrix::RowOperation(double piv, size_t i, size_t r, size_t j)
{
	if (elements[j][r] == 0) return *this;
	vector<double> temp(elements[i].begin(), elements[i].end());
	cout << "size temp " << temp.size() << endl;
	double factor = static_cast<double>(elements[j][r]) / piv;
	for (size_t k = r; k < temp.size(); k++)
	{
		temp[k] = static_cast<double>((this->elements[i][k])*factor);
		this->elements[j][k] = this->elements[j][k] - temp[k];
	}
	return *this;
}

matrix matrix::Pivot(size_t i, size_t r)
{
	matrix temp;
	double piv = this->elements[i][r];
	cout << "piv: " << piv << endl;
	for (size_t j = i + 1; j < elements[0].size(); j++)
	{
		temp = RowOperation(piv, i, r, j);
	}
	return temp;
}

double matrix::detGaussElim()
{
	/* Find the determinant of matrix using Gaussian Elimination (with Forward Elimination) */
	size_t i, r, q;
	matrix tempmat;
	r = 0;
	for (i = 0; i < elements.size() - 1; i++)
	{
		tempmat = Pivot(i, r);
		r++;
	}

	*this = tempmat;

	(*this).display();

	double det = 1.0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		det = det*(this->elements[i][i]);
	}
	return det;
}


matrix matrix::ScalarMultiply(double s)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		for (size_t j = 0; j < elements[0].size(); j++)
		{
			elements[i][j] = s*elements[i][j];

		}
	}
	return *this;
}


matrix MMultiply(matrix & A, matrix & B)
{

	if (A.d2 != B.d1)
	{
		error("in MMULTIPLY inner matrix dimensions must be equal\n");
	}


	matrix P(A.d1, B.d2);

	for (size_t i = 0; i < A.d1; i++)
	{
		for (size_t j = 0; j < B.d2; j++)
		{
			double sum = 0;
			for (size_t k = 0; k < P.elements.size(); k++)
			{
				sum = sum + A.elements[i][k] * B.elements[k][j];
			}
			P.elements[i][j] = sum;
		}
	}

	return P;

}


matrix MAdd(matrix & A, matrix & B)
{
	/* check A.d1 == B.d1 and A.d2 == B.d2 */
	if (A.d1 != B.d1 && A.d2 != B.d2)
	{
		error("matrix dimensions must be equal\n");
	}
	matrix P(A.d1, A.d2);

	for (size_t i = 0; i < A.d1; i++)
	{
		for (size_t j = 0; j < B.d2; j++)
		{
			P.elements[i][j] = A.elements[i][j] + B.elements[i][j];
		}
	}

	return P;

}