#include "linklist.h"
#include "linklist_node.h"

FUNC_TABLE_INIT(linklist) {
	FUNC_TABLE_SET(linklist, distructor),
	FUNC_TABLE_SET(linklist, clear),
	FUNC_TABLE_SET(linklist, push_back),
	FUNC_TABLE_SET(linklist, push_front),
	FUNC_TABLE_SET(linklist, pop_front),
	FUNC_TABLE_SET(linklist, pop_back),
	FUNC_TABLE_SET(linklist, front),
	FUNC_TABLE_SET(linklist, back),
	FUNC_TABLE_SET(linklist, remove),
	FUNC_TABLE_SET(linklist, get_size)
};

PRIVATE_MEMBER(linklist) {
	int32_t magic;
	linklist_node *head;
	linklist_node *tail;
	linklist_node *invalid;
	uint32_t length;
};

CLASS_CONSTRUCTOR_BASE_IMPL(linklist) {
	pv(length) = 0;
	pv(head) = pv(tail) = NULL;
	pv(invalid) = new(linklist_node);
}

CLASS_DISTRUCTOR_BASE_IMPL(linklist) {
	delete(pv(invalid));
	self_invoke(clear);
}

METHOD_IMPL
(void, linklist, clear) {
	linklist_node *temp;
	uint32_t i = 0;

	for (i = 0; i < pv(length); ++i) {
		temp = pv(head);
		pv(head) = pb_mb(pv(head), next);
		delete(temp);
	}
	
	pv(tail) = pv(head) = NULL;
	pv(length) = 0;
}METHOD_END

METHOD_IMPL
(void, linklist, push_back, void *data) {
	linklist_node *node = new(linklist_node);
	pb_mb(node, data) = data;

	if (!pv(length)) {
		pv(head) = pv(tail) = node;
	}
	else {
		pb_mb(pv(tail), next) = node;
		pb_mb(pb_mb(pv(tail), next), prev) = pv(tail);
		pv(tail) = pb_mb(pv(tail), next);
	}
	pv(length)++;
}METHOD_END

METHOD_IMPL
(void, linklist, push_front, void *data) {
	linklist_node *node = new(linklist_node);
	pb_mb(node, data) = data;

	if (!pv(length)) {
		pv(head) = pv(tail) = node;
	}
	else {
		pb_mb(pv(head), prev) = node;
		pb_mb(pb_mb(pv(head), prev), next) = pv(head);
		pv(head) = pb_mb(pv(head), prev);
	}
	pv(length)++;
}METHOD_END

METHOD_IMPL
(void, linklist, remove_node, linklist_node *node) {
	linklist_node *temp;
	if (pv(length) == 0)
		return;

	pv(length)--;

	if (pv(length) == 0) {
		temp = pv(head);
		pv(head) = pv(tail) = NULL;
		delete(temp);
		return;
	}

	if (pv(head) == node) {
		temp = pv(head);
		pv(head) = pb_mb(pv(head), next);
		pb_mb(pv(head), prev) = NULL;
		delete(temp);
		return;
	}

	if (pv(tail) == node) {
		temp = pv(tail);
		pv(tail) = pb_mb(pv(tail), prev);
		pb_mb(pv(tail), next) = NULL;
		delete(temp);
		return;
	}

	pb_mb(pb_mb(node, prev), next) = pb_mb(node, next);
	pb_mb(pb_mb(node, next), prev) = pb_mb(node, prev);
	delete(node);
}METHOD_END

METHOD_IMPL
(void *, linklist, pop_front) {
	void *data;

	if (!pv(length))
		return NULL;

	data = pb_mb(pv(head), data);

	linklist_remove_node(self, pv(head));

	return data;
}METHOD_END

METHOD_IMPL
(void *, linklist, pop_back) {
	void *data;

	if (!pv(length))
		return NULL;

	data = pb_mb(pv(tail), data);
	linklist_remove_node(self, pv(tail));

	return data;
}METHOD_END

METHOD_IMPL
(void *, linklist, front) {
	return pv(head) ? pb_mb(pv(head), data) : NULL;
}METHOD_END

METHOD_IMPL
(void *, linklist, back) {
	return pv(tail) ? pb_mb(pv(tail), data) : NULL;
}METHOD_END

METHOD_IMPL
(void, linklist, remove, void *data) {
	linklist_node *node = pv(head);
	while (node != NULL) {
		if (pb_mb(node, data) == data) {
			linklist_remove_node(self, node);
			return;
		}
		node = pb_mb(node, next);
	}
}METHOD_END

METHOD_IMPL
(uint32_t, linklist, get_size) {
	return pv(length);
}METHOD_END

FUNC_TABLE_INIT(linklist_iterator) {
	FUNC_TABLE_SET(linklist_iterator, distructor),
	FUNC_TABLE_SET(linklist_iterator, getend),
	FUNC_TABLE_SET(linklist_iterator, next),
	FUNC_TABLE_SET(linklist_iterator, prev),
	FUNC_TABLE_SET(linklist_iterator, get_data),
	FUNC_TABLE_SET(linklist_iterator, set_list)
};

PRIVATE_MEMBER(linklist_iterator) {
	linklist *list;
	linklist_node *node;
};

CLASS_CONSTRUCTOR_BASE_IMPL(linklist_iterator) {
	pv(list) = NULL;
	pv(node) = NULL;
}

CLASS_DISTRUCTOR_BASE_IMPL(linklist_iterator) {

}

METHOD_IMPL
(bool, linklist_iterator, getend) {
	return pv(node) == pv_mb(pv(list), invalid);
}METHOD_END

METHOD_IMPL
(void, linklist_iterator, next) {
	if (self_invoke(getend))
		return;

	if (pv(node) == pv_mb(pv(list), tail))
		pv(node) = pv_mb(pv(list), invalid);
	else
		pv(node) = pb_mb(pv(node), next);
}METHOD_END

METHOD_IMPL
(void, linklist_iterator, prev) {
	if (self_invoke(getend))
		return;

	if (pv(node) == pv_mb(pv(list), head))
		pv(node) = pv_mb(pv(list), invalid);
	else
		pv(node) = pb_mb(pv(node), prev);
}METHOD_END

METHOD_IMPL
(void *, linklist_iterator, get_data) {
	return pv(node) != pv_mb(pv(list), invalid) ?
		pb_mb(pv(node), data) : NULL;
}METHOD_END

METHOD_IMPL
(void, linklist_iterator, set_list, linklist *list) {
	pv(list) = list;
	pv(node) = pv_mb(list, length) ? pv_mb(list, head) : pv_mb(list, invalid);
}METHOD_END