    .data
A: .int 0
    .text
    .global supersum
CFHAPPEN:
    movb $1, 1(%ecx, %edx, 1)
    movl $1, A
    jmp next
CFHAPPEN2:
    movb $1, 1(%ecx, %edx, 1)
    movl $1, A
    jmp home
IFINCL0:
    movb $0, (%ecx, %edx, 1)
    jmp next2
CFNOTHAPPEN:
    movb $0, 1(%ecx, %edx, 1)
    movl $0, A
    jmp next
end: 
    addl A, %edx
    movl %edx, %eax
    pop %ebp
    pop %edi
    pop %esi
    pop %ebx
    pop %ecx
    ret

ifesinull:
    cmp $0, %edi
    jle end
    movb (%ebx, %edx, 1), %al
    
    jmp fromnull 

ifedinull:
    cmp $0, %esi
    jle end
    movb (%ebp, %edx, 1), %al
    jmp fromnull
supersum:
    push %ecx
    push %ebx
    push %esi
    push %edi
    push %ebp
// counter
    xor %edx, %edx
    movl %eax, %ebp
    xor %eax, %eax
    // chek that normal numbers
    cmp $0, %esi
    jle ifesinull
    cmp $0, %edi
    jle ifedinull
truesizeesi:
    cmpb $0, -1(%ebp, %esi, 1)
    jnz truesizeedi
    decl %esi
    jmp truesizeesi
truesizeedi:
    cmpb $0, -1(%ebx, %edi, 1)
    jnz GroundPlus
    decl %edi
    jmp truesizeedi
GroundPlus:
    xor %eax, %eax
    // A - %ebp
    // B - %ebx
    // C - %ecx
    cmp $0, %esi
    jle ifesinull
    cmp $0, %edi
    jle ifedinull
    movb (%ebp, %edx, 1), %ah
    movb (%ebx, %edx, 1), %al
    // cmp $0, %ah
    // je AHZERO
NOTAHZERO:    
    // -bite in A
fromnull:
    decl %esi 
    // -bite in B
    decl %edi
    // jmp if %edi == 0
    // movb $0, (%ecx, %edx, 1)    
    addb %ah, %al
    jc CFHAPPEN
    jnc CFNOTHAPPEN
    //JMP if  CFHAPPEN
next:
    cmp $0, %edx
    je IFINCL0
next2:
    addb %al, (%ecx, %edx, 1)  
    jc CFHAPPEN2
home:  
    incl %edx
    jmp GroundPlus

