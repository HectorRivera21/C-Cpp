.386
.MODEL FLAT, stdcall
.stack 4096

ExitProcess PROTO, dwExitCode:DWORD

.DATA
	f1	DWORD	0
	f2	DWORD	1
	sum DWORD	0 ;sum to hold the sum of eax and ebx
	oddsum DWORD 1;hold the sum of all odd numbers
.CODE
_main PROC
l1:
	mov eax, [f1] ;move previous number in sequence into eax
	mov ebx, [f2] ;move next sequence number into ebx

	mov ecx, 1000000 ;literal 1million for comparison 
	
	add eax, ebx ;add eax and ebx together
	cmp ecx, eax ;compare ecx to eax to check whether over 1million
	jl exit ;if over 1million go to exit 
	mov [sum], eax ;move value of eax into sum
	
	mov ebx, eax ;move value of eax into ebx
	;checking if eax is even or odd by remainder of 1 or 0
	mov ecx, 2 
	xor edx, edx
	div ecx
	;compare remainder edx with 1 for odd and if not 1 then its even
	mov eax , 1
	cmp edx ,eax
	;go to l2 if even / continue here if odd
	jnz l2
	
	mov eax, [oddsum] ;move oddsum into eax
	
	add eax, ebx ;add eax and ebx
	mov [oddsum], eax ;move eax into oddsum

l2:
	mov ebx, [f2] ;move f2 into ebx
	mov [f1], ebx ;move ebx into f1

	mov ebx, [sum]; move sum into ebx

	mov [f2], ebx ;move ebx into f2

	jmp l1 ;jump to l1

exit:
mov eax, [oddsum]; move oddsum into eax
	INVOKE ExitProcess, 0
_main ENDP
END