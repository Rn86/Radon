#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int quot;
  int rem;
} div_t;

__attribute__((__noreturn__))
void abort(void);
int abs(int x);
int atoi(const char *str);
long int atol(const char *str);
div_t div(int numer, int denom);
long int labs(long int x);

#ifdef __cplusplus
}
#endif

#endif
