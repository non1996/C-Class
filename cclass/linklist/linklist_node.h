#ifndef LINKLIST_NODE_H
#define LINKLIST_NODE_H

#include "c_class.h"

#define magic_linklist_node 1

CLASS(linklist_node)
NO_PRIVATE_MEMBER(linklist_node);

PUBLIC_MEMBER(linklist_node) {
	void *data;
	linklist_node *next;
	linklist_node *prev;
};

CLASS_CONSTRUCTOR_DECL(linklist_node);
CLASS_DISTRUCTOR_DECL(linklist_node);

PUBLIC_METHOD(linklist_node) {
	DISTRUCTOR;
};
CLASS_END

#endif // !LINKLIST_NODE_H

