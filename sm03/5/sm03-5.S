    .bss
arr1: .skip 128 * 4
arr2: .skip 128 * 4

    .section .rodata
ok: .asciz "YES"
no: .asciz "NO"

    .text
check_is_big:
    cmpl $65, %eax
    jl continue
    cmpl $90, %eax
    jg continue
    
    addl $32, %eax
    jmp continue

fill_arr1:
    call getchar
    cmpl $10, %eax
    je nextreading
    cmpl $32, %eax
    je fill_arr1
    
    jmp check_is_big
continue:
    addl $1, arr1(,%eax, 4)
    jmp fill_arr1


check_is_big1:
    cmpl $65, %eax
    jl continue1
    cmpl $90, %eax
    jg continue1
    
    addl $32, %eax
    jmp continue1

fill_arr2:
    call getchar
    cmpl $10, %eax
    je nextreading2
    cmpl $32, %eax
    je fill_arr2
    
    jmp check_is_big1
continue1:
    addl $1, arr2(, %eax, 4)
    jmp fill_arr2

    
    
    .text
    .global main
main:
    push %ebp
    movl %esp, %ebp
    
    jmp fill_arr1    
    
nextreading:

    jmp fill_arr2
        
nextreading2:
    xor %edx, %edx
loop:
    movl arr1(, %edx, 4), %eax
    movl arr2(, %edx, 4), %ecx
    cmpl %eax, %ecx
    jne badanswer
    cmpl $128, %edx
    jg end
    incl %edx
    jmp loop        
end:  
    push $ok
    call puts  
    xor %eax, %eax
    leave 
    ret

badanswer:
    push $no
    call puts  
    leave
    xor %eax, %eax 
    ret

