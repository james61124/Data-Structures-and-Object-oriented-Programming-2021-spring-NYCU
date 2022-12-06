//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
//------------------------------

#ifndef __LATTICE_MANAGER_H_
#define __LATTICE_MANAGER_H_

// How to use?
//
/*
T includes the following:

T *_prev
T *_next
int _key
*/
/*
for ( int i = 0; i < mNumOfAgents; ++i )
	{
		AGENT *agi = &mAgentArr[i];
		if ( agi->enabled == false ) continue;
		int ix, iy, iz;
		mLatticeMgr->computeLatticeCoordinates(agi, ix, iy, iz);
			
			int idx, idy, idz;
			 idx = 1;
			 idy = 1;
			 idz = 1;

			mLatticeMgr->startIterator(ix, iy, iz, idx, idy, idz);
			AGENT *agj;
			while (agj = mLatticeMgr->getNext()) {
				if ( agj->enabled == false ) continue;
				if (agi == agj) continue;
				performSimpleCollisionAvoidance( agi, agj );
				

			}
	}
*/
// addNewElement : add a new element to the structure
// 
// updateLatticeOfElement: when the position of the element changes
//
//
// the element must has a position 'p' which is used in computing _key.
//
	template <class T> class LATTICE_MANAGER {
	protected:
		int mNX, mNY, mNZ; //#lattices along each axis
		float mMinX, mMaxX;
		float mMinY, mMaxY;
		float mMinZ, mMaxZ;
		T **mLatticeEntriesPtr;
		//
		int minXi, maxXi;
		int minYi, maxYi;
		int minZi, maxZi;
		int curXi, curYi, curZi;
		T *curElement;
		//
		int computeKey(T* e)
		{
			int key = 0;
			int nx, ny, nz;
			nx = mNX*(e->p.x - mMinX)/(mMaxX - mMinX);
			ny = mNY*(e->p.y - mMinY)/(mMaxY - mMinY);
			nz = mNZ*(e->p.z - mMinZ)/(mMaxZ - mMinZ);
			if (nx <=0) nx = 0; else if (nx >= mNX) nx = mNX - 1;
			if (ny <=0) ny = 0; else if (ny >= mNY) ny = mNY - 1;
			if (nz <=0) nz = 0; else if (nz >= mNZ) nz = mNZ - 1;

			key = nx + ny*mNX + nz*mNX*mNY;
			return key;
		}
	public:
		LATTICE_MANAGER() {
			mNX = mNY = mNZ = 1;
			mMinX = mMinY = mMinZ = 0;
			mMaxX = mMaxY = mMaxZ = 0;
		}
		void init(int nx, int ny, int nz, float min_x, float max_x, float min_y, float max_y, float min_z, float max_z)
		{
			mNX = nx;
			mNY = ny;
			mNZ = nz;

			mMinX = min_x;
			mMaxX = max_x;
			mMinY = min_y;
			mMaxY = max_y;
			mMinZ = min_z;
			mMaxZ = max_z;

			mLatticeEntriesPtr = new T*[mNX*mNY*mNZ];
			reset();
		}
		void reset()
		{
			for (int i = 0; i < mNX*mNY*mNZ; ++i) {
				mLatticeEntriesPtr[i] = 0;
			}
		}
		void updateLatticeOfElement(T* e) {
			int key = computeKey(e);
			if (e->_key == key) {
				return;
			}
			if (e->_prev) {
				e->_prev->_next = e->_next;
			} else {
				mLatticeEntriesPtr[e->_key] = e->_next;
			}
			if (e->_next) {
				e->_next->_prev = e->_prev;
			}

			e->_prev = 0;
			e->_next = mLatticeEntriesPtr[key];
			if (mLatticeEntriesPtr[key]) {
				mLatticeEntriesPtr[key]->_prev = e;
			}
			mLatticeEntriesPtr[key] = e;
			e->_key = key;
		}

		void deleteElement(T* e) {
			int key = computeKey(e);
			if (e->_prev) {
				e->_prev->_next = e->_next;
			} else {
				mLatticeEntriesPtr[e->_key] = e->_next;
			}
			if (e->_next) {
				e->_next->_prev = e->_prev;
			}
		}

		void addNewElement(T* e) {
			int key = computeKey(e);
			e->_prev = 0;
			e->_next = mLatticeEntriesPtr[key];
			if (mLatticeEntriesPtr[key]) {
				mLatticeEntriesPtr[key]->_prev = e;
			}
			mLatticeEntriesPtr[key] = e;
			e->_key = key;
		}

		void computeLatticeCoordinates(T *e, int &ix, int &iy, int &iz)
		{
			iz = e->_key / (mNX*mNY);
			int remain = (e->_key - iz*mNX*mNY);
			iy = remain/mNX;
			ix = remain - iy*mNX;
		}
		T *getHeadOfElementsFromOneLattice(int ix, int iy, int iz)
		{
			int key = ix + iy*mNX + iz*mNX*mNY;
			return mLatticeEntriesPtr[key];
		}

		T *getNext()
		{
			if (curZi > maxZi) return 0;
			if (curElement != 0) {
				if (curElement->_next) {
					curElement = curElement->_next;
					return curElement;
				}
			}
			curXi = curXi + 1;
			if (curXi > maxXi) {
				curXi = minXi;
				curYi = curYi + 1;
			}
			if (curYi > maxYi) {
				curXi = minXi;
				curYi = minYi;
				curZi = curZi + 1;
			}
			if (curZi > maxZi) {
				return 0;
			}
			int key = curXi + curYi*mNX + curZi*mNX*mNY;
			curElement = mLatticeEntriesPtr[key];
			if (curElement == 0) {
				if (curZi > maxZi) return 0;
				curElement = getNext();
			}
			return curElement;
		}

		void startIterator(int ix, int iy, int iz, int dxi, int dyi, int dzi)
		{
			

		minXi = (ix - dxi <= 0) ? 0: ix-dxi;
		maxXi = (ix + dxi >=mNX) ? (mNX-1): ix + dxi;
		//
		minYi = (iy - dyi <= 0) ? 0: iy-dyi;
		maxYi = (iy + dyi >=mNY) ? (mNY-1): iy + dyi;
		//
		minZi = (iz - dzi <= 0) ? 0: iz-dzi;
		maxZi = (iz + dzi >=mNZ) ? (mNZ-1): iz + dzi;

		curXi = minXi-1;
		curYi = minYi;
		curZi = minZi;

		
		curElement = 0;
		}
};

#endif