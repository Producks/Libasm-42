global ft_list_size

		section	.text
ft_list_size:
		xor		rax, rax			; Set the counter to 0
		test	rdi, rdi			; Check for null ptr
		jz		done
routine:
		mov		rdi, [rdi + 8]
		inc		rax
		test	rdi, rdi			; Check *next for content
		jnz		routine
done:
		ret