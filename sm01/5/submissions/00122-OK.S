    .global main
end:
    movl %ecx, %eax
    call writei32
    call finish
increment:
    addl $1, %ecx
    jmp continue
main:
    movl $0, %ecx
    movl $1, %ebx
    call readi32
loop:
    test %ebx, %eax
    jnz increment
continue:
    shll $1, %ebx
    subl $0, %ebx
    jz end
    jmp loop
    
