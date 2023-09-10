global _ft_strlen

						section		.text
_ft_strlen:	xor				rax, rax 	; Set counter to 0
						cmp				rdi, 0		; check for null pointer?
						je				done			; go directly to done if NULL ptr
increment:
						cmp				BYTE [rdi + rax], 0 ; Check for \0
						je				done			; if it's \0 jump to done
						inc				rax				; Increment counter by 1
						jmp				increment	; Increment the index
done:
						ret