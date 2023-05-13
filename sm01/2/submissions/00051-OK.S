    .global main
main:
    call readi32
    movl %eax, %ecx
    call readi32
    sall $1, %eax
    subl %eax, %ecx
    call readi32
    movl %eax, %ebx
    sall $4, %eax
    addl %ebx, %eax
    addl %eax, %ecx
    call readi32
    call writei32
    movl %ecx, %eax
    call writei32
    call finish

