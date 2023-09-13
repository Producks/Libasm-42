global ft_strcmp

		section	.text
ft_strcmp:
		cmp	rdi, 0	; Check for NULL ptr
		je	done
		cmp	rsi, 0	; Check for NULL ptr
		je	done
routine:
		mov	al, BYTE [rdi]
		mov	dl, BYTE [rsi]
		cmp	al, dl
		jne	not_equal
		cmp	al, 0
		je	done
		inc rdi		; Incrementing pointer directly
		inc rsi
		jmp routine
not_equal:			; Linux implementation done, mac one is different
		cmp al, dl
		jb	negative
positive:
		mov rax, 1
		ret
negative:
		mov rax, -1
		ret
done:
		xor	rax, rax
		ret