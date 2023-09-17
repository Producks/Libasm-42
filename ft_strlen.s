global ft_strlen
		section .text
ft_strlen:
		xor		rax, rax			; Set counter to 0
		cmp		rdi, 0				; Check for null pointer?
		je		done				; Go directly to done if NULL ptr
increment:
		cmp		BYTE [rdi + rax], 0 ; Check for \0
		je		done				; If it's \0 jump to done
		inc		rax					; Increment counter by 1
		jmp		increment			; Increment the index
done:
		ret