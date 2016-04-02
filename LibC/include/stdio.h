#ifndef RN_LIB_C_STDIO_H_INCLUDED
#define RN_LIB_C_STDIO_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif //!RN_LIB_C_STDIO_H_INCLUDED
