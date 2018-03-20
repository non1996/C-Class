#include "linklist_node.h"

FUNC_TABLE_INIT(linklist_node) {
	FUNC_TABLE_SET(linklist_node, distructor)
};

CLASS_CONSTRUCTOR_BASE_IMPL(linklist_node) {
	pb(data) = NULL;
	pb(next) = NULL;
	pb(prev) = NULL;
}

CLASS_DISTRUCTOR_BASE_IMPL(linklist_node) {

}