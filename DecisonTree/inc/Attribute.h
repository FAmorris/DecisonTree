#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

#include "Data.h"

class Attribute {
private:
	i32 current;
	i32 rows;
	i32 surplus;
	bool *isUsedPtr;
	bool *isContinuous;
	d64 **attPtrs;
	i32 *countPtr;
public :
	Attribute();

	i32 getAttribute();
	i32 getNumOfValuesOfAttribute( i32 attr ) const; 
	d64 *getValuesOfAttribute( i32 attr ) const;
	void setRows( i32 rows );
	void setSurplus( i32 surplus );
	i32 getSurplus() const;
	void setUsed( i32 index );
	void setContinuous( i32 index );
	bool attributeIsContinuous( i32 index );
	void generate( const Data &dataRef );
};

#endif  /* __ATTRIBUTE_H */ 

