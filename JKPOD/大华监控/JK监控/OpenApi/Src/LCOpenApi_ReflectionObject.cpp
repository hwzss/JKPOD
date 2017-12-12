
#include "LCOpenApi_ReflectionObject.h"
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/* json                                                                 */
/************************************************************************/
namespace LCOpenApi{
cJSON *object_to_jsonobject(void *obj, metainfo_t *mi)
{
	cJSON *root = cJSON_CreateObject();	
	int i;

	for (i = 0; i < mi->fs.size; i++)
	{
		field_t *f = &mi->fs.array[i];
		void *ptr = ((char *)obj + f->pos);

		if (f->islist)
		{
			free_buffer_t *fb = (free_buffer_t *)ptr;
			cJSON *array = NULL;

			if (f->type == FIELD_TYPE_INT)
			{
				array = cJSON_CreateIntArray((int *)fb->ptr, fb->count);
			}
			else if (f->type == FIELD_TYPE_CSTR)
			{
				array = cJSON_CreateStringArray((const char **)fb->ptr, fb->count);
			} 
			else if (f->type == FIELD_TYPE_DOUBLE)
			{
				array = cJSON_CreateDoubleArray((double *)fb->ptr, fb->count);
			} 
			else if (f->type == FIELD_TYPE_STRUCT)
			{
				int k;
				array = cJSON_CreateArray();
				for (k = 0; k < fb->count; k++)
				{
					metainfo_t *mi = (metainfo_t *)f->metainfo;
					void *obj = fb->ptr + k * mi->obj_size;
					cJSON *item = object_to_jsonobject(obj, mi);
					cJSON_AddItemToArray(array, item);
				}
			}

			if (array)
			{
				cJSON_AddItemToObject(root, f->name, array);
			}
		}
		else
		{
			if (f->type == FIELD_TYPE_INT)
			{
				int *p = (int *)ptr;
				cJSON_AddNumberToObject(root, f->name, *p);
			}
			else if (f->type == FIELD_TYPE_DOUBLE)
			{
				double *p = (double *)ptr;
				cJSON_AddNumberToObject(root, f->name, *p);
			}
			else if (f->type == FIELD_TYPE_BOOL)
			{
				BOOL *p = (BOOL *)ptr;
				if (*p)
				{
					cJSON_AddTrueToObject(root, f->name);
				}
				else
				{
					cJSON_AddFalseToObject(root, f->name);
				}
			}
			else if (f->type == FIELD_TYPE_CSTR)
			{
				CSTR *p = (CSTR *)ptr;
				if (p->cstr)
				{
					cJSON_AddStringToObject(root, f->name, p->cstr);
				}
				else if (f->valConst)
				{
					cJSON_AddStringToObject(root, f->name, f->valConst);
				}
				else
				{
					cJSON_AddStringToObject(root, f->name, "");
				}
			} 
			else if (f->type == FIELD_TYPE_STRUCT)
			{
				cJSON * child = object_to_jsonobject(ptr, ( metainfo_t *)f->metainfo);
				cJSON_AddItemToObject(root, (char *)f->name, child);
			}
		}
	}

	return root;
}

void object_from_jsonobject(void *obj, metainfo_t *mi, cJSON *json)
{
	int i;
	for (i = 0; i < mi->fs.size; i++)
	{
		field_t *f = &mi->fs.array[i];
		void *ptr = ((char *)obj + f->pos);

		cJSON *item = cJSON_GetObjectItem(json, f->name);
		if (!item)
		{
			continue;
		}

		if (f->islist)
		{
			free_buffer_t *fb = (free_buffer_t *)ptr;

			if (item->type == cJSON_Array)
			{
				cJSON *array = item;
				int size = cJSON_GetArraySize(array);
				int k;
				for (k = 0; k < size; k++)
				{
					cJSON *item = cJSON_GetArrayItem(array, k);
					if (f->type == FIELD_TYPE_INT)
					{
						if (item->type == cJSON_Number)
						{
							LIST_ADD_INT(*fb, item->valueint);
						}
					}
					else if (f->type == FIELD_TYPE_DOUBLE)
					{
						if (item->type == cJSON_Number)
						{
							LIST_ADD_DOUBLE(*fb, item->valuedouble);
						}
					}
					else if (f->type == FIELD_TYPE_CSTR)
					{
						if (item->type == cJSON_String)
						{
							LIST_ADD_STR(*fb, item->valuestring);
						}
					} 
					else if (f->type == FIELD_TYPE_STRUCT)
					{
						if (item->type == cJSON_Object)
						{
							metainfo_t *mi = (metainfo_t *)f->metainfo;
							void *obj = object_new(mi);
							object_from_jsonobject(obj, mi, item);
							free_buffer_append(fb, obj, mi->obj_size);
							free(obj);
						}
					}
				}
			}
		}
		else
		{
			if (f->type == FIELD_TYPE_INT)
			{
				int *p = (int *)ptr;
				if (item->type == cJSON_Number)
				{
					*p = item->valueint;
				}
			}
			else if (f->type == FIELD_TYPE_DOUBLE)
			{
				double *p = (double *)ptr;
				if (item->type == cJSON_Number)
				{
					*p = item->valuedouble;
				}
			}
			else if (f->type == FIELD_TYPE_BOOL)
			{
				BOOL *p = (BOOL *)ptr;
				if (item->type == cJSON_True)
				{
					*p = 1;
				}
				else if (item->type == cJSON_False)
				{
					*p = 0;
				}
			}
			else if (f->type == FIELD_TYPE_CSTR)
			{
				CSTR *p = (CSTR *)ptr;
				if (item->type == cJSON_String)
				{
					*p = CS(item->valuestring);
				}
			} 
			else if (f->type == FIELD_TYPE_STRUCT)
			{
				if (item->type == cJSON_Object)
				{
					metainfo_t *mi = (metainfo_t *)f->metainfo;
					void *obj = ptr;
					object_from_jsonobject(obj, mi, item);
				}
			}
		}
	}
}



}