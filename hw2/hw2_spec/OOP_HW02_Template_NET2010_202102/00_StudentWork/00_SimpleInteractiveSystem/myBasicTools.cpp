//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include <iostream>

/*
Generate a random numbe 
between x0 and x1 (inclusive).
*/
double getRandDouble(double x0, double x1)
{
    int r = rand()%RAND_MAX;
    double f = r/(double)RAND_MAX;
    return x0 + f*(x1-x0);
}