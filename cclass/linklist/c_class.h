#ifndef C_CLASS_H
#define C_CLASS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define ptr_cast(classname, ptr) (classname*)ptr

//#define new_arg(class_name, func_name, ...) class_name ## _new_ ## func_name(__VA_ARGS__)
#define new(classname) classname ## _constructor((classname*)malloc(sizeof(classname)), NULL)
#define delete(ptr) if (ptr) { \
	invoke(ptr, distructor); \
	free(ptr); \
	ptr = NULL; \
}

#define invoke(ptr, func, ...) (ptr)->ftable->func((ptr), __VA_ARGS__)
#define self_invoke(func, ...) self->ftable->func(self, __VA_ARGS__)

#define pb_mb(ptr, m) (ptr)->pblc->m
#define pv_mb(ptr, m) (ptr)->prvt->m
#define pb(m) pb_mb(self, m)
#define pv(m) self->prvt->m

#define SELF void *s
#define BLOCK_END };
#define METHOD_END }

#define CLASS_DECL(classname) typedef struct classname ## _t classname

#define CLASS_BASE(classname) \
typedef struct classname ## _private_t classname ## _private; \
typedef struct classname ## _public_t classname ## _public; \
typedef struct classname ## _functable_t classname ## _functable; \
typedef struct classname ## _t classname; \
struct classname ## _t 

#define CLASS(classname) \
CLASS_BASE(classname) {\
	int32_t magic; \
	classname ## _functable *ftable; \
	classname ## _private *prvt; \
	classname ## _public *pblc; \
};

#define CLASS_EXTENDS(classname, parent) \
CLASS_BASE(classname) \
	parent _base; \
	classname ## _functable *ftable; \
	classname ## _private *prvt; \
	classname ## _public *pblc; \
};

#define CLASS_END

/************************类成员变量***************************************************************/
#define PUBLIC_MEMBER(classname) \
struct classname ## _public_t

#define NO_PUBLIC_MEMBER(classname) \
struct classname ## _public_t { \
	char empty; \
}

#define PRIVATE_MEMBER(classname) \
struct classname ## _private_t 

#define NO_PRIVATE_MEMBER(classname) \
struct classname ## _private_t { \
	char empty; \
}

#define MEMBER(type, name) type name

/************************类成员函数***************************************************************/


#define PUBLIC_METHOD(classname) \
struct classname ## _functable_t

#define DISTRUCTOR void(*distructor)(void*self)	

#define METHOD(type, func, ...) type(*func)(SELF, __VA_ARGS__)

#define METHOD_DECL(type, classname, func, ...) type classname ## _ ## func(SELF, __VA_ARGS__)

#define METHOD_IMPL(type, classname, func, ...) \
type classname ## _ ## func(SELF, __VA_ARGS__) { \
	classname *self = ptr_cast(classname, s);

/************************类构造、析构函数*********************************************************/
#define CLASS_CONSTRUCTOR_DECL(classname) \
classname *classname ## _constructor \
	(classname *self, void *vftable)

#define CLASS_CONSTRUCTOR_BASE_IMPL(classname) \
inline void classname ## _constructor_fn(classname *self); \
classname *classname ## _constructor \
	(classname *self, void *vftable) { \
	self->magic = magic_ ## classname; \
	self->ftable = vftable ? (classname ## _functable*)vftable : &classname ## _f; \
	self->pblc = (classname ## _public*)malloc(sizeof(classname ## _public)); \
	self->prvt = (classname ## _private*)malloc(sizeof(classname ## _private)); \
	classname ## _constructor_fn(self); \
	return self; \
} \
inline void classname ## _constructor_fn(classname *self) 

#define CLASS_CONSTRUCTOR_EXTENDS_IMPL(classname, parent) \
inline void classname ## _constructor_fn(classname *self); \
classname *classname ## _constructor \
	(classname *self, void *vftable) { \
	parent ## _constructor(&(self->_base), &classname ## _f); \
	self->magic = magic_ ## classname; \
	self->ftable = &classname ## _f; \
	self->pblc = (classname ## _public*)malloc(sizeof(classname ## _public)); \
	self->prvt = (classname ## _private*)malloc(sizeof(classname ## _private)); \
	classname ## _constructor_fn(self); \
	return self; \
} \
inline void classname ## _constructor_fn(classname *self) 

#define CLASS_DISTRUCTOR_DECL(classname) void classname ## _distructor(SELF)

#define CLASS_DISTRUCTOR_BASE_IMPL(classname) \
inline void classname ## _distructor_fn(classname *self); \
void classname ## _distructor(SELF) { \
	classname *self = ptr_cast(classname, s); \
	classname ## _distructor_fn(self); \
	free(self->prvt); \
	free(self->pblc); \
} \
inline void classname ## _distructor_fn(classname *self) 

#define CLASS_DISTRUCTOR_EXTENDS_IMPL(classname, parent) \
inline void classname ## _distructor_fn(classname *self); \
void classname ## _distructor(classname *self) { \
	classname ## _distructor_fn(self); \
	parent ## _distructor(&(self->_base)); \
	free(self->prvt); \
	free(self->pblc); \
} \
inline void classname ## _distructor_fn(classname *self) 

/************************类虚函数表初始化*********************************************************/
#define FUNC_TABLE_INIT(classname) \
static classname ## _functable classname ## _f = 

#define FUNC_TABLE_SET(classname, func) classname ## _ ## func

#endif // !C_CLASS_H
