    .global okay
okay:
    push %ebp
    movl %esp, %ebp
    
    movsd 8(%ebp), %xmm0
    movsd 16(%ebp), %xmm1

    mulsd 8(%ebp), %xmm0
    mulsd 8(%ebp), %xmm0
    mulsd 8(%ebp), %xmm0

    mulsd 16(%ebp), %xmm1
    mulsd 16(%ebp), %xmm1
    mulsd 16(%ebp), %xmm1

    addsd %xmm0, %xmm1

    sqrtsd %xmm1, %xmm0

    movl 24(%ebp), %eax
    movsd %xmm0, (%eax)
     
    leave
    ret 
