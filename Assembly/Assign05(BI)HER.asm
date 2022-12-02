.386
.MODEL FLAT, stdcall
.stack 4096

ExitProcess PROTO, dwExitCode:DWORD

.DATA
	pe DWORD 25, 89, 49, 80
	pp DWORD 30, 100, 50, 150
	k  DWORD 0
	n  DWORD ?
	sum DWORD ?
.CODE
_main PROC
	mov esi, OFFSET pe
	mov edi, OFFSET pp
	mov n, LENGTHOF pe ;hold total number of items
	
	;setting registers to 0
	sub eax, eax 
	sub ebx, ebx	
	xor edx, edx
	xor ecx, ecx
l1: 
	add eax, [esi + ecx * 4]	;adding each element in array to eax 
	add ebx, [edi + ecx * 4]	;adding each element in array to ebx 
	inc ecx		; adding 1 to exc to point to next element in array
	mov k, ecx	; keep track of current item
	cmp ecx, LENGTHOF pe
	jne l1		; jump back to l1
	jmp l2		; jump to l2
l2:
	imul eax, 100	;do integer multiplication
	div ebx		;using the diviser ebx to divide eax
	mov sum, eax	;mov to sum
	
	INVOKE ExitProcess, 0
_main ENDP
END