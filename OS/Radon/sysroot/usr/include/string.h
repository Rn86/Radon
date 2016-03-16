#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);
void* strcpy(void* __restrict, const void* __restrict);
char *strchr(const char *str, int c);
int strcmp(const char* s1, const char* s2);
size_t strspn(const char *str1, const char *str2);
char *strstr(const char *haystack, const char *needle);

#ifdef __cplusplus
}
#endif

#endif
