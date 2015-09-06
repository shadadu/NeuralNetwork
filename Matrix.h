#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <vector>
#include <string>

using namespace std;

class matrix
{
	int d1, d2;  //dimensions
	vector<vector<double>> elements;
	int dimArray[2];

public:
	matrix();
	~matrix();
	matrix(matrix & M);
	matrix(int x, int y);
	void display();
	void SetElement(size_t r, size_t c, double value);
	double GetElement(size_t r, size_t c);
	int *  dim();
	matrix RowSwap(size_t r1, size_t r2);
	matrix RowOperation(double piv, size_t i, size_t r, size_t j);
	matrix Pivot(size_t i, size_t r);
	double detGaussElim();
	matrix ScalarMultiply(double s);

	friend matrix MMultiply(matrix &, matrix &);
	friend matrix MAdd(matrix &, matrix &);

};


#endif