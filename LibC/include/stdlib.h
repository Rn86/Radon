#ifndef RN_LIB_C_STDLIB_H_INCLUDED
#define RN_LIB_C_STDLIB_H_INCLUDED

typedef struct
{
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

#endif //!RN_LIB_C_STDLIB_H_INCLUDED
