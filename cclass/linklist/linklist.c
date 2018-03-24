#include "linklist.h"
#include <stdio.h>


class(linklist_node)
	public_member
		void *data;
		linklist_node *next;
		linklist_node *prev;
	public_member_end

	class_constructor_decl(linklist_node);
	class_distructor_decl(linklist_node);

	no_public_method(linklist_node)
class_end

functable_init(linklist_node) {
	set_func(linklist_node, distructor)
};

functable_init(linklist) {
	set_func(linklist, distructor),
	set_func(linklist, clear),
	set_func(linklist, push_back),
	set_func(linklist, push_front),
	set_func(linklist, pop_front),
	set_func(linklist, pop_back),
	set_func(linklist, front),
	set_func(linklist, back),
	set_func(linklist, remove),
	set_func(linklist, get_size)
};

functable_init(linklist_iterator) {
	set_func(linklist_iterator, distructor),
	set_func(linklist_iterator, getend),
	set_func(linklist_iterator, next),
	set_func(linklist_iterator, prev),
	set_func(linklist_iterator, get_data),
	set_func(linklist_iterator, set_list)
};

class_constructor_base_impl(linklist_node) {
	self->data = NULL;
	self->next = NULL;
	self->prev = NULL;
}

class_distructor_base_impl(linklist_node) {

}

class_constructor_base_impl(linklist) {
	self->length = 0;
	self->head = self->tail = NULL;
	self->invalid = new(linklist_node);
}

class_distructor_base_impl(linklist) {
	delete(self->invalid);
	self_invoke(clear);
}

method_impl
(void, linklist, clear) {
	linklist_node *temp;
	uint32_t i = 0;

	for (i = 0; i < self->length; ++i) {
		temp = self->head;
		self->head = self->head->next;
		delete(temp);
	}
	
	self->tail = self->head = NULL;
	self->length = 0;
}method_end

method_impl
(void, linklist, push_back, void *data) {
	linklist_node *node = new(linklist_node);
	node->data = data;

	if (!self->length) {
		self->head = self->tail = node;
	}
	else {
		self->tail->next = node;
		node->prev = self->tail;
		self->tail = node;
	}
	self->length++;
}method_end

method_impl
(void, linklist, push_front, void *data) {
	linklist_node *node = new(linklist_node);
	node->data = data;

	if (!self->length) {
		self->head = self->tail = node;
	}
	else {
		self->head->prev = node;
		node->next = self->head;
		self->head = node;
	}
	self->length++;
}method_end

method_impl
(void, linklist, remove_node, linklist_node *node) {
	linklist_node *temp;
	if (self->length == 0)
		return;

	self->length--;

	if (self->length == 0) {
		temp = self->head;
		self->head = self->tail = NULL;
		delete(temp);
		return;
	}

	if (self->head == node) {
		temp = self->head;
		self->head = self->head->next;
		self->head->prev = NULL;
		delete(temp);
		return;
	}

	if (self->tail == node) {
		temp = self->tail;
		self->tail = self->tail->prev;
		self->tail->next = NULL;
		delete(temp);
		return;
	}

	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete(node);
}method_end

method_impl
(void *, linklist, pop_front) {
	void *data;

	if (!self->length)
		return NULL;

	data = self->head->data;

	linklist_remove_node(self, self->head);

	return data;
}method_end

method_impl
(void *, linklist, pop_back) {
	void *data;

	if (!self->length)
		return NULL;

	data = self->tail->data;
	linklist_remove_node(self, self->tail);

	return data;
}method_end

method_impl
(void *, linklist, front) {
	return self->head ? self->head->data : NULL;
}method_end

method_impl
(void *, linklist, back) {
	return self->tail ? self->tail->data : NULL;
}method_end

method_impl
(void, linklist, remove, void *data) {
	linklist_node *node = self->head;
	while (node != NULL) {
		if (node->data == data) {
			linklist_remove_node(self, node);
			return;
		}
		node = node->next;
	}
}method_end

method_impl
(uint32_t, linklist, get_size) {
	return self->length;
}method_end

class_constructor_base_impl(linklist_iterator) {
	self->list = NULL;
	self->node = NULL;
}

class_constructor_arg_impl(linklist_iterator, list,
	linklist *list) {
	self_invoke(set_list, list);
}class_constructor_end

class_distructor_base_impl(linklist_iterator) {

}

method_impl
(bool, linklist_iterator, getend) {
	return self->node == self->list->invalid;
}method_end

method_impl
(void, linklist_iterator, next) {
	if (self_invoke(getend))
		return;

	if (self->node == self->list->tail)
		self->node = self->list->invalid;
	else
		self->node = self->node->next;
}method_end

method_impl
(void, linklist_iterator, prev) {
	if (self_invoke(getend))
		return;

	if (self->node == self->list->head)
		self->node = self->list->invalid;
	else
		self->node = self->node->prev;
}method_end

method_impl
(void *, linklist_iterator, get_data) {
	return self->node != self->list->invalid ?
		   self->node->data : NULL;
}method_end

method_impl
(void, linklist_iterator, set_list, linklist *list) {
	self->list = list;
	self->node = list->length ? list->head : list->invalid;
}method_end