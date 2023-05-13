.data
buf: .int 0x3f800000, 0xbf800000, 0x3f800000, 0xbf800000

.text
    .global product

load_answer:
    jmp get_sum_of_buf
continue_fill_answer:
    addss %xmm4, %xmm3
    movl 20(%ebp), %eax
    movss %xmm3, (%eax)
    leave
    ret

get_sum_of_buf:
    haddps %xmm5, %xmm3
    haddps %xmm5, %xmm3
    jmp continue_fill_answer
check_n:
    cmpl $3, 8(%ebp)
    je n_is_three

    cmpl $2, 8(%ebp)
    je n_is_two

    cmpl $1, 8(%ebp)
    je n_is_one

    cmpl $0, 8(%ebp)
    je n_is_zero

    jmp loop

product:
    push %ebp
    movl %esp, %ebp
    
    xor %eax, %eax
    xor %edx, %edx
    xor %ecx, %ecx    

    movups buf, %xmm2 // buf
    vxorps %xmm3, %xmm3, %xmm3  // answer
    vxorps %xmm4, %xmm4, %xmm4  // almost_answer
    vxorps %xmm1, %xmm1, %xmm1
    vxorps %xmm0, %xmm0, %xmm0
    vxorps %xmm5, %xmm5, %xmm5    


    movl 12(%ebp), %eax // x
    movl 16(%ebp), %ecx // y

    jmp check_n
    
loop:  
    movups (%eax), %xmm0
    movups (%ecx), %xmm1
    
    mulps %xmm1, %xmm0
    mulps %xmm2, %xmm0
    addps %xmm0, %xmm3    
    
    addl $16, %eax
    addl $16, %ecx
    
    subl $4, 8(%ebp)

    jmp check_n

n_is_three:
    sall $2, %edx
    movss (%eax), %xmm0
    movss (%ecx), %xmm1
    mulss %xmm1, %xmm0
    addss %xmm0, %xmm4

    addl $4, %eax
    addl $4, %ecx

    movss (%eax), %xmm0
    movss (%ecx), %xmm1
    mulss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    subss %xmm0, %xmm4

    addl $4, %eax
    addl $4, %ecx    
    
    movss (%eax), %xmm0
    movss (%ecx), %xmm1
    mulss %xmm1, %xmm0
    addss %xmm0, %xmm4

    jmp load_answer

n_is_two:
    movss (%eax), %xmm0
    movss (%ecx), %xmm1
    mulss %xmm1, %xmm0
    addss %xmm0, %xmm4

    addl $4, %eax
    addl $4, %ecx

    movss (%eax), %xmm0
    movss (%ecx), %xmm1

    mulss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    subss %xmm0, %xmm4

    jmp load_answer

n_is_one:
    movss (%eax), %xmm0
    movss (%ecx), %xmm1

    mulss %xmm1, %xmm0
    addss %xmm0, %xmm4
    jmp load_answer
n_is_zero:
    jmp load_answer
