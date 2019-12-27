Data Segment
	
	Int8 	DB	00001000b
	Int16 	DW	124
	Int32	DD 	0Fa010000h
	
Data ENDS
Code Segment
	Dudu	DD	69
	Sti
	jnz @merch
	Dec AL
	@20:
	Inc Dudu[ecx + eax*2]

	and Int8, AL
	mov ebx, es:Int32[ecx + eax*2]
	or ecx, (0ABC0h + 386)*2 + 9
		
	cmp eax, ebx
	jnz @20
	@merch:
	add Int16[ecx + eax*4], 202 + 2
		
		

Code ENDS

END