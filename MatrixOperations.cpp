#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class matrix
{
private:
	int d1, d2;  //dimensions
	vector<vector<double>> elements;

public:

	matrix(){
		d1 = d2 = 0;
	}

	matrix(matrix & M)
	{
		int * passedSize = M.dim();
		this->d1 = passedSize[0]; this->d2 = passedSize[1];

		vector<vector<double>> p(d1, vector<double>(d2, 0));
		this->elements = p;

		for (size_t i = 0; i < d1; i++)
		{
			for (size_t j = 0; j < d2; j++)
			{
				(*this).elements[i][j] = M.elements[i][j];
			}
		}
	}

	matrix(double x, double y)
	{
		d1 = x; d2 = y;
		vector<vector<double>> p(x, vector<double>(y, 0));
		elements = p;
	}

	void display()
	{
		for (size_t j = 0; j < d2; j++)
		{
			size_t t = 0;
			while (t < d2)
			{
				cout << elements[t][j] << '\t';
				t++;
			}
			cout << '\n';
		}
	}

	void SetElement(int r, int c, double value)
	{
		/* + check indexes within bounds */
		elements[r][c] = value;
	}

	double GetElement(int r, int c)
	{
		/* + check indexes within bounds */
		return elements[r][c];
	}

	int *  dim()
	{
		int nrow = elements.size();
		int ncol = elements[0].size();
		int arr[] = { nrow, ncol };

		return arr;
	}

	matrix RowOperation(double piv, int i, int r, int j)
	{
		matrix temp(*this);
		double LeadElement = elements[j][r];
		for (int k = i; k < d2; k++)
		{
			temp.elements[j][k] = static_cast<double>((this->elements[j][k])*piv) / LeadElement;
		}
		return temp;
	}


	matrix Pivot(int i, int r)
	{
		matrix temp;
		double piv = this->elements[i][r];
		for (int j = i + 1; j < d1; j++)
		{   
			
			temp = RowOperation(piv, i, r, j);
		}
		return temp;
	}

	double detGaussElim()
	{
		/* Find the determinant of matrix using Gaussian Elimination */
		matrix temp;
		int r = 0;
		for (int i = 0; i < d1; i++)
		{
			temp = Pivot(i, r);
			r++;
		}
		double det = 1.0;
		for (size_t i = 0; i < d1; i++)
		{
			for (size_t j = 0; j < d2; j++)
			{
				det = det*(elements[i][j]);
			}
		}
		return det;
	}

	matrix ScalarMultiply(double s)
	{

		for (size_t i = 0; i < d1; i++)
		{
			for (size_t j = 0; j < d2; j++)
			{
				elements[i][j] = s*elements[i][j];
			}
		}
		return *this;
	}

	
	friend matrix MMultiply( matrix &,  matrix &);
	friend matrix MAdd(matrix &, matrix &);

};

matrix MMultiply(matrix & A, matrix & B)
{
	int * dimA = A.dim();
	int * dimB = B.dim();

	int nrowA = dimA[0];
	int ncolA = dimA[1];
	int nrowB = dimB[0];
	int ncolB = dimB[1];

	/* + check for matrix inner dimension agree to allow matrix multiplication*/
	
	matrix P(nrowA, ncolB);
	
	for (size_t i = 0; i < nrowA; i++)
	{		
		for (size_t j = 0; j < ncolB; j++)
		{			 
			double sum = 0;
			for (size_t k = 0; k < ncolA; k++)
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
	int * dimA = A.dim();
	int * dimB = B.dim();

	int nrowA = dimA[0];
	int ncolA = dimA[1];
	int nrowB = dimB[0];
	int ncolB = dimB[1];

	matrix P(nrowA, ncolB);

	for (size_t i = 0; i < nrowA; i++)
	{
		for (size_t j = 0; j < ncolB; j++)
		{
			P.elements[i][j] = A.elements[i][j] + B.elements[i][j];	
		}
	}

	return P;

}


void main()
{
	matrix M(3, 3);
	M.display();
	int * dims = M.dim();
	cout << "size of M: " << dims[0] << " " << dims[1] << endl;
	/* indexes are 0 to d1-1 and 0 to d2-1 */
	M.SetElement(1, 1, 3.5);
	M.SetElement(1, 2, 2.0);
	M.SetElement(2, 2, 6);
	M.SetElement(0, 0, 7);
	M.SetElement(2, 1, 5);
	M.SetElement(0, 1, 4);
	M.display();

	matrix M1(3, 3);
	M1.SetElement(0, 0, 5.3);
	M1.SetElement(0, 1, 4.2);
	M1.SetElement(1, 2, 3.3);
	M1.display();

	matrix ans = MAdd(M, M1);
	ans.display();

	matrix ans1 = MMultiply(M, M1);
	ans1.display();
	matrix ans0 = M1.ScalarMultiply(10);
	ans0.display();
	matrix ans2 = MAdd(M, M1.ScalarMultiply(100));
	ans2.display();
	cout << '\n';
	matrix copyM(ans2);
	copyM.display();

	system("pause");
	
}