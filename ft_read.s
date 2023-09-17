global ft_read
extern __errno_location

		section	.text
ft_read:
		push	rbx
		mov		rax, 0	; Systemcall for read
		syscall
		cmp 	rax, 0
		jl 		error
		pop		rbx
		ret
error:
		neg		rax
		mov		rdi, rax
		call 	__errno_location wrt ..plt
		mov		[rax], rdi
		mov		rax, -1
		pop		rbx
		ret