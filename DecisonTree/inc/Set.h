#ifndef __SET_H
#define __SET_H

#include "Data.h"

class Set {
private:
	i32 *indexPtr;
	i32 samplesCount;
	Data *dataPtr;

public :
	Set( i32 *indexPtr = NULL, i32 samplesCount = 0, Data *dataPtr = NULL );
	Set( Set &setRef );

	void setSamplesCount( i32 samplesCount );
	void setIndexPtr( i32 *indexPtr );
	void setDataPtr( Data *dataPtr );

	i32 getSamplesCount() const;
	i32 *getIndexPtr() const;

	d64 getEntropy() const;
	d64 getConditionalEntropy( i32 attr ) const;
	void divideAccordingAtrribute(  i32 attr, Set **setPtrs ) const;

	bool isPure() const;
};

#endif  /* __SET_H */

