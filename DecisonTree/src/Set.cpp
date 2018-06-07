#include "../inc/Set.h"

Set::Set( i32 *indexPtr, i32 samplesCount, Data *dataPtr )
{
	this->setDataPtr( dataPtr );
	this->setSamplesCount( samplesCount );
	this->setIndexPtr( indexPtr );
} /* end construtor */

Set::Set( Set &setRef )
{
	this->setDataPtr( setRef.getDataPtr() );
	this->setSamplesCount( setRef.getSamplesCount() );
	this->setIndexPtr( setRef.getIndexPtr() );
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
	this->indexPtr = new i32[ count ];

	for ( i32 i = 0; i < count; i++ ) {
		this->indexPtr[ i ] = indexPtr[ i ];
	} /* end for */
} /* end function setIndexPtr */

i32 Set::getSamplesCount() const
{
	return this->samplesCount;
} /* end function getIndexCount */

i32 *Set::getIndexPtr() const
{
	return this->indexPtr;
} /* end function getIndexPtr */

void Set::divideAccordingAtrribute( i32 attr, Set **setPtrs ) const
{
	i32 numOfValues = this->dataPtr->A.getNumOfValuesOfAttribute( attr );
	i32 *iPtr = NULL;

	for( i32 i = 0; i < numOfValues; i++ ) {
		
	} /* end for */

} /* end function divideAccordingAttribute */

d64 Set::getEntropy() const
{
	d64 entropy = 0.0;
	i32 sCount = this->getSamplesCount();
	i32 classes = this->dataPtr->getNumOfClasses();
	i32 *classFrePtr = new i32[  classes + 1 ];
	i32 *amPtr = this->dataPtr->getAimOutput();
	i32 *indPtr = this->getIndexPtr();

	for ( i32 i = 0; i < classes + 1; i++ ) {
		classFrePtr[ i ] = 0;
	} /* end for */

	for ( i32 i = 0; i < sCount; i++ ) {
		classFrePtr[ amPtr[ indPtr[ i ] ] ]++;
	} /* end for */

	for ( i32 i = 1; i < classes + 1; i++ ) {
		entropy += ( d64 )classFrePtr[ i ] / sCount;
	} /* end for */ 

	delete classFrePtr;

	return entropy;
} /* end function getEntropy */

d64 Set::getConditionalEntropy( i32 attr ) const
{

} /* end function getConditonalEntropy */
