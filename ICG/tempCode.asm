func PROC
L1:
	PUSH BP
	MOV BP, SP
L2:
	SUB SP, 2
L3:
	MOV AX, 0
	MOV DX, AX
	MOV AX, [BP+4]
	CMP AX, DX
	JE L
	JMP L
L4:
	MOV AX, 0
	JMP L
L5:
	MOV AX, [BP+4]
	MOV [BP-2], AX
	PUSH AX
	POP AX
L6:
	MOV AX, 1
	MOV DX, AX
	MOV AX, [BP+4]
	SUB AX, DX
	PUSH AX
	POP AX
	PUSH AX
	CALL func
	PUSH AX
	MOV AX, [BP-2]
	MOV DX, AX
	POP AX
	ADD AX, DX
	PUSH AX
	POP AX
	JMP L
L7:
	ADD SP, 2
	POP BP
	RET 2
func ENDP
func2 PROC
L8:
	PUSH BP
	MOV BP, SP
L9:
	SUB SP, 2
L10:
	MOV AX, 0
	MOV DX, AX
	MOV AX, [BP+4]
	CMP AX, DX
	JE L
	JMP L
L11:
	MOV AX, 0
	JMP L
L12:
	MOV AX, [BP+4]
	MOV [BP-2], AX
	PUSH AX
	POP AX
L13:
	MOV AX, 1
	MOV DX, AX
	MOV AX, [BP+4]
	SUB AX, DX
	PUSH AX
	POP AX
	PUSH AX
	CALL func
	PUSH AX
	MOV AX, [BP-2]
	MOV DX, AX
	POP AX
	ADD AX, DX
	PUSH AX
	POP AX
	JMP L
L14:
	ADD SP, 2
	POP BP
	RET 2
func2 ENDP
main PROC
L15:
	MOV AX, @DATA
	MOV DS, AX
L16:
	PUSH BP
	MOV BP, SP
L17:
	SUB SP, 2
L18:
	MOV AX, 7
	PUSH AX
	CALL func
	PUSH AX
	POP AX
	MOV [BP-2], AX
	PUSH AX
	POP AX
L19:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
L20:
	MOV AX, 0
	JMP L
L21:
	ADD SP, 2
	POP BP
	MOV AX, 4CH
	INT 21H
main ENDP
