#ifndef _LCOPENAPI_ALGORITHM_H_
#define _LCOPENAPI_ALGORITHM_H_

namespace LCOpenApi{
int common_algorithm_md5(char *str, char *outbuf);
int common_algorithm_md5_lowercase(char *str, char *outbuf);
int common_algorithm_base64(char *data, int len, char *out);
int common_algorithm_sha1(char *data, int len, char *outbuf);
int common_algorithm_hmacsha1(char *data, int len, char *key, int key_len, char *outbuf);

}

#endif
