        .att_syntax     noprefix
        .text
        .align  16
        .global invoke
// 8(ebp)  - ebx - arr
// 12(ebp) - esi - size
// 16(ebp) - edi - pivot
invoke:
        push    ebp
        mov     esp, ebp
        push    ebx
        push    esi
        push    edi
        sub     $12, esp

        mov     8(ebp), ebx
        mov     12(ebp), esi
        mov     16(ebp), edi
        call    partition
        mov     edx, eax

        cmp     ebx, 8(ebp)
        jnz     fail
        cmp     esi, 12(ebp)
        jnz     fail
        cmp     edi, 16(ebp)
        jnz     fail

        add     $12, esp
        pop     edi
        pop     esi
        pop     ebx
        pop     ebp
        ret

fail:
        push    $stderr
        push    $msg
        call    fputs
        add     $8, esp
        call    abort

        .section        .rodata
msg:    .asciz  "subroutine 'partition' messed up ebx, esi, or edi\n"





final:
    pop %ebp
    pop %ecx
    pop %eax
    ret

Do:
    movl %eax, %edx

    .global partition
partition:
    push %eax
    push %ecx
    push %ebp    

    xor %eax, %eax
    movl %esi, %ecx
    decl %ecx
Floop:
    cmp %eax, %ecx
    jle final

Sloop:
    cmp %eax, %esi
    jl Go

    cmpw (%ebx, %eax, 2), %di
    jle Go 

    incl %eax
    jmp Sloop

Go:
    cmp $0, %ecx
    jl Last

    cmpw (%ebx, %ecx, 2), %di
    jge Last

    decl %ecx
    jmp Go

Last:
    cmpl %eax, %ecx
    jle final

    movw (%ebx, %ecx, 2), %bp
    xchgw %bp, (%ebx, %eax, 2)

    cmpw (%ebx, %eax, 2), %di
    jz Do

    jmp Floop



.global main

main:
    call invoke
