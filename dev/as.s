							global _start

							section 	.text
	_start:     xor			rcx, rcx
	hello:
							mov			rax, 1
							mov			rdi, 1
							mov			rdx, 13
							mov			rsi, md
							push		rcx ; fix garbage
							syscall
							pop			rcx ; ???
							inc			rcx
							cmp			rcx, 10
							jne			hello
	exit:		
							mov       	rax, 60
							xor			rdi, rdi
							syscall
							section		.data
	message:		db			"Hello, World", 10
	md:					db			"retard", 10


global ft_list_remove_if
extern free

		section	.text
;void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
; rdi taken arg1
; rsi taken arg2
; rax return value for cmp none in free
; rdx = hold cmp func pointer arg3 push to preserve
; rcx = hold free func pointer arg4 push to preserve
;
; r8 will hold t_list *prev
; r9 will hold t_list *current
; r10 to hold return adress
; r11 used to hold temp data like dereferencing pointer adress
global ft_atoi_base

		section	.text
ft_atoi_base:
		test	rdi, rdi				; Check for NULL ptr's
		jz		return_error
		test	rsi, rsi
		jz		return_error
		xor		rcx, rcx				; Setup counter to 0
check_base:
		cmp		BYTE [rsi + rcx], 0		; while (base[index])
		jne		check_base_value		; base[index] != '\0' jump to check_base_value
		cmp		rcx, 2					; check if length is at least 2
		jb		return_error
		mov		r11, rcx
atoi:
		mov		rdx, 1					; signed = 1
		xor		rcx, rcx				; index = 0
		xor		rax, rax				; total = 0
		mov		r8b, BYTE [rdi]
		cmp		r8b, 43					; check if it's +
		je		set_positive
		cmp		r8b, 45
		je		set_negative			; check if it's -
atoi_loop:
		cmp		BYTE [rdi + rcx], 0		; while (str[index])
		je		done
		xor		r9, r9					; Index for get_number = 0;
get_number:
		cmp		BYTE [rsi + r9], 0		; while (base[index])
		je		calculus				; if true go to calculus
		mov		r10b, BYTE [rdi + rcx]	; r10b = char c
		cmp		r10b, BYTE [rsi + r9]	; c != base[index]
		je		calculus
		inc		r9
		jmp		get_number
calculus:
		cmp		BYTE [rsi + r9], 0		; if (!base[index])
		je		done
		imul	rax, r11				; total * base_valid
		add		rax, r9					; total + number
		inc		rcx
		jmp		atoi_loop
check_base_value:
		mov		r8b, BYTE [rsi + rcx]	; Move it once so I don't have to deference it multiple time
		cmp		r8b, 43					; +
		je		return_error
		cmp		r8b, 45					; -
		je		return_error
		cmp		r8b, 32					;space
		je		return_error
		cmp		r8b, 10					;\n
		je		return_error
		cmp		r8b, 9					;\t
		je		return_error
		cmp		r8b, 11					;\v
		je		return_error
		cmp		r8b, 12					;\f
		je		return_error
		cmp		r8b, 13					;\r
		je		return_error
check_for_double:
		mov		r9, rcx
		inc		r9						; j = index + 1
loop_double:
		cmp		BYTE [rsi + r9], 0		; while (base[j])
		je		increment				; break the loop
		cmp		r8b, BYTE [rsi + r9]	; if (c == base[j])
		je		return_error
		inc		r9						; j++
		jmp		loop_double				; Jump back to while
increment:
		inc		rcx						; rcx++;
		jmp		check_base
set_negative:
		neg		rdx						; signed = -1
set_positive:
		inc		rcx						; index++
		jmp		atoi_loop
return_error:
		xor		rax, rax				; Set return to 0 since an error happened
		ret
done:
		imul	rax, rdx				; total * signed
		ret
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
		mov		rdi, qword [r9]		; Move current->data into arg1
		call	rdx					; Call cmp
		call	restore_registers	; Restore values
		test	rax, rax			; Check if it returned 0
		jnz		move_node			; If the return isn't 0, jump to move_node
		test	r8, r8				; Check if prev is NULL
		jnz		previous_not_null
previous_null:
		mov		r11, [r9 + 8]		; current->next in r11
		mov		[rdi], r11			; *begin_list = current->next
		call	save_registers
		mov		rdi, qword [r9]		; Pass argument
		call	rcx					; Call free function to delete current->data	
		call	restore_registers
		call	save_registers
		mov		rdi, r9				; Pass *current to free 
		call	free wrt ..plt
		call	restore_registers
		mov		r9, [rdi]			; current = *begin_list
		jmp		routine
previous_not_null:
		mov		r11, [r9 + 8]		; current->next in r11
		mov		[r8 + 8], r11		; prev->next = current->next
		call	save_registers
		mov		rdi, qword [r9]
		call	rcx
		call	restore_registers
		call	save_registers
		mov		rdi, r9
		call	free wrt ..plt
		call	restore_registers
		mov		r9, [r8 + 8]
		jmp		routine
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
		push	rbx				; Stack alignment
		push	r10				; GARBAGE FIX
		ret
restore_registers:
		pop		r10
		pop		rbx				; Stack alignment
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
global ft_list_push_front
extern malloc

		section	.text
ft_list_push_front:
		cmp		rdi, 0				; Check for Null ptr **
		je		exit
		push	rdx					; Stack alignment
		push	rsi					; Save data
		push	rdi					; Save begin_list
allocate:
		mov		rdi, 16				; Size of t_list for malloc
		call	malloc wrt ..plt
		cmp		rax, 0				; Check for malloc failure
		je		clean
fill_info:
		pop		rdi
		pop		rsi
		pop		rdx					; Stack alignement
		mov		[rax], rsi			; Give the data to malloc node
		mov		rdx, [rdi]			; Begining of list ptr stored in rdx
		cmp		rdx, 0
		je		null_head			; If head is null, jump to function that handle it
		mov		[rax + 8], rdx		; Give begining to next to malloc node
		mov		[rdi], rax			; Head is the node we generated
		ret
null_head:
		mov		qword [rax + 8], 0	; Next is NULL
		mov		[rdi], rax			; Head is the node we generated
		ret
clean:
		pop		rdi					; Clean stack before we leave
		pop		rsi
		pop		rdx
exit:
		ret