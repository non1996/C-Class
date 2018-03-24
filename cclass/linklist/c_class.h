#ifndef C_CLASS_H
#define C_CLASS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define magic(ptr) *(int32_t*)(ptr)
#define ptr_cast(classname, ptr) ptr_cast_ ## classname((ptr));

//	alloc
#define new(classname) classname ## _constructor((classname*)malloc(sizeof(classname)), NULL)
#define new_args(classname, alias, ...) classname ## _constructor_ ## alias((classname*)malloc(sizeof(classname)), NULL, __VA_ARGS__)
#define delete(ptr) if (ptr) { \
	invoke(ptr, distructor); \
	free(ptr); \
	ptr = NULL; \
}

//	method invoke
#define invoke(ptr, func, ...) (ptr)->ftable->func((ptr), __VA_ARGS__)
#define self_invoke(func, ...) self->ftable->func(self, __VA_ARGS__)

//	parent object pointer
#define super &(self->_base)

//	helper
#define SELF void *s
#define BLOCK_END };

//	class declaration
#define class_decl(classname) typedef struct classname ## _t classname

//	class implementation
#define CLASS_BASE(classname) \
typedef struct classname ## _functable_t classname ## _functable; \
typedef struct classname ## _t classname; \
struct classname ## _t 

#define class(classname) \
CLASS_BASE(classname) {\
	int32_t magic; \
	classname ## _functable *ftable; 

#define class_extends(classname, parent) \
CLASS_BASE(classname) \
	parent _base; \
	classname ## _functable *ftable; 

#define class_end

/************************class member variable***************************************************************/
#define public_member

#define public_member_end BLOCK_END

/************************class member method*****************************************************************/
#define public_method(classname) \
struct classname ## _functable_t { \
	void(*distructor)(void*self);

#define public_method_end BLOCK_END

#define no_public_method(classname) \
struct classname ## _functable_t { \
	void(*distructor)(void*self); \
};

#define method(type, func, ...) type(*func)(SELF, __VA_ARGS__)

#define method_decl(type, classname, func, ...) type classname ## _ ## func(SELF, __VA_ARGS__)
#define method_impl(type, classname, func, ...) \
type classname ## _ ## func(SELF, __VA_ARGS__) { \
	classname *self = ptr_cast(classname, s);
#define method_end }

/************************constructor and distructor*******************************************************/
#define class_constructor_decl(classname) \
classname *classname ## _constructor \
	(classname *self, void *vftable)

#define class_constructor_arg_decl(classname, alias, ...) \
classname *classname ## _constructor_ ## alias \
	(classname *self, void *vftable, __VA_ARGS__)

#define class_constructor_arg_impl(classname, alias, ...) \
classname *classname ## _constructor_ ## alias \
	(classname *self, void *vftable, __VA_ARGS__) { \
	self = classname ## _constructor(self, vftable);

#define class_constructor_end return self; }

#define class_constructor_base_impl(classname) \
inline void classname ## _constructor_fn(classname *self); \
classname *classname ## _constructor \
	(classname *self, void *vftable) { \
	self->magic = magic_ ## classname; \
	self->ftable = vftable ? (classname ## _functable*)vftable : &classname ## _f; \
	classname ## _constructor_fn(self); \
	class_constructor_end \
inline void classname ## _constructor_fn(classname *self) 

#define class_constructor_extends_impl(classname, parent) \
inline void classname ## _constructor_fn(classname *self); \
classname *classname ## _constructor \
	(classname *self, void *vftable) { \
	parent ## _constructor(&(self->_base), &classname ## _f); \
	self->magic = magic_ ## classname; \
	self->ftable = &classname ## _f; \
	classname ## _constructor_fn(self); \
	class_constructor_end \
inline void classname ## _constructor_fn(classname *self) 

#define class_distructor_decl(classname) void classname ## _distructor(SELF)

#define class_distructor_base_impl(classname) \
inline void classname ## _distructor_fn(classname *self); \
void classname ## _distructor(SELF) { \
	classname *self = ptr_cast(classname, s); \
	classname ## _distructor_fn(self); \
} \
inline void classname ## _distructor_fn(classname *self) 

#define class_distructor_extends_impl(classname, parent) \
inline void classname ## _distructor_fn(classname *self); \
void classname ## _distructor(classname *self) { \
	classname ## _distructor_fn(self); \
	parent ## _distructor(&(self->_base)); \
} \
inline void classname ## _distructor_fn(classname *self) 

/************************virtual table initialize*********************************************************/
#define functable_init(classname) \
static classname ## _functable classname ## _f = 

#define set_func(classname, func) classname ## _ ## func

/************************pointer cast function template***************************************************/
#define ptr_cast_impl(classname, condition) \
inline classname *ptr_cast_ ## classname(void *ptr) { \
	assert(ptr && condition); \
	return (classname*)ptr; \
}	

#endif // !C_CLASS_H
