    .global main
end:
    call finish
writing:
    cmp $0, %ebx
    jz end
    decl %ebx
    pop %eax
    call writei32
    jmp writing
main:
    xor %ebx, %ebx
reading:
    call readi32
    jc writing
    push %eax
    incl %ebx
    jmp reading
    
