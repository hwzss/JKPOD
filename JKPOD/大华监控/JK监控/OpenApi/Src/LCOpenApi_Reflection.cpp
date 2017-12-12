#include "LCOpenApi_Reflection.h"
#include "LCOpenApi_ReflectionObject.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

namespace LCOpenApi{

metainfo_t *metainfo_create(int obj_size)
{
	metainfo_t *mi = (metainfo_t *)malloc(sizeof(metainfo_t));
	memset(mi, 0, sizeof(metainfo_t));
	mi->obj_size = obj_size;
	return mi;
}

void metainfo_destroy(metainfo_t *mi)
{
	LIST_CLEAR(mi->fs);
	free(mi);
}

void metainfo_add_member(metainfo_t *mi, int pos, int type, const char *name, int islist)
{
	field_t f;
	f.valConst = 0;
	f.pos = pos;
	f.type = type;
	f.islist = islist;
	f.name = name;
	f.metainfo = NULL;
	LIST_ADD_OBJ(mi->fs, f);
}
void metainfo_add_member_const(metainfo_t *mi, int pos, int type, const char *name, int islist,char *valConst)
{
	field_t f;
	f.pos = pos;
	f.type = type;
	f.islist = islist;
	f.name = name;
	f.metainfo = NULL;

	f.valConst = valConst;
	LIST_ADD_OBJ(mi->fs, f);
}

metainfo_t *metainfo_add_child(metainfo_t *mi, int pos, int obj_size, const char *name, int islist)
{
	metainfo_t *child = metainfo_create(obj_size);
	field_t f;
	f.pos = pos;
	f.type = FIELD_TYPE_STRUCT;
	f.islist = islist;
	f.name = name;
	f.metainfo = child;
	LIST_ADD_OBJ(mi->fs, f);
	return child;
}

metainfo_t *metainfo_get_child(metainfo_t *mi, const char *name)
{
	int i;
	for (i = 0; i < mi->fs.size; i++)
	{
		field_t *f = &mi->fs.array[i];
		if (0 == strcmp(f->name, name))
		{
			return (metainfo_t *)f->metainfo;
		}
	}
	return NULL;
}

void *object_new(metainfo_t *mi)
{
	void *ptr = calloc(mi->obj_size, 1);
	return ptr;
}

void object_clear(void *obj, metainfo_t *mi)
{
	int i;

	for (i = 0; i < mi->fs.size; i++)
	{
		field_t *f = &mi->fs.array[i];
		void *ptr = ((char *)obj + f->pos);

		if (f->islist)
		{
			free_buffer_t *fb = (free_buffer_t *)ptr;
			int k;

			if (f->type == FIELD_TYPE_CSTR)
			{
				for (k = 0; k < fb->count; k++)
				{
					CSTR *p = (CSTR *)(fb->ptr + k * sizeof(CSTR));
					CS_CLEAR(*p);
				}
			} 
			else if (f->type == FIELD_TYPE_STRUCT)
			{
				for (k = 0; k < fb->count; k++)
				{
					metainfo_t *mi = (metainfo_t *)f->metainfo;
					void *obj = fb->ptr + k * mi->obj_size;
					object_clear(obj, mi);
				}
			}

			LIST_CLEAR(*fb);
		}
		else
		{
			if (f->type == FIELD_TYPE_INT)
			{
				int *p = (int *)ptr;
				*p = 0;
			}
			else if (f->type == FIELD_TYPE_BOOL)
			{
				BOOL *p = (BOOL *)ptr;
				*p = 0;
			}
			else if (f->type == FIELD_TYPE_CSTR)
			{
				CSTR *p = (CSTR *)ptr;
				CS_CLEAR(*p);
			} 
			else if (f->type == FIELD_TYPE_DOUBLE)
			{
				double *p = (double *)ptr;
				*p = 0;
			}
			else if (f->type == FIELD_TYPE_STRUCT)
			{
				metainfo_t *mi = (metainfo_t *)f->metainfo;
				void *obj = ptr;
				object_clear(obj, mi);
			}
		}
	}
}

int object_copy(void *obj, void *src, metainfo_t *mi)
{
	cJSON *json;

	if (!obj || !src || !mi)
	{
		return -1;
	}

	json = object_to_jsonobject(src, mi);
	if (!json)
	{
		return -1;
	}

	object_from_jsonobject(obj, mi, json);

	cJSON_Delete(json);

	return 0;
}

/************************************************************************/
/* object                                                               */
/************************************************************************/
const_string_t object_to_json(void *obj, metainfo_t *mi)
{
	const_string_t cs = {NULL};
	cJSON *json;

	if (!obj || !mi)
	{
		return cs;
	}

	json = object_to_jsonobject(obj, mi);

	cs.cstr = cJSON_Print(json);

	cJSON_Delete(json);

	return cs;
}

int object_from_json(void *obj, metainfo_t *mi, const char *str)
{
	cJSON *json;
	if (!obj || !mi || !str)
	{
		return -1;
	}

	json = cJSON_Parse(str);
	if (json == NULL)
	{
		return -1;
	}

	object_from_jsonobject(obj, mi, json);

	cJSON_Delete(json);

	return 0;
}


}