#ifndef LINKLIST_H
#define LINKLIST_H

#include "c_class.h"

#define magic_linklist 0
#define magic_linklist_node 1
#define magic_linklist_iterator 2

class_decl(linklist_iterator);
class_decl(linklist_node);

/************************Á´±í***************************************************************/
class(linklist)
	public_member
		linklist_node *head;
		linklist_node *tail;
		linklist_node *invalid;
		uint32_t length;
	public_member_end

	class_constructor_decl(linklist);
	class_distructor_decl(linklist);

	public_method(linklist) 
		method(void, clear);
		method(void, push_back, void *data);
		method(void, push_front, void *data);
		method(void *, pop_front);
		method(void *, pop_back);
		method(void *, front);
		method(void *, back);
		method(void, remove, void *data);
		method(uint32_t, get_size);
	public_member_end
class_end

method_decl(void, linklist, clear);
method_decl(void, linklist, push_back, void *data);
method_decl(void, linklist, push_front, void *data);
method_decl(void *, linklist, pop_front);
method_decl(void *, linklist, pop_back);
method_decl(void *, linklist, front);
method_decl(void *, linklist, back);
method_decl(linklist_iterator *, linklist, remove_iter, linklist_iterator *iter);
method_decl(void, linklist, remove, void *data);
method_decl(linklist_iterator *, linklist, insert_behind, linklist_iterator *iter, void *data);
method_decl(linklist_iterator *, linklist, insert_front, linklist_iterator *iter, void *data);
method_decl(uint32_t, linklist, get_size);

/************************µü´úÆ÷***************************************************************/
class(linklist_iterator)
	public_member
		linklist *list;
		linklist_node *node;
	public_member_end

	class_constructor_decl(linklist_iterator);
	class_constructor_arg_decl(linklist_iterator, list, linklist *list);
	class_distructor_decl(linklist_iterator);

	public_method(linklist_iterator)
		method(bool, getend);
		method(void, next);
		method(void, prev);
		method(void *, get_data);
		method(void, set_list, linklist *list);
	public_method_end
class_end

method_decl(bool, linklist_iterator, getend);
method_decl(void, linklist_iterator, next);
method_decl(void, linklist_iterator, prev);
method_decl(void *, linklist_iterator, get_data);
method_decl(void, linklist_iterator, set_list, linklist *list);

ptr_cast_impl(linklist, 
	(magic(ptr) == magic_linklist)
)

ptr_cast_impl(linklist_iterator,
	(magic(ptr) == magic_linklist_iterator)
)

ptr_cast_impl(linklist_node,
	(magic(ptr) == magic_linklist_node)
)

#define linklist_foreach_begin(type, elem, list) \
{												 \
	linklist_iterator *iter = new_args(linklist_iterator, list, list); \
	for (; !invoke(iter, getend); invoke(iter, next)) {\
		type *elem = (type*)invoke(iter, get_data);

#define linklist_foreach_end \
	} \
	delete(iter); \
}

#endif // !LINKLIST_H
