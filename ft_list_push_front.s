global ft_list_push_front
extern malloc

;void ft_list_push_front(t_list **begin_list, void *data);
		section	.text
ft_list_push_front:
		cmp		rdi, 0			; Check for Null ptr **
		je		exit
		push	rdx				; Stack alignment
		push	rsi				; Save data
		push	rdi				; Save begin_list
allocate:
		mov		rdi, 16			; Size of t_list for malloc
		call	malloc wrt ..plt
		cmp		rax, 0			; Check for malloc failure
		je		clean
fill_info:
		pop		rdi
		pop		rsi
		pop		rdx				; Stack alignement
		mov		[rax], rsi		; Give the data to malloc node
		mov		rdx, [rdi]		; Begining of list ptr stored in rdx
		cmp		rdx, 0
		je		null_head		; If head is null, jump to function that handle it
		mov		[rax + 8], rdx	; Give begining to next to malloc node
		mov		[rdi], rax		; Head is the node we generated
		ret
null_head:
		mov		qword [rax + 8], 0	; Next is NULL
		mov		[rdi], rax			; Head is the node we generated
		ret
clean:
		pop		rdi				; Clean stack before we leave
		pop		rsi
		pop		rdx
exit:
		ret