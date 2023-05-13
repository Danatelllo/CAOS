.global A, B, R
.data
A: .int 0
B: .int 0       
R: .int 0
.text
    .global process
plus:
    addl %edx, %eax 
    jmp next
process:
    xor %eax, %eax
    movl B, %edx
    movl $1, %ecx
do:
    test A, %ecx
    jnz plus
next:
    shll %ecx
    sall %edx
    jnz do
    movl %eax, R
    ret        
