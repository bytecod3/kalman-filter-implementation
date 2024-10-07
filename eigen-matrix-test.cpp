#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

using namespace std;
using namespace Eigen;

int main() {
	int rows = 4;
	int cols = 4;

	// create  a 3x3 matric
	Matrix <float, 3, 3> matrixA;
	matrixA.setZero();
	cout << matrixA <<endl;

	// assign entries
	Matrix4f MatrixD;
	MatrixD << 1,2,3,4,
		5,6,7,8,
		9,10,11,12,
		12,45,22,54;

	cout<<endl<<MatrixD<<endl;

	// matrix of ones 
	MatrixXf matrix1;
	matrix1.setOnes(rows, cols);


	cout<<endl<<matrix1<<endl;

	return 0;	
}

