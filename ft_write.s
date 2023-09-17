global ft_write
extern	__errno_location

		section	.text
ft_write:
		mov		rax, 1			; System call for write
		push	rbx				; Stack alignment
		syscall
		cmp		rax, 0			; Check for return value
		jl		error			; Jump if it's negative
		pop		rbx
		ret
error:
		neg		rax				; Make rax positive
		mov		rdi, rax		; Save rax value
		call 	__errno_location wrt ..plt
		mov		[rax], rdi		; Set errno
		mov		rax, -1			; Set back return value to -1 for write
		pop		rbx				; Stack alignment
		ret