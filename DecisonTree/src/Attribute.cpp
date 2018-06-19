#include "../inc/Attribute.h"
#include <malloc.h>
#include <cmath>

bool _isInList( d64 element, d64 *vPtr, i32 length )
{
	for ( i32 i = 0; i < length; i++ ) {
		if ( fabs( element - vPtr[ i ] ) <= PRECISION ) {
			return true;
		} /* end if */
	} /* end for */
	return false;
} /* end isInList */

Attribute::Attribute()
{
	this->current = -1;
} /* end constructors */

void Attribute::setRows( i32 rows )
{
	this->rows = ( rows >= 0 ) ? rows : 0;
} /* end funciton setRows */

void Attribute::setSurplus( i32 surplus )
{
	this->surplus = ( surplus >= 0 ) ? surplus : 0;
} /* end function setSurplus */

i32 Attribute::getSurplus() const
{
	return this->surplus;
} /* end function getSurplus */

i32 Attribute::getAttribute()
{
	i32 temp = this->rows - 1;

	if ( this->current == temp ) this->current = -1;

	while( this->current < temp ) {
		if ( !this->isUsedPtr[ ++this->current ] ) return this->current;
	} /* end while */
	return -1;
} /* end function getCurrent */

i32 Attribute::getNumOfValuesOfAttribute( i32 attr ) const
{
	return this->countPtr[ attr ];
} /* end function getNumOfValuesOfAttribute */

d64 *Attribute::getValuesOfAttribute( i32 attr ) const
{
	if ( attr >= 0 ) return this->attPtrs[ attr ];
	else return NULL;
} /* end function getValuesOfAttribute */

void Attribute::setUsed( i32 index ) {
	this->isUsedPtr[ index ] = true;
	this->setSurplus( this->getSurplus() - 1 );
} /* end function setUsed */

bool Attribute::attributeIsContinuous( i32 index )
{
	if ( index > 0 && index < this->rows ) {
		return this->isContinuous[ index ];
	} /* end if */
	else {
		cout << "Ë÷Òý³¬³ö·¶Î§" << endl;
		exit( -1 );
	} /* end else */
} /* end function attributeIsContinuous */

void Attribute::setContinuous( i32 index )
{
	if ( index > 0 && index < this->rows ) {
		this->isContinuous[ index ] = true;
		d64 temp;
		for ( i32 i = 1; i < this->countPtr[ index ]; i ++ ) {
			for ( i32 j = 0; j < this->countPtr[ index ] - 1; j++ ) {
				if ( this->attPtrs[ index ][ j ] > this->attPtrs[ index ][ j + 1 ] ) {
					temp = this->attPtrs[ index ][ j ];
					this->attPtrs[ index ][ j ] = this->attPtrs[ index ][ j + 1 ];
					this->attPtrs[ index ][ j + 1 ] = temp;
				} /* end if */
			} /* end inner for */
		} /* end outter for */
	} /* end if */
	else {
		cout << "Ë÷Òý³¬³ö·¶Î§" << endl;
		exit( -1 );
	} /* end else */
} /* end function setContinuous */

void Attribute::generate( const Data &dataRef )
{
	i32 columns = dataRef.getMatrixColumn();
	d64 **dPtrs = dataRef.getSamples();

	this->isUsedPtr = new bool[ this->rows ];
	this->countPtr = new i32[ this->rows ];
	this->isContinuous = new bool[ this->rows ];
	this->attPtrs = ( d64 ** )malloc( sizeof( d64 * ) * this->rows );

	for ( i32 r = 0; r < this->rows; r++ ) {
		this->isUsedPtr[ r ] = false;
		this->countPtr[ r ] = 0;
		this->isContinuous[ r ] = false;
		this->attPtrs[ r ] = NULL;
	} /* end for */

	for ( i32 r = 0; r < this->rows; r++ ) {
		for( i32 c = 0; c < columns; c++ ) {
			if ( !_isInList( dPtrs[ r ][ c ], attPtrs[ r ], this->countPtr[ r ] ) ) {
				this->countPtr[ r ]++;
				this->attPtrs[ r ] = ( d64 * )realloc( this->attPtrs[ r ], sizeof( d64 ) * this->countPtr[ r ] );
				this->attPtrs[ r ][ this->countPtr[ r ] - 1 ] = dPtrs[ r ][ c ];
			} /* end if */
		} /* end inner for */
	} /* end outer for */
} /* end function generate */



