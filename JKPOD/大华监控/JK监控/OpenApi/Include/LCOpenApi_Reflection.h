#ifndef _LCOPENAPI_REFLECTION_H_
#define _LCOPENAPI_REFLECTION_H_

#include <stddef.h>
#include "LCOpenApi_ConstString.h"
#include "LCOpenApi_FreeBuffer.h"
#include "LCOpenApi_ClientSdk.h"

/************************************************************************/
/* metainfo                                                             */
/************************************************************************/
namespace LCOpenApi{
enum
{
	FIELD_TYPE_INT = 0,
	FIELD_TYPE_BOOL,
	FIELD_TYPE_CSTR,
	FIELD_TYPE_DOUBLE,
	FIELD_TYPE_STRUCT = 100,
};

typedef struct
{
	int pos;
	int type;
	int islist;
	const char *name;
	void *metainfo;

	char *valConst;
} field_t;

typedef struct  
{
	int obj_size;
	DECLARE_LIST(field_t) fs;
} metainfo_t;

metainfo_t *metainfo_create(int obj_size);
void metainfo_destroy(metainfo_t *mi);
void metainfo_add_member(metainfo_t *mi, int pos, int type, const char *name, int islist);
void metainfo_add_member_const(metainfo_t *mi, int pos, int type, const char *name, int islist,char *valConst);

metainfo_t *metainfo_add_child(metainfo_t *mi, int pos, int obj_size, const char *name, int islist);
metainfo_t *metainfo_get_child(metainfo_t *mi, const char *name);

#define METAINFO(s)							_metainfo_##s

#define METAINFO_CREATE(s,b)					METAINFO(s) = metainfo_create((int)sizeof(struct b::s))
#define METAINFO_DESTROY(s)					metainfo_destroy(METAINFO(s))

#define METAINFO_ADD_MEMBER(s,b, t, n)		metainfo_add_member(METAINFO(s), offsetof(struct b::s, n), t, #n, 0)
#define METAINFO_ADD_MEMBER_CONST(s,b,t,n,v)  metainfo_add_member_const(METAINFO(s), offsetof(struct b::s, n), t, #n, 0,v)

#define METAINFO_ADD_MEMBER_LIST(s,b, t, n)	metainfo_add_member(METAINFO(s), offsetof(struct b::s, n), t, #n, 1)
#define METAINFO_ADD_CHILD(s,b, t, n)			metainfo_add_child(METAINFO(s), offsetof(struct b::s, n), (int)sizeof(struct t), #n, 0)
#define METAINFO_ADD_CHILD_LIST(s,b, t, n)	metainfo_add_child(METAINFO(s), offsetof(struct b::s, n), (int)sizeof(struct t), #n, 1)

#define METAINFO_CHILD_BEGIN(s,b, t, n)		{ metainfo_t *METAINFO(t) = METAINFO_ADD_CHILD(s,b, t, n);
#define METAINFO_CHILD_LIST_BEGIN(s,b, t, n)	{ metainfo_t *METAINFO(t) = METAINFO_ADD_CHILD_LIST(s,b, t, n);
#define METAINFO_CHILD_END()				}

#define METAINFO_GET_CHILD(s, name)			metainfo_get_child(METAINFO(s), #name)

/************************************************************************/
/* reflection                                                           */
/************************************************************************/
void *object_new(metainfo_t *mi);
#define OBJECT_NEW(s)					(struct s*)object_new(METAINFO(s))

void object_clear(void *obj, metainfo_t *mi);
#define OBJECT_CLEAR(obj, s)			object_clear(&obj, METAINFO(s))

int object_copy(void *obj, void *src, metainfo_t *mi);
#define OBJECT_COPY(obj, src, s)		object_copy(&obj, &src, METAINFO(s))

const_string_t object_to_json(void *obj, metainfo_t *mi);
#define OBJECT_TO_JSON(obj, s)			object_to_json(&obj, METAINFO(s))

int object_from_json(void *obj, metainfo_t *mi, const char *str);
#define OBJECT_FROM_JSON(obj, s, str)	object_from_json(&obj, METAINFO(s), str)

}
#endif
