DS_HEADER equ	0xF00FF00F

SECTION .text
BITS 32

EXTERN main
EXTERN fault
EXTERN cls

GLOBAL entry
GLOBAL tsscall

entry:
	mov eax,[ds_magic]
	cmp eax,DS_HEADER
	je ds_ok

	mov word [0B8000h],9F44h
	jmp short $
	
ds_ok:

	lgdt [gdt_ptr]

	mov ax,LINEAR_DATA_SEL
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
  
	mov ax,LINEAR_STACK_SEL

	mov ss,ax
    
	jmp LINEAR_CODE_SEL:dstart
	
dstart:

  mov esp,0x1100000

	mov ecx,(idt_end - idt) >> 3 
	mov edi,idt
	mov esi,isr0
	
fix_idt:
  
	mov eax,esi			
	mov [edi],ax		
	shr eax,16
	mov [edi + 6],ax
   
	add edi,8			
	add esi,(isr1 - isr0)		
	loop fix_idt

	lidt [idt_ptr]
	
	call main
	jmp $

MULTIBOOT_PAGE_ALIGN	equ 1<<0
MULTIBOOT_MEMORY_INFO	equ 1<<1
MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

ALIGN 4
mboot:
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_CHECKSUM

%macro PUSHB 1
	db 6Ah
	db %1
%endmacro


%macro INTR 1
global isr%1
isr%1:
	push byte 0
  push esp
  push ss
	PUSHB %1		
	push gs			
	push fs			
	push es			
	push ds			
	pusha				
		mov ax,LINEAR_DATA_SEL
		mov ds,eax
		mov es,eax
		mov fs,eax
		mov gs,eax
		mov eax,esp
		push eax		
.1:
			mov eax,fault
			call eax
			jmp all_ints
%endmacro		

%macro INTR_EC 1
global isr%1
isr%1:
	nop				
	nop
  push esp
  push ss
	PUSHB %1
	push gs		
	push fs		
	push es		
	push ds		
	pusha			
		mov ax,LINEAR_DATA_SEL	
		mov ds,eax	
		mov es,eax	
		mov fs,eax	
		mov gs,eax	
		mov eax,esp	
		push eax		
.1:
			mov eax,fault
			call eax	
			jmp all_ints
%endmacro				

all_ints:
		pop eax
	popa			
	pop ds		
	pop es
	pop fs
	pop gs
	add esp,14  
	iret

getvect:
	push ebp
		mov ebp,esp
		push esi
		push ebx
			mov esi,[ebp + 8]

			xor ebx,ebx
			mov bl,[ebp + 12]
			shl ebx,3
			mov al,[idt + ebx + 5]
			mov [esi + 0],eax

			mov eax,isr1
			sub eax,isr0
			mul byte [ebp + 12]
			mov ebx,eax
			add ebx,isr0
			mov eax,[ebx + (isr0.1 - isr0 + 1)]
			mov [esi + 4],eax
		pop ebx
		pop esi
	pop ebp
	ret

setvect:
	push ebp
		mov ebp,esp
		push esi
		push ebx
			mov esi,[ebp + 8]

			mov eax,[esi + 0]
			xor ebx,ebx
			mov bl,[ebp + 12]
			shl ebx,3
			mov [idt + ebx + 5],al

			mov eax,isr1
			sub eax,isr0
			mul byte [ebp + 12]
			mov ebx,eax
			add ebx,isr0
			mov eax,[esi + 4]
			mov [ebx + (isr0.1 - isr0 + 1)],eax
		pop ebx
		pop esi
	pop ebp
	ret

	INTR 0		; zero divide (fault)
	INTR 1		; debug/single step
	INTR 2		; non-maskable interrupt (trap)
	INTR 3		; INT3 (trap)
	INTR 4		; INTO (trap)
	INTR 5		; BOUND (fault)
	INTR 6		; invalid opcode (fault)
	INTR 7		; coprocessor not available (fault)
	INTR_EC 8	; double fault (abort w/ error code)
	INTR 9		; coproc segment overrun (abort; 386/486SX only)
	INTR_EC 0Ah	; bad TSS (fault w/ error code)
	INTR_EC 0Bh	; segment not present (fault w/ error code)
	INTR_EC 0Ch	; stack fault (fault w/ error code)
	INTR_EC 0Dh	; GPF (fault w/ error code)
	INTR_EC 0Eh	; page fault
	INTR 0Fh	; reserved
	INTR 10h	; FP exception/coprocessor error (trap)
	INTR 11h	; alignment check (trap; 486+ only)
	INTR 12h	; machine check (Pentium+ only)
	INTR 13h
	INTR 14h
	INTR 15h
	INTR 16h
	INTR 17h
	INTR 18h
	INTR 19h
	INTR 1Ah
	INTR 1Bh
	INTR 1Ch
	INTR 1Dh
	INTR 1Eh
	INTR 1Fh

	INTR 20h	; IRQ 0/timer interrupt
	INTR 21h	; IRQ 1/keyboard interrupt
	INTR 22h
	INTR 23h
	INTR 24h
	INTR 25h
	INTR 26h	; IRQ 6/floppy interrupt
	INTR 27h
	INTR 28h	; IRQ 8/real-time clock interrupt
	INTR 29h
	INTR 2Ah
	INTR 2Bh
	INTR 2Ch
	INTR 2Dh	; IRQ 13/math coprocessor interrupt
	INTR 2Eh	; IRQ 14/primary ATA ("IDE") drive interrupt
	INTR 2Fh	; IRQ 15/secondary ATA drive interrupt

; syscall software interrupt
	INTR 30h

%assign i 31h
%rep (0FFh - 30h)

	INTR i

%assign i (i + 1)
%endrep


;LoadTR:
;	mov ebp, esp
;	mov eax, (ebp+8)
;	ltr (eax)
;	ret

tsscall:
	jmp 0x20:cls
	ret
	
SECTION .data

ds_magic:
	dd DS_HEADER

gdt:
	dw 0			
	dw 0			
	db 0			
	db 0			
	db 0			
	db 0			

	dw 0
	dw 0
	db 0
	db 0
	db 0
	db 0

LINEAR_DATA_SEL	equ	$-gdt
	dw 0FFFFh
	dw 0
	db 0
	db 92h			
	db 0CFh     
	db 0

LINEAR_CODE_SEL	equ	$-gdt
	dw 0FFFFh
	dw 0
	db 0
	db 9Ah		
	db 0CFh   
	db 0 

LINEAR_STACK_SEL	equ	$-gdt
	dw 0x0800
	dw 0
	db 0
	db 0x96
	db 0xC0
	db 0
      
%rep 251 ; FB = (0xFF - 0x4) Clean GDT Entry - might be useful in future
;NULL ENTRY
	dw 0
	dw 0
	db 0
	db 0
	db 0
	db 0
%endrep
	
gdt_end:

gdt_ptr:
	dw gdt_end - gdt - 1
	dd gdt

idt:
%rep 32
	dw 0			
	dw LINEAR_CODE_SEL
	db 0	
	db 8Eh
	dw 0	
%endrep

;sys_task_gate:
;	dw 0
;	dw 72
;	db 0
;	db 85h
;	dw 0

%rep 16
	dw 0
	dw LINEAR_CODE_SEL
	db 0
	db 8Eh
	dw 0
%endrep

_sys_call:
	dw 0
	dw LINEAR_CODE_SEL
	db 0
	db 0xEE
	dw 0
   
%rep 207
	dw 0
	dw LINEAR_CODE_SEL
	db 0
	db 8Eh
	dw 0
%endrep

idt_end:

idt_ptr:
	dw idt_end - idt - 1
	dd idt	
		