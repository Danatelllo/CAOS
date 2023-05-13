

    .text
    .global grater
grater:
    push %ebp
    movl %esp, %ebp
   
    movl 8(%ebp), %ecx
    xor %eax, %eax
    movswl (%ecx), %eax
   
    cmpl $0, %eax
    jl mul1
    
next1:
    
    movl 12(%ebp), %edx
    xor %ecx, %ecx
    movswl (%edx), %ecx

        
    cmpl $0, %ecx
    jl mul2
    
next2:
    
    cmpl %ecx, %eax
    je answer0
    jl answerminus1
    jg answer1
answer0:
    movl $0, %eax
    jmp end    
answerminus1:
    movl $-1, %eax
    jmp end
answer1:
    movl $1, %eax
    jmp end
end:    
    leave
    ret
mul1:
    imul $-1, %eax
    jmp next1

mul2:
    imul $-1, %ecx
    jmp next2



    
    .global sort_by_abs
sort_by_abs:
    push %ebp
    movl %esp, %ebp

    movl $2, %eax
        
    push $grater
    push %eax
    push 12(%ebp)
    push 8(%ebp)
    
 
    //push 8(%ebp)
    //push 12(%ebp)
    //push %eax
    //push %edx
    
    call qsort
    
    addl $16, %esp

    leave
    xor %eax, %eax
    ret
