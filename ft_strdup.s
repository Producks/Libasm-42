global ft_strdup
extern ft_strcpy
extern ft_strlen
extern malloc

		section	.text
ft_strdup:
		cmp		rdi, 0		; Check for NULL ptr
		je		error
		push	rdi			; Save ptr on the stack for later
get_length:
		call	ft_strlen
		inc		rax
		mov		rdi, rax	; Give the length to rdi
allocate:
		call	malloc wrt ..plt
		pop		rsi			; Remove from stack and alignment
		cmp		rax, 0		; Check for failure
		je		error		; Leave if malloc failure
copy:
		mov		rdi, rax	; Give malloc ptr to rdi
		push	rdx			; Stack alignment
		call	ft_strcpy
		pop		rdx			; Stack alignment
		ret
error:
		xor		rax, rax
		ret