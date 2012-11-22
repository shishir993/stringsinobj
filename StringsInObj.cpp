// StringsInObj.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>

bool fIsPrintable(char ch);

int main(int argc, char* argv[])
{
    int fd = -1;
    int iRetVal = 0;

    int nBytes = 0;

    // byte read from the file
    char ch = 0;

    if(argc != 2)
    {
        printf("main(): usage: %s <PathToObjectFile>\n", argv[0]);
        return 1;
    }

	#ifndef _DEBUG
	printf("Shishir's Garage project::StringsInObj : Output printable characters from input file.\
				\nCoder: Shishir Prasad {shishir89@gmail.com} : www.shishirprasad.net\
				\nCopyright: None but don't forget to include my name as a reference in your code/webpage. :)\n\n");
	#endif

    // open the file in read binary mode
    if( (fd = _open(argv[1], _O_RDONLY|_O_BINARY)) == -1 )
    {   
        printf("main(): open() error %d\n", errno);
        return 1;
    }

	printf("** Strings in %s **\n", argv[1]);

    // read the file contents byte by byte
    while( (iRetVal = _read(fd, &ch, 1)) > 0 )
    {
        ++nBytes;

        if( fIsPrintable(ch) )
        {
            printf("%08x: ", nBytes-1);
            printf("%c", ch);

            // print further printable characters in the same line
            // until a non-printable character is encountered
            while( (iRetVal = _read(fd, &ch, 1)) > 0 )
            {
                ++nBytes;

                if( fIsPrintable(ch) )
                    printf("%c", ch);
                else
                    break;
            }
            
            // insert a new line after printing 
            // consecutive printable characters
            printf("\n");

            // check if we have reached EOF/encountered an error
            if(iRetVal <= 0)
                break;

        }// if printable
    
    }// while read() > 0

    if(iRetVal == -1)
        printf("main(): read() error %d\n", errno);

    // close the file
    _close(fd);

    printf("\n\nBytes read: %d\n", nBytes);

	return 0;
}

bool fIsPrintable(char ch)
{
    // passing a negative value to
    // is*() functions causes an assertion to trigger
    if( (ch > 0) && 
        (isalpha(ch) || ispunct(ch) || isdigit(ch) || ch == ' '
		 || ch == '\n' || ch == '\r') )
    {
        return true;
    }

    return false;
}
