    .text    
    .global print_tb
is_foo:
    push $f
    call puts
    // addl $3, %ebp
    addl $4, %esp 
    jmp next_step
is_bar:
    push $b
    call puts
    // addl $3, %ebp
    addl $4, %esp
    jmp next_step

next2:
    incl %edx
    jmp continue_min

swap:
    movl arr(, %edx, 4), %eax

next1:
    incl %edx
    jmp for
min:
    xor %edx, %edx

continue_min:
    cmpl $0, arr(, %edx, 4)
    jg next2
    movl arr(, %edx, 4), %eax
for:
    cmpl $3, %edx
    je got_min

    cmpl $0, arr(, %edx, 4)
    jg next1

    cmpl %eax, arr(, %edx, 4)
    jg swap
step:    
    incl %edx 
    jmp for 
    

    

print_tb:
    push %ebp
    movl %esp, %ebp  
    push $p
    call puts
    addl $4, %esp
body:
    movl %ebp, %eax
    addl $4, %eax    
    movl (%eax), %eax  // adress some function   // adress some function 

    movl $foo, %ecx
    movl $bar, %edx

    subl %eax, %ecx
    subl %eax, %edx
     
    movl %ecx, arr
    movl %edx, arr + 4
       
    movl $main, %ecx
    subl %eax, %ecx
    movl %ecx, arr + 8

    
    movl arr + 4, %ecx
    movl arr + 8, %edx
    movl arr, %eax

    jmp min
got_min:
    cmpl %eax, arr
    je is_foo
    
    cmpl %eax, arr + 4
    je is_bar
    
    push $m
    call puts
    addl $4, %esp
    xor %eax, %eax 
    leave 
    ret

next_step:
    movl (%ebp), %ebp
    jmp body

    .data
pointer: .int 0
    .bss
arr: .skip 4 * 3    

    .section .rodata
f:  .asciz "foo"
b:  .asciz "bar"
m:  .asciz "main"
p:  .asciz "print_tb"
