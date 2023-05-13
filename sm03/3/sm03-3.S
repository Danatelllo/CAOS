    .text    
    .global main
main:
    push %ebp
    movl %esp, %ebp
    
    push $1f
    push %ebp
    movl %esp, %ebp
    jmp process
1:
    movl %eax, number
    pushl number
    push $printf_instruction
    call printf
    
    addl $6, %esp
    xor %eax, %eax
    leave
    ret
    .section .rodata
printf_instruction: .asciz "%d"
    .data
number: .int 0

