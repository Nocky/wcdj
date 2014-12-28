/*
 * This makes an infinite loop because context holds the program counter.
 */

#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

volatile int g_ivar = 1;
 
int main(int argc, const char *argv[]){
	ucontext_t context;
 
	printf("before getcontext: g_ivar[%d]\n", g_ivar);

	getcontext(&context);

	g_ivar = 2;

	printf("after getcontext: g_ivar[%d]\n", g_ivar);

	puts("Hello world");
	sleep(1);
	setcontext(&context);

	return 0;
}
/*
gcc -o demo_loop_simple demo_loop_simple.c -D_XOPEN_SOURCE -Wno-deprecated-declarations

output:
gerryyang@mba:demo$./demo_loop_simple 
before getcontext: g_ivar[1]
after getcontext: g_ivar[2]
Hello world
after getcontext: g_ivar[2]
Hello world
after getcontext: g_ivar[2]
Hello world
^C

 */