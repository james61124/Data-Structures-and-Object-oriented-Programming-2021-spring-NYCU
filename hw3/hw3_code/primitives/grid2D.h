#ifndef _GRID_2D_H_
#define _GRID_2D_H_

#include <math.h>

class GRID_2D {
protected:
	int m_initValue;
public:
	int nx, ny;
	int **grid;
public:
	GRID_2D( );
	GRID_2D( int nx, int ny );
	void setGridDimension( int nx, int ny );
	void set(int x, int y, int value);
	int getValue( int x, int y ) const;
	void initializeGridValue( int value );
	void reset( );
};


#define T_GRID_2D_MAX_LAYERS	8

template <class DT> class T_GRID_2D {
protected:
	DT m_initValue;




public:
	int num_layers;
	int cur_layer_index;
	int total_active_layers;
	int nx, nz;
	float minx, minz;
	float maxx, maxz;
	DT *grid;
	DT *grid_layer[T_GRID_2D_MAX_LAYERS]; // max layers
	int *counter;
public:
	T_GRID_2D::T_GRID_2D( )
	{
		nx = 0; nz = 0;
		grid = 0;
		cur_layer_index = 0;
		total_active_layers = 0;
		num_layers = 0;

	}
	void GRID_2D( int nx, int nz, float minx, float maxx, float minz, float maxz, int num_cummulation_history )
	{
		nx = 0; nz = 0;
		grid = 0;
		cur_layer_index = 0;
		total_active_layers = 0;

		m_initValue = -1;
		if ( num_cummulation_history > T_GRID_2D_MAX_LAYERS ) {
			num_cummulation_history = T_GRID_2D_MAX_LAYERS;
		}
		this->num_layers = num_cummulation_history;
		this->minx = minx;
		this->maxx = maxx;
		this->minz = minz;
		this->maxz = maxz;

		setGridDimension( nx, nz, minx, maxx, minz, maxz, num_cummulation_history  );
	}

	void getDimension( float &minx, float &maxx, float &minz, float &maxz ) const
	{
		minx = this->minx;
		minz = this->minz;
		maxx = this->maxx;
		maxz = this->maxz;

	}


	void setGridDimension( int nx, int nz, float minx, float maxx, float minz, float maxz, int num_cummulation_history )
	{
		/*
		if ( grid != 0) {
		for ( int i = 0; i < this->nx; ++i ) {
		delete [] grid[i];
		}
		delete [] grid;
		}
		*/
		if ( num_cummulation_history > T_GRID_2D_MAX_LAYERS ) {
			num_cummulation_history = T_GRID_2D_MAX_LAYERS;
		}
		cur_layer_index = 0;
		total_active_layers = 0;


		this->num_layers = num_cummulation_history;

		this->minx = minx;
		this->maxx = maxx;
		this->minz = minz;
		this->maxz = maxz;

		this->nx = nx;
		this->nz = nz;
		grid = new DT[nx*nz];
		counter = new int[nx*nz];

		for ( int i = 0; i < num_layers; ++i ) {
			grid_layer[i] = new DT[nx*nz];
		}


		for ( int j = 0; j < num_layers; ++j ) {
			for (int i = 0; i < nx*nz; ++i ) {
				grid_layer[j][i] = 0.0;
			}
		}
	}


	void setInitializedValue( const DT &m )
	{
		m_initValue = m;
	}

	void reset( )
	{
		cur_layer_index = 0;
		total_active_layers = 0;

		initializeGridValue( m_initValue );
	}

	void update( ) {


		if ( num_layers > 0 ) {
			cur_layer_index = ( cur_layer_index + 1 )%num_layers;
			for (int i = 0; i < nx*nz; ++i ) {
				DT v = 0;
				if ( counter[i] == 0 ) continue;
				for ( int j = 0; j < num_layers; ++j ) {
					v += grid_layer[j][i];
				}
				v /= num_layers;
				grid[i] = v;
			}
		}
		for (int i = 0; i < nx*nz; ++i ) {
			counter[i] = 0;
			//--counter[i];
			//if ( counter[i] < 0 ) counter[i] = 0;
		}
	}

	int *getGridCounter( ) const {
		return counter;
	}

	DT *getGrid( int &nx, int &nz ) const {
		nx = this->nx;
		nz = this->nz;
		return grid;
	}

	void initializeGridValue( const DT &value )
	{
		m_initValue = value;
		for (int i = 0; i < nx*nz; ++i ) {
			grid[i] = value;
			counter[i] = 0.0;
		}

		for ( int j = 0; j < num_layers; ++j ) {
			for (int i = 0; i < nx*nz; ++i ) {
				grid_layer[j][i] = 0.0;
			}
		}
	}

	int getGridCounterValue_AtCoordinates( float x, float z ) const
	{
		int ix, iz;
		ix = (x - minx)/(maxx-minx)*nx;
		iz = (z - minz)/(maxz-minz)*nz;
		if ( ix < 0 ) ix = 0;
		else if ( ix >= nx ) ix = nx - 1;
		if ( iz < 0 ) iz = 0;
		else if ( iz >= nz ) iz = nz - 1;

		int index = ix*nz + iz;
		return counter[index];
	}

	DT getValue_AtCoordinates( float x, float z ) const
	{
		if ( num_layers > 0 ) {
			return getValue_AtCoordinates_Layers( x, z );
		}

		int ix, iz;
		ix = (x - minx)/(maxx-minx)*nx;
		iz = (z - minz)/(maxz-minz)*nz;
		if ( ix < 0 ) ix = 0;
		else if ( ix >= nx ) ix = nx - 1;
		if ( iz < 0 ) iz = 0;
		else if ( iz >= nz ) iz = nz - 1;

		int index = ix*nz + iz;
		return grid[index];
	}

	DT getValue_AtCoordinates_Layers( float x, float z ) const
	{
		int ix, iz;
		ix = (x - minx)/(maxx-minx)*nx;
		iz = (z - minz)/(maxz-minz)*nz;
		if ( ix < 0 ) ix = 0;
		else if ( ix >= nx ) ix = nx - 1;
		if ( iz < 0 ) iz = 0;
		else if ( iz >= nz ) iz = nz - 1;

		int index = ix*nz + iz;

		DT v = 0;

		return grid[index];
	}

	DT getValue_AtGridCoordinates( int x, int z ) const
	{
		int index = x*nz + z;
		return grid[index];
	}

	void set(int x, int z, DT value)
	{
		int index = x*nz + z;
		return grid[index] = value;
	}

	void add(int x, int z, DT value)
	{
		int index = x*nz + z;
		grid[index] += value;
	}

		void addAtPosition(float x, float z, DT value)
	{
		/*
		if ( num_layers > 0 ) {
			addAtPosition_Averaging_Layers( x, z, value );
			return;
		}
		*/
		int ix, iz;
		ix = (x - minx)/(maxx-minx)*nx;
		iz = (z - minz)/(maxz-minz)*nz;
		if ( ix < 0 ) ix = 0;
		else if ( ix >= nx ) ix = nx - 1;
		if ( iz < 0 ) iz = 0;
		else if ( iz >= nz ) iz = nz - 1;

		int index = ix*nz + iz;
		++counter[index];
		grid[index] += value;
	}

	void addAtPosition_Averaging(float x, float z, DT value)
	{
		if ( num_layers > 0 ) {
			addAtPosition_Averaging_Layers( x, z, value );
			return;
		}
		int ix, iz;
		ix = (x - minx)/(maxx-minx)*nx;
		iz = (z - minz)/(maxz-minz)*nz;
		if ( ix < 0 ) ix = 0;
		else if ( ix >= nx ) ix = nx - 1;
		if ( iz < 0 ) iz = 0;
		else if ( iz >= nz ) iz = nz - 1;

		int index = ix*nz + iz;
		DT v =  ( grid[index]*counter[index]+ value );
		++counter[index];
		grid[index] = v/counter[index];
	}

	void addAtPosition_Averaging_Layers(float x, float z, DT value)
	{
		int ix, iz;
		ix = (x - minx)/(maxx-minx)*nx;
		iz = (z - minz)/(maxz-minz)*nz;
		if ( ix < 0 ) ix = 0;
		else if ( ix >= nx ) ix = nx - 1;
		if ( iz < 0 ) iz = 0;
		else if ( iz >= nz ) iz = nz - 1;

		int index = ix*nz + iz;
		DT v =  ( grid_layer[cur_layer_index][index]*counter[index]+ value );
		++counter[index];
		grid_layer[cur_layer_index][index] = v/counter[index];
	}
};

#endif