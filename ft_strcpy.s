global _ft_strcpy

section		.text
;char *strcpy(char *dest, const char *src);
_ft_strcpy:
						cmp	rdi, 0			; Check for null ptr
						je 	error
						cmp	rsi, 0
						je	error
						xor	rcx, rcx		; Set counter to 0
copy_routine:
						mov	r8, [rsi + rcx]
						mov	[rdi + rcx], r8
						cmp	BYTE [rdi + rcx], 0
						je	end
						inc	rcx
						jmp	copy_routine
end:
						mov	rax, rdi
						ret
error:
						mov	rax, 0			; Return NULL if any of the string were NULL
						ret