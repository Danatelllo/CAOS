    .global call_process
call_process:
    jmp process+3    




    .global process
process:
    push %ebp
    mov %esp, %ebp
    push %ebp
    mov %esp, %ebp
    mov $4, %eax
    mov %ebp, %esp
    pop %ebp
    ret

    .global main
main:
    push %ebp
    movl %esp, %ebp
    
    call call_process

    leave
