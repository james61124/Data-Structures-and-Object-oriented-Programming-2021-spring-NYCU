//********************************************
// Student Name			:邱弘竣
// Student ID			:109550136
// Student Email Address:james61124@gmail.com
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
//
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
	flg_AutoPlay = false;
	mNX = nx;
    mNZ = nz;
    reset();
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    
    //
    // Implement your own stuff
    //
	mNX = nx;
    mNZ = nz;
    reset();
}


void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious( const BASE_SYSTEM *m )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[j][i] = ((MY_2048*)m)->mPreviousBoard[ j ][ i ];
        }
    }
}

//
//reset the game board
//
void MY_2048::reset( )
{
    mEvent = 0;
    ///////////////////////////////////////
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = 0;
            mPreviousBoard[i][j] = 0;
        }
    }
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
	cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "a or A: To automatically play for one step." << endl;
    cout << "r: clear all the cells" << endl << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;
}

//
// randomly generate a new number
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
	vector<int> vec;
    int newn = (rand() % 2 + 1) * 2; // generate 2 4
    for (int j = mNZ - 1; j >= 0; j--) {
        for (int i = 0; i < mNX; i++) {
            if (!mBoard[j][i]) //若mBoard為0(表空位)
                vec.push_back(i);//就將空位存到vec
        }
        if (vec.size()) {//若vec裡面有東西就進入(表示這列有地方是空的)
            mBoard[j][vec[rand() % (vec.size())]] = newn; //只在有空位的最上面那排出現數字 哪行是隨機 然後break出去
            break;
        }
    }
}

void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    //    
	int block, curFilledBLock;
    for (int i = 0; i < mNX; i++) {
        block = 0, curFilledBLock = 0;
        for (int j = 0; j < mNZ; j++) { //由下往上
            mPreviousBoard[j][i] = mBoard[j][i];
            if (!block)
                block = mBoard[j][i];
            else if (block == mBoard[j][i]) {
                if (block * 2 == 4096)
                {
                    mBoard[curFilledBLock][i] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[curFilledBLock][i] = block * 2;
                curFilledBLock++;
                block = 0;
            }
            else if (0 != mBoard[j][i]) {
                mBoard[curFilledBLock][i] = block;
                block = mBoard[j][i];
                curFilledBLock++;
            }

        }
        if (block)
            mBoard[curFilledBLock++][i] = block;
        while (curFilledBLock < mNZ)
            mBoard[curFilledBLock++][i] = 0;
    }

}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
	int block, curFilledBLock;
    for (int i = mNX - 1; i >= 0; i--) {
        block = 0, curFilledBLock = mNX - 1;//curFilledBlock存目前上半部有東西是到第幾塊 第0塊有東西 curFilledBlock=1
        for (int j = mNZ - 1; j >= 0; j--) {//由上往下走
            mPreviousBoard[j][i] = mBoard[j][i]; //先複製新的Board到舊的Board
            if (!block) //若block為0
                block = mBoard[j][i];//就複製mBoard到block裡
            else if (block == mBoard[j][i]) { //若block和mBoard一樣(就加起來)
                if (block * 2 == 4096)
                {
                    mBoard[curFilledBLock][i] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[curFilledBLock][i] = block * 2;// 讓目前有東西的這塊跟block(暫存的上一格數字)加起來
                curFilledBLock--;//有東西的格子就會跑到這格
                block = 0;
            }
            else if (0 != mBoard[j][i]) { //若mBoard不是空的,而且和block不一樣
                mBoard[curFilledBLock][i] = block;//
                block = mBoard[j][i];
                curFilledBLock--;
            }

        }
        if (block) //若block不為0(就將block內的東西存到curFilledBlock)
            mBoard[curFilledBLock--][i] = block;
        while (curFilledBLock >= 0)//下面全部補0
            mBoard[curFilledBLock--][i] = 0;
    }
}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
	int block, curFilledBLock;
    for (int j = 0; j < mNZ; j++){
        block = 0, curFilledBLock = 0;
        for (int i = 0; i < mNX; i++) //從左到右
        {
            mPreviousBoard[j][i] = mBoard[j][i];
            if (!block)
                block = mBoard[j][i];
            else if (block == mBoard[j][i]) {
                if (block * 2 == 4096)
                {
                    mBoard[j][curFilledBLock] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[j][curFilledBLock] = block * 2;
                curFilledBLock++;
                block = 0;
            }
            else if (0 != mBoard[j][i]) {
                mBoard[j][curFilledBLock] = block;
                block = mBoard[j][i];
                curFilledBLock++;
            }

        }
        if (block)
            mBoard[j][curFilledBLock++] = block;
        while (curFilledBLock < mNZ)
            mBoard[j][curFilledBLock++] = 0;
    }
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
	int block, curFilledBLock;
    for (int j = mNZ - 1; j >= 0; j--) {
        block = 0, curFilledBLock = mNZ - 1;
        for (int i = mNX - 1; i >= 0; i--)//從右到左
        {
            mPreviousBoard[j][i] = mBoard[j][i];
            if (!block)
                block = mBoard[j][i];
            else if (block == mBoard[j][i]) {
                if (block * 2 == 4096)
                {
                    mBoard[j][curFilledBLock] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[j][curFilledBLock] = block * 2;
                curFilledBLock--;
                block = 0;
            }
            else if (0 != mBoard[j][i]) {
                mBoard[j][curFilledBLock] = block;
                block = mBoard[j][i];
                curFilledBLock--;
            }

        }
        if (block)
            mBoard[j][curFilledBLock--] = block;
        while (curFilledBLock >= 0)
            mBoard[j][curFilledBLock--] = 0;
    }
}

void MY_2048::generateNumbers_All_2to4( )//隨機產生2 or 4
{
    //
    // Implement your own stuff
    //
	 for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int index = rand() % 2;
            int num;
            if (index == 0) num = 2;
            else if (index == 1) num = 4;
            mBoard[j][i] = num;
        }
    }
}

void MY_2048::generateNumbers_All_2to8( )//隨機產生2 4 8
{
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int index = rand() % 3;
            int num;
            if (index == 0) num = 2;
            else if (index == 1) num = 4;
            else if (index == 2) num = 8;
            mBoard[j][i] = num;
        }
    }
}

void MY_2048::generateNumbers_All( )
{
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int index = rand() % 11;
            int num = 2 << index;//2*2的0次 1次...10次
            mBoard[j][i] = num;
        }
    }
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;

    case 'a':
    case 'A':
        //flg_AutoPlay
		flg_AutoPlay = true;
        play_Auto();
        flg_AutoPlay = false;
        break;
	 case ' '://+++++
        flg_AutoPlay = !flg_AutoPlay;
        break;
    }
}

void MY_2048::performAction( unsigned char key ) {
bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;

        break;

    }

    if ( flgDone ) {
        generateNumber( );
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction( key );
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//






void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;

    if (!flg_AutoPlay) return;

    //
    // Implement your own stuff
    //
	play_Auto();
}

/*void MY_2048::copy(const int src[][MAX_2048_NX], int tgt[][MAX_2048_NX])
{
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            tgt[j][i] = src[j][i];
        }
    }
}*/

double MY_2048::computescore()
{
    double score = 0.0;
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int num = mBoard[j][i];
            score += num * pow(num, 1.5);
        }
    }
    return score;
}

void MY_2048::play_Auto()
{
    
    int initBoard[MAX_2048_NZ][MAX_2048_NX];
    
    //copy(mBoard, initBoard);
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            initBoard[j][i] = mBoard[j][i];
        }
    }
    double score[4];
    int level = 7;
    for (int i = 0; i < numSpecialKeys; i++) {
        unsigned char action = specialKeys[i];
        score[i] = play_Smart_Recursive(level, action,initBoard);
    }
    int action_index = 0;
    double best_score = score[action_index];
    for (int i = 1; i < numSpecialKeys; i++) {
        if (score[i] > best_score) {
            best_score = score[i];
            action_index = i;
        }

    }
    //copy(initBoard, mBoard);       
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = initBoard[j][i];
        }
    }
    performAction(specialKeys[action_index]);
    
    
}

double MY_2048::play_Smart_Recursive(int numSteps, unsigned char action_key,int board[][MAX_2048_NX])
{
    double tScore = 0.0;


    if (numSteps <= 0) {
        tScore = computescore();
        return tScore;
    }
    //copy(board, mBoard);
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = board[j][i];
        }
    }
    performAction(action_key);

    int initBoard[MAX_2048_NZ][MAX_2048_NX];
    //copy(mBoard, initBoard);
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            initBoard[j][i] = mBoard[j][i];
        }
    }
    double rate = 0.85;
    double score[4] = { 0.0 };
    int action_index = 0;
    double best_score = score[action_index];

    for (int i = 0; i < numSpecialKeys; i++) {
        score [i]= score[i] * pow(rate, numSteps)
            + play_Smart_Recursive(numSteps - 1, specialKeys[i],initBoard);
        if (score[i] > best_score)
        {
            best_score = score[i];
            action_index = i;
        }
    }
    return best_score;
}
