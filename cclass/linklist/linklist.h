#ifndef LINKLIST_H
#define LINKLIST_H

#include "c_class.h"

#define magic_linklist 0
#define magic_linklist_iterator 3

CLASS_DECL(linklist_iterator);

/************************Á´±í***************************************************************/
CLASS(linklist)
	NO_PUBLIC_MEMBER(linklist);

	CLASS_CONSTRUCTOR_DECL(linklist);
	CLASS_DISTRUCTOR_DECL(linklist);

	PUBLIC_METHOD(linklist) {
		DISTRUCTOR;
		METHOD(void, clear);
		METHOD(void, push_back, void *data);
		METHOD(void, push_front, void *data);
		METHOD(void *, pop_front);
		METHOD(void *, pop_back);
		METHOD(void *, front);
		METHOD(void *, back);
		METHOD(void, remove, void *data);
		METHOD(uint32_t, get_size);
	};
CLASS_END

METHOD_DECL(void, linklist, clear);
METHOD_DECL(void, linklist, push_back, void *data);
METHOD_DECL(void, linklist, push_front, void *data);
METHOD_DECL(void *, linklist, pop_front);
METHOD_DECL(void *, linklist, pop_back);
METHOD_DECL(void *, linklist, front);
METHOD_DECL(void *, linklist, back);
METHOD_DECL(linklist_iterator *, linklist, remove_iter, linklist_iterator *iter);
METHOD_DECL(void, linklist, remove, void *data);
METHOD_DECL(linklist_iterator *, linklist, insert_behind, linklist_iterator *iter, void *data);
METHOD_DECL(linklist_iterator *, linklist, insert_front, linklist_iterator *iter, void *data);
METHOD_DECL(uint32_t, linklist, get_size);

/************************µü´úÆ÷***************************************************************/
CLASS(linklist_iterator)
	NO_PUBLIC_MEMBER(linklist_iterator);

	CLASS_CONSTRUCTOR_DECL(linklist_iterator);
	CLASS_DISTRUCTOR_DECL(linklist_iterator);

	PUBLIC_METHOD(linklist_iterator) {
		DISTRUCTOR;
		METHOD(bool, getend);
		METHOD(void, next);
		METHOD(void, prev);
		METHOD(void *, get_data);
		METHOD(void, set_list, linklist *list);
	};
CLASS_END

METHOD_DECL(bool, linklist_iterator, getend);
METHOD_DECL(void, linklist_iterator, next);
METHOD_DECL(void, linklist_iterator, prev);
METHOD_DECL(void *, linklist_iterator, get_data);
METHOD_DECL(void, linklist_iterator, set_list, linklist *list);

#define linklist_foreach_begin(type, elem, list) \
{												 \
	linklist_iterator *iter = new(linklist_iterator); \
	invoke(iter, set_list, list); \
	for (; !invoke(iter, getend); invoke(iter, next)) {\
		type *elem = (type*)invoke(iter, get_data);

#define linklist_foreach_end \
	} \
	delete(iter); \
}

#endif // !LINKLIST_H
