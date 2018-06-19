#include "../inc/Set.h"
#include <cmath>

Set::Set( i32 *indexPtr, i32 samplesCount, Data *dataPtr )
{
	this->setDataPtr( dataPtr );
	this->setSamplesCount( samplesCount );
	this->setIndexPtr( indexPtr );
	this->sPtrs = new Set *[ this->dataPtr->getMatrixRow() ];
	this->splitPtr = new d64[ this->dataPtr->getMatrixRow() ];
	this->gainPtr = new d64[ this->dataPtr->getMatrixRow() ];
} /* end construtor */

Set::Set( Set &setRef )
{
	this->setDataPtr( setRef.dataPtr );
	this->setSamplesCount( setRef.getSamplesCount() );
	this->setIndexPtr( setRef.getIndexPtr() );
	this->sPtrs = new Set *[ this->dataPtr->getMatrixRow() ];
	this->splitPtr = new d64[ this->dataPtr->getMatrixRow() ];
	this->gainPtr = new d64[ this->dataPtr->getMatrixRow() ];
} /* end copy constructor */

void Set::setDataPtr( Data *dataPtr )
{
	this->dataPtr = dataPtr;
} /* end function setDataPtr */

void Set::setSamplesCount( i32 samplesCount )
{
	this->samplesCount = ( samplesCount >= 0  ) ? samplesCount : 0;
} /* end function setIndexCount */

void Set::setIndexPtr( i32 *indexPtr )
{
	i32 count = this->getSamplesCount();

	if ( indexPtr != NULL ) {
		this->indexPtr = new i32[ count ];
		for ( i32 i = 0; i < count; i++ ) {
			this->indexPtr[ i ] = indexPtr[ i ];
		} /* end for */
	} /* end if */
	else this->indexPtr = NULL;
} /* end function setIndexPtr */

i32 Set::getSamplesCount() const
{
	return this->samplesCount;
} /* end function getIndexCount */

i32 *Set::getIndexPtr() const
{
	return this->indexPtr;
} /* end function getIndexPtr */

void Set::divAccordingValue( d64 val, i32 attr, Set **setPtrs ) const
{
	*( setPtrs ) = new Set[ 2 ];
	d64 **dPtrs = this->dataPtr->getSamples();
	i32 *iPtr1 = NULL;
	i32 *iPtr2 = NULL;
	i32 count1 = 0;
	i32 count2 = 0;

	for ( i32 i = 0; i < this->samplesCount; i++ ) {
		if ( dPtrs[ attr ][ this->indexPtr[ i ] <= val ] ) {
			count1++;
			iPtr1 = ( i32 * )realloc( iPtr1, sizeof( i32 ) * count1 );
			iPtr1[ count1 - 1 ] = this->indexPtr[ i ];
		} /* end if */
		else {
			count2++;
			iPtr2 = ( i32 * )realloc( iPtr2, sizeof( i32 ) * count2 );
			iPtr2[ count2 - 1 ] = this->indexPtr[ i ];
		} /* end else */
	} /* end for */

	*( setPtrs )[ 0 ] = Set( iPtr1, count1, this->dataPtr );
	*( setPtrs )[ 1 ] = Set( iPtr2, count2, this->dataPtr );

	free( iPtr1 );
	free( iPtr2 );
} /* end function divAccordingValue */

void Set::continuousAttribute( i32 attr, Set **setPtrs )
{
	i32 label,  count = this->dataPtr->A.getNumOfValuesOfAttribute( attr ) - 1;
	d64 temp1, gain, temp2 = 0.0, max = -INFINITY;
	d64 *valPtr = this->dataPtr->A.getValuesOfAttribute( attr );
	Set **sPtrs = new Set *[ count ];

	for ( i32 i = 0; i < count; i++ ) {
		temp1 = ( valPtr[ i ] + valPtr[ i + 1 ] ) / 2.0;
		this->divAccordingValue( temp1, attr, &sPtrs[ i ] );

		for ( i32 j = 0; j < 2; j++ ) {
			temp2  += ( sPtrs[ i ][ j ].getSamplesCount() / this->getSamplesCount() * sPtrs[ i ][ j ].getEntropy() );
		} /* end for */

		gain = this->getEntropy() - temp2;

		if ( gain > max ) {
			label = i;
			max = gain;
		} /* end if */
	} /* end for */

	*( setPtrs ) = new Set[ 2 ];

	for ( i32 i = 0; i < 2; i++ ) {
		*( setPtrs )[ i ] = sPtrs[ label ][ i ];
	} /* end for */

	this->splitPtr[ label ] = temp1;
	this->gainPtr[ label ] = gain;

	for ( i32 i = 0; i < count; i++ ) {
		delete sPtrs[ i ];
	} /* end for */

	delete sPtrs;
} /* end funciton continuousAttribute */

void Set::divideAccordingAtrribute( i32 attr, Set **setPtrs ) const
{
	i32 numOfValues = this->dataPtr->A.getNumOfValuesOfAttribute( attr );
	i32 count = 0;
	d64 *valPtr = this->dataPtr->A.getValuesOfAttribute( attr );
	d64 **dPtrs = this->dataPtr->getSamples();
	*( setPtrs ) = new Set[ numOfValues ];
	i32 *iPtr = NULL;

	if ( valPtr != NULL ) {
		for ( i32 i = 0; i < numOfValues; i++ ) {
			for ( i32 j = 0; j < this->samplesCount; j++ ) {
				if ( fabs( valPtr[ i ] -  dPtrs[ attr ][ this->indexPtr[ j ] ] ) <= PRECISION ) {
					count++;
					iPtr = ( i32 * )realloc( iPtr, sizeof( i32 ) * count );
					iPtr[ count - 1 ] = this->indexPtr[ j ];
				} /* end if */
			} /* end inner for */
			*( setPtrs )[ i ] = Set( iPtr, count, this->dataPtr );
			count = 0;
			free( iPtr );
			iPtr = NULL;
		} /* end outer for */
	} /* end if */
	else {
		cout << "请输入正确的特征！" << endl;
		exit( -1 );
	} /* end else */
} /* end function divideAccordingAttribute */

d64 Set::getEntropy() const
{
	d64 temp;
	d64 entropy = 0.0;
	i32 classes = this->dataPtr->getNumOfClasses();
	i32 *classFrePtr = new i32[  classes + 1 ];
	i32 *amPtr = this->dataPtr->getAimOutput();
	i32 *indPtr = this->getIndexPtr();

	for ( i32 i = 0; i < classes + 1; i++ ) {
		classFrePtr[ i ] = 0;
	} /* end for */

	for ( i32 i = 0; i < this->samplesCount; i++ ) {
		classFrePtr[ amPtr[ indPtr[ i ] ] ]++;
	} /* end for */

	for ( i32 i = 1; i < classes + 1; i++ ) {
		temp = ( d64 )classFrePtr[ i ] / this->samplesCount;
		if ( fabs( 0 - temp ) <= PRECISION ) {
			temp = 1.0;
		} /* end if */
		entropy += temp * log2( temp );
	} /* end for */ 

	delete classFrePtr;
	return entropy;
} /* end function getEntropy */

d64 Set::getConditionalEntropy( i32 attr ) const
{
	d64 cdtEntropy = 0.0;
	i32 count = this->dataPtr->A.getNumOfValuesOfAttribute( attr );

	this->divideAccordingAtrribute( attr, &this->sPtrs[ attr ] );

	for ( i32 i = 0; i < count; i++ ) {
		cdtEntropy += ( ( d64 )this->sPtrs[ attr ][ i ].getSamplesCount() / this->samplesCount ) * this->sPtrs[ attr ][ i ].getEntropy();
	} /* end for */
	return cdtEntropy;
} /* end function getConditonalEntropy */
