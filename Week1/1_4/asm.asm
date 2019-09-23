.cpu cortex-m0
.text
.align 2
.global print_asciz
.global application
.global convert_char



print_asciz:
	MOV R4, R0
loop:
	LDRB R0, [ R4 ]
	ADD R0, #0
	BEQ done
	BL convert_char
	ADD R4, #1
	B loop
done:
	POP { R4, PC }

application:
	PUSH { R4, LR }
	B print_asciz

convert_char:
	MOV R1, #'a'
	SUB R1, #'A'
	CMP R0, #'z'
	BGT print
	CMP R0, #'A'
	BLT print
	CMP R0, #'Z'
	BLE upper
	CMP r0, #'a'
	BGE lower
	B print
upper:
	ADD R0, R1
	B print
lower:
	SUB R0, R1
	B print
print:
	B uart_put_char
	MOV PC, LR