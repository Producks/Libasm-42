global ft_list_remove_if
extern free

		section	.text
; rdi taken arg1
; rsi taken arg2
; rax return value for cmp none in free
; rdx = hold cmp func pointer arg3 push to preserve
; rcx = hold free func pointer arg4 push to preserve
; r8 will hold t_list *prev
; r9 will hold t_list *current
; r10 to hold return adress
; r11 used to hold temp data like dereferencing pointer adress
ft_list_remove_if:
		test	rdi, rdi		; Check all ptr for NULL, exit if any of them are
		jz		done
		test	rsi, rsi
		jz		done
		test	rdx, rdx
		jz		done
		test	rcx, rcx
		jz		done
		xor		r8, r8				; Make T_list *prev NULL
		mov		r9, [rdi]			; Get the begining of the list
routine:
		test	r9, r9				; Check if current is NULL
		jz		done				; If so, end the loop and leave the function
compare:
		call	save_registers		; Save values
		xor		rdi, rdi
		mov		rdi, qword [r9]		; Move current->data into arg1
		push	rdi
		call	rdx					; Call cmp
		pop		rdi
		call	restore_registers	; Restore values
		test	rax, rax			; Check if it returned 0
		jnz		move_node			; If the return isn't 0, jump to move_node
		test	r8, r8				; Check if prev is NULL
		jnz		previous_not_null
previous_null:
		mov		r11, [r9 + 8]		; current->next in r11
		mov		[rdi], r11			; *begin_list = current->next
		call	free_element
		mov		r9, [rdi]			; current = *begin_list
		jmp		routine
previous_not_null:
		mov		r11, [r9 + 8]		; current->next in r11
		mov		[r8 + 8], r11		; prev->next = current->next
		call	free_element
		mov		r9, [r8 + 8]
		jmp		routine
free_element:
		call	save_registers
		mov		rdi, qword [r9]
		call	rcx
		call	restore_registers
		call	save_registers
		mov		rdi, r9
		call	free wrt ..plt
		call	restore_registers
		ret
move_node:
		mov		r8, r9				; prev = current
		mov		r9, [r9 + 8]		; DOUBLE CHECK IF THERE A BUG! SHOULD WORK? current = current->next
		jmp		routine
save_registers:
		pop		r10				; LMAO
		push	rdi
		push	rsi
		push	rdx
		push	rcx
		push	r8
		push	r9
		push	r10				; GARBAGE FIX
		ret
restore_registers:
		pop		r10
		pop		r9
		pop		r8
		pop		rcx
		pop		rdx
		pop		rsi
		pop		rdi
		push	r10
		ret
done:
		ret