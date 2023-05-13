    .global A, B, R
.data
A: .int 0
B: .int 0       
R: .int 0
.text
    .global process
process:
    push %ebp
    movl %esp, %ebp    


    movl A, %eax
    movl B, %edx
    
    sarl $4, %edx
    jo finish
    
    subl %edx, %eax
    jo finish

    addl A, %eax
    jo finish

    addl A, %eax
    jo finish
    
    movl %eax, R


finish:    
    leave
    ret
