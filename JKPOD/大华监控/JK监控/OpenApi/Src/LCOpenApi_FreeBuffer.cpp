#include "LCOpenApi_FreeBuffer.h"
#include <stdlib.h>
#include <memory.h>

namespace LCOpenApi{
#define BLOCK_SIZE	1024
#define CEIL(n)		((n) + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE

void free_buffer_init(free_buffer_t *buf)
{
	memset(buf, 0, sizeof(free_buffer_t));
}

void free_buffer_append(free_buffer_t *buf, void *data, size_t len)
{
	size_t need_len = buf->length + len + 1;
	if (need_len > buf->size)
	{
		size_t newlen = buf->length + len;
		size_t newsize = CEIL(need_len);

		char *newptr = (char *)malloc(newsize);
		memcpy(newptr, buf->ptr, buf->length);
		if (data)
		{
			memcpy(newptr + buf->length, data, len);
		}
		else
		{
			memset(newptr + buf->length, 0, len);
		}

		free(buf->ptr);
		buf->ptr = newptr;
		buf->length = newlen;
		buf->size = newsize;
	}
	else
	{
		if (data)
		{
			memcpy(buf->ptr + buf->length, data, len);
		}
		else
		{
			memset(buf->ptr + buf->length, 0, len);
		}
		buf->length += len;
	}

	buf->ptr[buf->length] = 0;

	buf->count++;
}

void free_buffer_clear(free_buffer_t *buf)
{
	buf->length = 0;
	buf->count = 0;
}

void free_buffer_destroy(free_buffer_t *buf)
{
	if (buf->ptr)
	{
		free(buf->ptr);
	}
	buf->ptr = NULL;
	buf->length = 0;
	buf->size = 0;
	buf->count = 0;
}

}