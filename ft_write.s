				global _ft_write

				section 	.text
				extern 		__errno_location
_ft_write:
				mov				rax, 1			; syscall for write
				syscall
				cmp				rax, 0			; Check for return value
				jl				error				; Jump if it's negative
				ret										; return if no error
error:
				neg				rax					; make rax positive
				mov				rdi, rax		; save rax value
				call			__errno_location wrt ..plt ; ..plt to fix gcc compliation issue on linux, what garbage is this?
				mov				[rax], rdi	; set errno
				mov				rax, -1			; set back return value to -1 for write
				ret										; return