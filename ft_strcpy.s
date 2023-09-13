global ft_strcpy

		section	.text
ft_strcpy:
		cmp	rdi, 0		; Check for NULL ptr
		je	error
		cmp	rsi, 0		; Check for NULL ptr
		je	error
		xor	rcx, rcx	; Set counter to 0
copy_routine:
		mov	dl, [rsi + rcx]
		mov	[rdi + rcx], dl
		cmp	BYTE [rdi + rcx], 0
		je	end
		inc	rcx
		jmp	copy_routine
end:
		mov	rax, rdi
		ret
error:
		xor	rax, rax	; Return NULL if any of the string were NULL
		ret