global ft_list_sort

		section	.text
ft_list_sort:
		push	rbx					; Stack alignement and save rbx so we can use it
		test	rdi, rdi			; Check for NULL ptr
		jz		done
		test	rsi, rsi			; Check for NULL ptr
		jz		done
		mov		rbx, qword [rdi]	; Save begining ptr in rbx preserved register
		test	rbx, rbx			; Check if it's pointing to NULL
		jz		done
		push	r12					; Preserve r12
		mov		r12, 1				; Store flag in r12 preserved register
		push	r13					; Preserve r13
		mov		r13, rsi			; Store func ptr i n rcx
setup:
		test	r12, r12			; Check if any swap was done
		jz		pop_deez			; If not, jump to done
		xor		r12, r12			; Set sorting flag to none
		mov		rcx, rbx			; *current = *begin
routine:
		mov		rdx, qword [rcx + 8]; Store next ptr in rdx
		test	rdx, rdx			; Check if -> next is null
		jz		setup
		mov		rdi, qword [rcx]	; Store current->data
		mov		rsi, qword [rdx]	; Store current->next->data
		push	rdx					; Save *current->next
		push	rcx					; Save *current
		call	r13					; Call the func *
		pop		rcx					; Restore *current
		pop		rdx					; Restore *current->next
compare:
		cmp		rax, 1
		je		swap				; Jump if rax = 1
		mov		rcx, rdx			; SEND HELP
		jmp		routine				; Keep looping
swap:
		mov		rdi, qword [rcx]	; Store current->data
		mov		rsi, qword [rdx]	; Store current->next->data
		mov		[rcx], rsi			; Second value is now the first one
		mov		[rdx], rdi
		mov		r12, 1				; Set flag(r12) swap to true
		jmp		setup				; Go back to begining(setup)
pop_deez:
		pop		r13
		pop		r12					; Restore r12 (calling conventation)
done:
		pop		rbx					; Stack alignement and restore rbx to the original value
		ret