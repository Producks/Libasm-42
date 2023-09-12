global _ft_strdup
extern _ft_strcpy
extern _ft_strlen
extern malloc

		section	.text
_ft_strdup:
		cmp		rdi, 0		; Check for NULL ptr
		je		error
		push	rdi			; Save ptr on the stack for later
get_length:
		call	_ft_strlen
		inc		rax
		mov		rdi, rax	; Give the length to rdi
allocate:
		call	malloc wrt ..plt
		pop		rsi			; Remove from stack
		cmp		rax, 0		; Check for failure
		je		error		; Leave if malloc failure
copy:
		mov		rdi, rax	; Give malloc ptr to rdi
		call	_ft_strcpy
		ret
error:
		xor		rax, rax
		ret