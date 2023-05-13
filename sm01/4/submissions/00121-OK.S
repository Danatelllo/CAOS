    .global main
end:
    movl %ecx, %eax
    call writei32
    movl %ebx, %eax
    call writei32
    call finish
even:
    addl %eax, %ecx
    jmp for
odd:
    addl %eax, %ebx
    jmp for

main:
    movl $0, %ecx
    movl $0, %ebx
for:
    call readi32
    jc end
    test $1, %eax
    jz even
    jnz odd
    jmp for 
    
