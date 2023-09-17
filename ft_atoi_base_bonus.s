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