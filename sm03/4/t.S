    .global main
main:
    pushl %ebp
    movl %esp, %ebp

    movl $5, %ebx #размера массива
    pushl %ebx
    pushl $arr
    call sort_by_abs
    xor %edi, %edi
    movl $arr, %esi
    
loop:
    movswl (%esi, %edi, 2), %eax
    call writei32
    incl %edi
    cmpl %ebx, %edi
    jz end
    jnz loop

end:
    mov %ebp, %esp
    pop %ebp
    ret

    .data
arr: .word -32768, 1, 2, 3, 4 #массив
