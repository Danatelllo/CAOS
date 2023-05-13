    .global main
    .text
overflow:
    push $ov_flow
    push $printf_string
    call printf
    addl $12, %esp
    jmp end

main:
    pushl %ebp
    movl %esp, %ebp

do:
    pushl $number
    pushl $scanf_parametrs
    call scanf

    addl $8, %esp
    
    movl number, %ecx
    addl %ecx, sum
    jo overflow
    movl $0, number    
    cmp $1, %eax
    je do
    
    pushl sum
    pushl $printf_parametrs    
    call printf
    
    addl $8, %esp

end:
    xor %eax, %eax
    leave
    ret
    
    .data
number: .int 0  
sum: .int 0
    .section .rodata
scanf_parametrs: .asciz "%d"  
printf_parametrs: .asciz "%d\n"
printf_string: .asciz "%s\n"
ov_flow: .asciz "Overflow"
