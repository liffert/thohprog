Data Segment

Int2   DB  11101000b
Int10  DW  523
Int16  DD  0F856Ah
Text1 DB  'HoHoHo'

Data ENDS

Code Segment 

NUMBER EQU 5

Innt DB 52
Start:
IF NUMBER
Cli
Jbe good
Inc ah
Dec Innt
Add al, dl
Cmp dl, [edx+esi]
And Innt,dl
Mov al,5
Or byte ptr[edx+esi],NUMBER
ELSE
mov word ptr es:[ebx + ecx], 33
ENDIF
Jbe start
Cli
good:
push dword ptr[eax+eax]
push word ptr[eax+ecx]
push Int16
push Int10


Code ENDS

END
