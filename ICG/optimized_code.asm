;-------
;
;-------
.MODEL SMALL
.STACK 1000H
.Data
	number DB "00000$"
	CR EQU 0DH
	LF EQU 0AH
.CODE
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
	JE L4
	JMP L4
L4:
	MOV AX, 0
	JMP L
L5:
	MOV AX, [BP+4]
	MOV [BP-2], AX
L6:
	MOV AX, 1
	MOV DX, AX
	MOV AX, [BP+4]
	SUB AX, DX
	PUSH AX
	CALL func
	PUSH AX
	MOV AX, [BP-2]
	MOV DX, AX
	POP AX
	ADD AX, DX
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
	JE L11
	JMP L11
L11:
	MOV AX, 0
	JMP L
L12:
	MOV AX, [BP+4]
	MOV [BP-2], AX
L13:
	MOV AX, 1
	MOV DX, AX
	MOV AX, [BP+4]
	SUB AX, DX
	PUSH AX
	CALL func
	PUSH AX
	MOV AX, [BP-2]
	MOV DX, AX
	POP AX
	ADD AX, DX
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
	MOV [BP-2], AX
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
new_line PROC

	push ax
	push dx
	mov ah,2
	mov dl,cr
	int 21h
	mov ah,2
	mov dl,lf
	int 21h
	pop dx
	pop ax
	ret
new_line endp
print_output proc  ;print what is in ax
	push ax
	push bx
	push cx
	push dx
	push si
	lea si,number
	mov bx,10
	add si,4
	cmp ax,0
	jnge negate
print:
	xor dx,dx
	div bx
	mov [si],dl
	add [si],'0'
	dec si
	cmp ax,0
	jne print
	inc si
	lea dx,si
	mov ah,9
	int 21h
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	ret
negate:
	push ax
	mov ah,2
	mov dl,'-'
	int 21h
	pop ax
	neg ax
	jmp print
print_output endp
END MAIN
