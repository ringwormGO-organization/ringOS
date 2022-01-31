#include <uefi.h>

int main (int argc, char** argv)
{
    ST->ConOut->SetAttribute(ST->ConOut, EFI_BLUE);
    printf("Welcome to ringOS POSIX!! \n");
    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);

    (void)argc;
    (void)argv;
    FILE *f;
    char *buff;
    long int size;

    if((f = fopen("file.txt", "r"))) 
    {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        printf("File size: %d bytes\n\n", size);
        buff = malloc(size + 1);
        if(!buff) 
        {
            fprintf(stderr, "unable to allocate memory\n");
            return 1;
        }
        fread(buff, size, 1, f);
        buff[size] = 0;
        fclose(f);
        printf("File contents:\n%s\n", buff);
        free(buff);
    } 
    else
        fprintf(stderr, "Unable to open file\n");


    while(1);
    return 0;
}