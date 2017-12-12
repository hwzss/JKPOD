#define _CRT_SECURE_NO_WARNINGS
#include "LCOpenApi_ConstString.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

namespace LCOpenApi{

#ifdef WIN32
#define strdup _strdup
#define snprintf sprintf_s
#define strncasecmp _strnicmp
#endif

const_string_t const_string_new(const char *str)
{
	const_string_t cs;
	cs.cstr = str ? strdup(str) : NULL; // str为NULL时,调用strdup会crash
	return cs;
}

const_string_t const_string_new_length(const char *str, int len)
{
	const_string_t cs;
	cs.cstr = (char *)malloc(len + 1);
	memcpy(cs.cstr, str, len);
	cs.cstr[len] = 0;
	return cs;
}

void const_string_clear(const_string_t cs)
{
	if (cs.cstr)
	{
		free(cs.cstr);
	}
}

int const_string_length(CSTR cs)
{
	if (cs.cstr)
	{
		return (int)strlen(cs.cstr);
	}
	else
	{
		return 0;
	}
}

int const_string_start_with(CSTR cs, const char *str)
{
	if (!str || (const_string_length(cs) < (int)strlen(str)) || (0 == strlen(str)))
	{
		return -1;
	}

	if (0 == strncmp(cs.cstr, str, strlen(str)))
	{
		return 0;
	}

	return -1;
}

int const_string_end_with( CSTR cs, const char *str )
{
	int cs_len = const_string_length(cs);
	int str_len =  (int)strlen(str);
	int i;

	if (cs_len <= 0 || str_len <= 0 || cs_len < str_len)
	{
		return -1;
	}

	for (i = 0; i <= cs_len - str_len; i++)
	{
		if ( (strncmp(cs.cstr + i, str, str_len) == 0) && (i + str_len == cs_len) )
		{
			return 0;
		}
	}

	return -1;
}

void const_string_appendn(CSTR *cs, const char *str, int len)
{
	char *newstr;
	int len1 = const_string_length(*cs);
	int len2 = len;

	if (len1 == 0 && len2 <= 0)
	{
		return;
	}

	newstr = (char*)malloc(len1 + len2 + 1);
	if (!newstr)
	{
		return;
	}

	memcpy(newstr, cs->cstr, len1);
	memcpy(newstr + len1, str, len2);
	newstr[len1 + len2] = 0;

	free(cs->cstr);
	cs->cstr = newstr;
}

void const_string_append(CSTR *cs, const char *str)
{
	if (!str)
	{
		return;
	}

	const_string_appendn(cs, str, (int)strlen(str));
}

void const_string_append_int(CSTR *cs, int n)
{
	char str[16] = {0};
	snprintf(str, sizeof(str), "%d", n);
	const_string_append(cs, str);
}

void const_string_append_double(CSTR *cs, double n)
{
	char str[16] = {0};
	snprintf(str, sizeof(str), "%0.6f", n);
	const_string_append(cs, str);
}

CSTR const_string_sub(CSTR cs, int start_pos, int end_pos)
{
	int len = const_string_length(cs);
	char *newstr;
	CSTR ns;

	if (!cs.cstr)
	{
		return CS("");
	}

	if (start_pos < 0) start_pos = 0;
	if (start_pos > len) start_pos = len;
	if (end_pos > len) end_pos = len;
	if (start_pos > end_pos) start_pos = end_pos;

	newstr = (char *)malloc(end_pos - start_pos + 1);
	if (!newstr)
	{
		return CS("");
	}

	memcpy(newstr, cs.cstr + start_pos, end_pos - start_pos);
	newstr[end_pos - start_pos] = 0;

	ns.cstr = newstr;

	return ns;
}

CSTR const_string_sub_between(CSTR s, const char *begin_str, const char *end_str)
{
	int begin_pos;
	int end_pos;

	begin_pos = const_string_indexof(s, begin_str);
	if (begin_pos < 0)
	{
		return CS("");
	}
	begin_pos += (int)strlen(begin_str);

	end_pos = const_string_indexof_from(s, end_str, begin_pos);
	if (end_pos < 0)
	{
		return CS("");
	}

	return const_string_sub(s, begin_pos, end_pos);
}

CSTR const_string_cat(CSTR cs1, CSTR cs2)
{
	CSTR ns;
	char *newstr;
	int len1 = const_string_length(cs1);
	int len2 = const_string_length(cs2);

	if (len1 == 0 && len2 == 0)
	{
		return CS("");
	}

	newstr = (char *)malloc(len1 + len2 + 1);
	if (!newstr)
	{
		return CS("");
	}

	memcpy(newstr, cs1.cstr, len1);
	memcpy(newstr + len1, cs2.cstr, len2);
	newstr[len1 + len2] = 0;

	ns.cstr = newstr;

	return ns;
}

int const_string_indexof(CSTR cs, const char *str)
{
	return const_string_indexof_from(cs, str, 0);
}

int const_string_indexof_from(CSTR cs, const char *str, int from)
{
	int len = const_string_length(cs);
	int size = (int)strlen(str);
	int i;

	if (len == 0 || !str || (size > len - from))
	{
		return -1;
	}

	for (i = from; i <= len - size; i++)
	{
		if (0 == strncasecmp(cs.cstr + i, str, size))
		{
			return i;
		}
	}

	return -1;
}

CSTR const_string_replace(CSTR cs, const char *from, const char *to)
{
	int start = 0;
	int from_len = (int)strlen(from);
	CSTR rep = CS("");

	while (1)
	{
		int pos = const_string_indexof_from(cs, from, start);
		if (pos < 0)
		{
			const_string_append(&rep, cs.cstr + start);
			break;
		}

		const_string_appendn(&rep, cs.cstr + start, pos - start);
		const_string_append(&rep, to);

		start = pos + from_len;
	}

	return rep;
}

}