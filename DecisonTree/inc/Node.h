#ifndef __NODE_H
#define __NODE_H

#include "Data.h"

class Node {
private :
	i32 label;
	i32 subNodeCount;
	d64 *attrPtr;
	Node *subNodePtr;

public :
	Node();
};

#endif  /* __NODE_H */
