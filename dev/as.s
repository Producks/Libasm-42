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