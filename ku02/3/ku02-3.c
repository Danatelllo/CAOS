int call_func(int eax, int ebx, int ecx, int edx) {
    int answer = 0;
    __asm__("push %%ebp\n\t"
            "call func\n\t"
            "pop %%ebp\n\t"
            : "=S"(answer)
            : "a"(eax), "c"(ecx), "d"(edx), "b"(ebx));
    return answer;
}
