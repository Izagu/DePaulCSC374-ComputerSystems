#include <stdio.h>
#include <stdlib.h>

int 	fib (int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);

	return (fib(n-1) + fib(n-2));
}


//   push rbp
// * mov rsp,rbp
// * sub 0x10, rsp
// * mov edi, -0xC(rbp)
// * cmpl 0x0 -0xC (rbp)
// * jne case1
// * move 0x0, eax
// * jmp theEnd
//Case1:
//   cmpl 0x1, -0xC(rbp)
//   jnw case2
//   move 0x0 eax
//   jmp theEnd
//Case2:
//   mov -0xC(rbp), eax
//   sub 0x1, eax
//   mov eax, edi
//   call fib
//   mov eax, -0x10(rbp)
//   sub 0x2, eax
//   mov eax, edi
//   call fib
//   add -0x10(rpi), eax
//theEnd:
//   leave
//   ret


