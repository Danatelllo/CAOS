max_int:
    movl $2147483647, %eax
    call writei32
    call finish
not_just:
    movl $-2147483648, %eax
    call writei32
    call finish

just_number:
    cmpl $0, %eax
    jg not_just
    call writei32
    call finish
m32:
    cmpl $0, %eax
    jl max_int
    call writei32
    call finish
mneg64:
    cmpl $-1, %edx
    je just_number
    movl $-2147483648, %eax
    call writei32
    call finish
    
mpos64:
    movl $2147483647, %eax
    call writei32
    call finish

    .global main
main:
    call readi64
    cmpl $0, %edx
    je m32
    cmpl $0, %edx
    jl mneg64
    
    jmp mpos64
