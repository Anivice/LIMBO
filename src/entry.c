__asm__("jmp main");

void write_to_video_memory(char c, unsigned loc)
{
    __asm__ volatile (
        /*   movb %b0,(%1,%2,2)        */
        "movb   %b0,(%1,%2,2)\n\t"
        :
        : "q"(c),                /* operand 0: any low-8-bit reg (al, bl, cl, dl) */
          "r"((void*)0xB8000),     /* operand 1: base pointer in any GP reg */
          "r"(loc)                 /* operand 2: index in any GP reg */
        : "memory"                 /* clobber memory so store isn’t optimized away */
    );
}


[[noreturn]]
int main(void)
{
    const char * msg = "Hello World!";
    unsigned int i = 0;
    void * ptr = write_to_video_memory;
    while (msg[i]) {
        write_to_video_memory(msg[i], i);
        i++;
    }

    while (true);
}


