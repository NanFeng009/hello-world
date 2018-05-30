/*C program to convert String into Hexadecimal.*/
 
#include <stdio.h>
#include <string.h>
/* for implement print function */
static void printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
}

static void _print_hex(uint32_t src_len, uint8_t* src_str)
{
    int i, j;
    int dst_len = src_len * 2 + 2;
    unsigned char *dst_str = new unsigned char[dst_len];
    memset(dst_str, 0, dst_len);
    for(i = 0, j = 0; i < src_len; i++, j+=2)
    {
        sprintf((char*)(dst_str+j), "%02X", src_str[i]);
    }
    dst_str[j++] = '\0';
    dst_str[j] = '\n';
    printf("The length is %d\n, and date is \n%s\n", src_len, dst_str);
    delete[] dst_str;
}

int main()
{
    unsigned char str[100] = "Hwllo world";
    
    _print_hex(100, str);
    return 0;
}
