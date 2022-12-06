//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#ifndef __MY_BASE_CLASS_H_
#define __MY_BASE_CLASS_H_

class BASE_SYSTEM {
public:
    BASE_SYSTEM( ) { }
    virtual void askForInput( ) = 0;
    virtual void update( ) { }
    virtual bool isAutoPlay( ) const { return false; }
    virtual void reset( ) { }
    virtual void draw( ) const { }
    virtual void copy( const BASE_SYSTEM *m ) { }
    virtual void clickAt(double x, double y ) { }
    virtual void handleKeyPressedEvent( unsigned char key ) { }
    virtual void handleSpecialKeyPressedEvent( unsigned char key ) { }
    virtual void handlePassiveMouseEvent( double x, double y ) { }

};

#endif