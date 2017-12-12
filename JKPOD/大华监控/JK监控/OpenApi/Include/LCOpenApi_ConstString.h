#ifndef _LCOPENAPI_CONST_STRING_H_
#define _LCOPENAPI_CONST_STRING_H_

namespace LCOpenApi{
typedef struct
{
	char *cstr;
} const_string_t;
const_string_t const_string_new(const char *str);
const_string_t const_string_new_length(const char *str, int len);
void const_string_clear(const_string_t cs);

#define CSTR				const_string_t
#define CS(str)				const_string_new(str)
#define CS_LENGTH(cs)		const_string_length(cs)
#define CS_CLEAR(cs)		const_string_clear(cs), (cs).cstr = NULL

int const_string_length(CSTR cs);
int const_string_start_with(CSTR cs, const char *str);
int const_string_end_with(CSTR cs, const char *str);

void const_string_appendn(CSTR *cs, const char *str, int len);
void const_string_append(CSTR *cs, const char *str);
void const_string_append_int(CSTR *cs, int n);
void const_string_append_double(CSTR *cs, double n);

CSTR const_string_sub(CSTR cs, int start_pos, int end_pos);
CSTR const_string_sub_between(CSTR s, const char *begin_str, const char *end_str);
CSTR const_string_cat(CSTR cs1, CSTR cs2);

int const_string_indexof(CSTR cs, const char *str);
int const_string_indexof_from(CSTR cs, const char *str, int from);

CSTR const_string_replace(CSTR cs, const char *from, const char *to);

}
#endif
