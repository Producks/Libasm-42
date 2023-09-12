global _ft_strdup
section		.text
extern _ft_strcpy
extern _ft_strlen
extern malloc

;char 		*_ft_strdup(const char *s);
_ft_strdup:
						cmp		rdi, 0			; Check for NULL ptr
						je		error				; Jump if NULL
						push	rdi					; save ptr for later
get_length:
						call	_ft_strlen
						inc		rax
						mov		rdi, rax		; give the length to rdi
allocate:
						call	malloc wrt ..plt
						cmp		rax, 0			; check for failure
						je		error				; leave if malloc failure
copy:
						pop		rsi
						mov		rdi, rax		; give ptr to rdi
						call	_ft_strcpy
						ret
error:
						xor		rax, rax
						ret