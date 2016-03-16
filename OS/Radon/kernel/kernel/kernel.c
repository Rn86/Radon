#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_early(void)
{
	terminal_initialize();
}

void kernel_main(void)
{
	char oo[5] = "aaaaa";
	printf("Hello, %s kernel World!\n",oo);
	
	char src[40];
	char dest[100];
  
	memset(dest, '\0', sizeof(dest));
	strcpy(src, "This is tutorialspoint.com");
	strcpy(dest, src);

	printf("Final copied string : %s\n", dest);
}
