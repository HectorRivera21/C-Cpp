.386
.MODEL FLAT, C
.stack 4096

ExitProcess PROTO stdcall, dwExitCode:DWORD

.DATA
	Ct DWORD 32
	Ft DWORD ?
	A1 DWORD 9
	B1 DWORD 5
.CODE
_main PROC
	
	push Ct ;push 32 into stack
	push A1 ;push 9 into stack
	push B1 ;push 5 into stack
	call _convertC2F ;calling function
	add esp, 8 ;stack caller cleaner
	
	mov Ft, eax ;move the final conversion to Ft 

_main ENDP
_convertC2F PROC
	;create frame for stack
	push ebp 
	mov ebp, esp
	;move stack values into registers
	mov eax, [ebp + 16]
	mov ebx, [ebp + 12]
	mov ecx, [ebp + 8]
	xor edx, edx

	imul eax, ebx ;mutiply eax and ebx
	div ecx ;divide eax by ecx
	add eax, 32 ;add 
	
	pop ebp ;pop the stack frame

	ret ;return 
 _convertC2F ENDP
END