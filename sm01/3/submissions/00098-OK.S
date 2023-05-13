     .global main
end:
    call finish
main:
    call readi32
    subl $0, %eax
    jl end
loop:
    call writei32
    subl $1, %eax
    jge loop
    call finish
