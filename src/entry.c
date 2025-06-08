int fd = 0x114514;
char buffer[256];

int main(void)
{
    const char * msg = "Hello World!";
    for (unsigned int i = 0; true; i++)
    {
        if (msg[i] == '\0') {
            break;
        }

        fd += msg[i];
    }
}
