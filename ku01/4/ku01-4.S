    .text

    .global my.args.forward
my.args.forward:
    push %ebp
    movl %esp, %ebp
    
    push 16(%ebp)
    push 12(%ebp)
    push 8(%ebp)
    push 20(%ebp)
    
    
    call process
    neg %eax

    //addl $12, %esp
    leave
    ret

