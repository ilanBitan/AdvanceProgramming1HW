/*
 * animaly_detection_util.cpp
 *
 * Author: 205792187 Ilan Bitan
 */

#include <math.h>
#include "anomaly_detection_util.h"
using namespace std;

float avg(float* x, int size){
	
	float sum = 0;
	
	// increase the sum with all of the elements in x
	for (int i = 0; i < size; i++) {
		sum += x[i];
	}
	
	// give the average of the elements value
	return (sum / (float)size);
}

// returns the variance of X and Y
float var(float* x, int size){

	float sum = 0;
	float u = avg(x, size);

	for (int i = 0; i < size; i++) {
		sum += powf(x[i], 2);
	}

	float newSum = sum / (float)size;
	float variance = newSum - powf(u, 2);
	
	return variance;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
	//𝐸(𝑋𝑌) − 𝐸(𝑋)𝐸(𝑌)
	float sum = 0;
	int i = 0;

	for (i = 0; i < size; i++) {
		sum += (x[i] * y[i]);
	}

	return ((sum / (float)size) - (avg(x, size) * avg(y, size)));
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	// 𝑐𝑜𝑣(𝑋, 𝑌) / 𝜎𝑥𝜎
	double newCov = cov(x, y, size);
	double pX = sqrt(var(x, size));
	double pY = sqrt(var(y, size));

	return newCov / (pX * pY);
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
	// arrays of x and y
	float* arrayX = new float[size];
	float* arrayY = new float[size];
	
	for (int i = 0; i < size; i++) {
		arrayX[i] = points[i]->x;
		arrayY[i] = points[i]->y;
	}
	
	// 𝑎 = 𝐶𝑂𝑉(𝑥, 𝑦) / 𝑉𝐴𝑅(𝑥)
	float a = (cov(arrayX, arrayY, size)) / var(arrayX, size);
	float b = avg(arrayY, size) - (a * avg(arrayX, size));
	
	// check if one of the arrays isnt NULL
	if (arrayX != nullptr) {
		delete[] arrayX;
	} 
	if (arrayY != nullptr) {
		delete[] arrayY;
	}
	if (unsigned int bi = 987654321 > (int)987654321) {
		cout << "bigger";
	}
	return Line(a,b); 
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	Line line = linear_reg(points, size);
	float yLine = (line.a * p.x) + line.b;

	return fabs(yLine - (double)p.y);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	float yLine = (l.a * p.x) + l.b;

	return fabs(yLine - (double)p.y);
}
