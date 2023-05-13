.global partition

partition:
    //edx - start
    // eax - end
    xor %edx, %edx
    movl %esi, %eax
    decl %eax
    xor %ecx, %ecx
while1:
    cmp %edx, %eax
    jle getanswer
while2:
    cmp %esi, %edx
    jge while3
    cmpw (%ebx, %edx, 2), %di
    jle while3
    incl %edx
    jmp while2       
while3:
    cmp $0, %eax
    jl if1 
    cmpw %di, (%ebx, %eax, 2)
    jl if1
    decl %eax
    jmp while3
if1: 
    cmp %edx, %eax 
    jle getanswer
    xor %ecx, %ecx
    movw (%ebx, %eax, 2), %cx
    xchgw %cx, (%ebx, %edx, 2)
    movw %cx, (%ebx, %eax, 2)
    jmp while1 
getanswer:
     movl $-1, %eax
next:
     incl %eax
     cmpw (%ebx, %eax, 2), %di
     jg next
     movl %eax, %edx
     ret

