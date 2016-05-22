#ifndef RN_LIB_C_STRING_H_INCLUDED
#define RN_LIB_C_STRING_H_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void*, const void*, size_t);
void * memcpy(void *dest, const void *src, size_t n);
void * memmove(void*, const void*, size_t);
void * memset(void *s, int c, size_t n);
size_t strlen(const char*);
char * strcpy(char *dest, const char *src);
char * strchr(const char *str, int c);
int strcmp(const char* s1, const char* s2);
size_t strspn(const char *s1, const char *s2);
char * strstr(const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif

#endif //!RN_LIB_C_STRING_H_INCLUDED
