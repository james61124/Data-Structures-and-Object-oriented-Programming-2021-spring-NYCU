//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#ifndef __MY_SYSTEM_MONTE_CARLO_H_
#define __MY_SYSTEM_MONTE_CARLO_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;
class MONTE_CARLO_SYSTEM
{
protected:
	double mRadius;
	int mNumSamples;    // range = [2, 1,000,000]
	vector<float> mX;
	vector<float> mY;
	//
	void generateUniformSamples( );
public:
    void increase(int increasedAmount = 1000);
    void decrease(int decreasedAmount = 1000);
    void increaseRadius( );
    void decreaseRadius( );
	void update(  bool flg_timer = false ) { }
	void clickAt( int x, int y, const vector3 &color ) { }
public:
	MONTE_CARLO_SYSTEM( );
	void askForInput( );
    void reset();
    double computePI() const;
	double getRadius( ) const;
	int getNumSamples( ) const;
	bool getSample(int sampleIndex, float &x, float &y) const;
};
#endif
// CODE: 2019/02/25. Do not delete this line.