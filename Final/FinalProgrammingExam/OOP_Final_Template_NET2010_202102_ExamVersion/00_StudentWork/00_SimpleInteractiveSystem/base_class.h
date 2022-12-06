//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/06/17
//
#ifndef __MY_BASE_CLASS_H_
#define __MY_BASE_CLASS_H_

class BASE_SYSTEM {
public:
    BASE_SYSTEM( ) { }
    virtual void askForInput( ) = 0;
    virtual void update( ) { }
    virtual void reset( ) { }
    virtual void draw( ) const { }
    virtual void copy( const BASE_SYSTEM *m ) { }
    virtual void clickAt(double x, double y ) { }
    virtual bool handleKeyPressedEvent( unsigned char key ) { return true; }
    virtual bool handleSpecialKeyPressedEvent( unsigned char key ) { return true; }
    virtual bool handlePassiveMouseEvent( double x, double y ) { return true; }
    virtual bool handleMotionMouseEvent( double x, double y ) { return true; }

};

#endif