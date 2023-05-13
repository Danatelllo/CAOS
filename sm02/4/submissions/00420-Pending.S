    .bss
arr: .skip 8 * 1000

    .text
end:
    call finish
put:
    movl %ebx, arr(, %edx, 8)
    movl %ecx, arr + 4(, %edx, 8)
    incl %edx
    jmp read

emptystack:
    movl $-1, %eax
    call writei32 
    jmp read
ifnull:
    // ebx - ancestor, ecx - weight
    call readi32
    movl %eax, %ebx
    call readi32
    movl %eax, %ecx
    jmp put
ifnotnull:
    // ebx - ancestor, ecx
    call readi32 
    movl arr(, %eax, 8), %ebx
    cmpl $-1, %ebx
    jz emptystack
    
    movl arr + 4(, %eax, 8), %ecx
   // movl arr(,%ebx, 8), %ebx

    movl %ecx, %eax
    call writei32
    
    movl arr + 4(, %ebx, 8), %ecx
    movl arr(, %ebx, 8), %ebx
    jmp put
    .global main
main:
    // counter
    xor %edx, %edx
    // first stat 0, 4)
    movl $-1, arr(, %edx, 4)
    incl %edx
    movl $0, arr(, %edx, 4)
read:
    call readi32
    jc end
    test $1, %eax
    jz ifnull     
    jnz ifnotnull
