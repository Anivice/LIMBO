[[noreturn]]
int main(void)
{
    const char * msg = "Hello World!";
    unsigned int i = 0;
    unsigned int j = 0;
    while (msg[i]) {
        j += msg[i++];
    }

    while (true);
}
