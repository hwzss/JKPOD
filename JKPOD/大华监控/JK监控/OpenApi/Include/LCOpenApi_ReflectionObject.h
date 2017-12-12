#ifndef _LCOPENAPI_REFLECTION_OBJECT_H_
#define _LCOPENAPI_REFLECTION_OBJECT_H_

#include "LCOpenApi_Reflection.h"
#include "cJSON/cJSON.h"

namespace LCOpenApi{
cJSON *object_to_jsonobject(void *obj, metainfo_t *mi);
void object_from_jsonobject(void *obj, metainfo_t *mi, cJSON *json);

}
#endif
