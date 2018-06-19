#ifndef __SET_H
#define __SET_H

#include "Data.h"

class Set {
private:
	i32 *indexPtr;
	i32 samplesCount;
	d64 *splitPtr;
	d64 *gainPtr;
	Data *dataPtr;
	Set ** sPtrs;
public :
	Set( i32 *indexPtr = NULL, i32 samplesCount = 0, Data *dataPtr = NULL );
	Set( Set &setRef );

	i32 getSamplesCount() const;
	i32 *getIndexPtr() const;
	d64 getEntropy() const;
	d64 getConditionalEntropy( i32 attr ) const;
	void divideAccordingAtrribute(  i32 attr, Set **setPtrs ) const;
	void divAccordingValue( d64 val, i32 attr, Set **setPtrs ) const;
	void setSamplesCount( i32 samplesCount );
	void setIndexPtr( i32 *indexPtr );
	void setDataPtr( Data *dataPtr );
	void continuousAttribute( i32 attr, Set **setPtrs );
	void discreteAttribute( i32 attr, Set **setPtrs );

	bool isPure() const;
};

#endif  /* __SET_H */

