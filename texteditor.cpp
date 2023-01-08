#include <iostream>
#include <string>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

termios original_attributes;

void die(const char *s)
{
    perror(s);
    exit(1);
}

void enableRawMode()
{
    // Save the current terminal attributes
    tcgetattr(0, &original_attributes);

    // Set the terminal to raw mode
    termios raw_attributes = original_attributes;
    // BRKINT : Turns off break condition when SIGINT is sent INPCK: Disables parity checking
    // ISTRIP: Disables stripping of 8th bit ICRNL: Disables Ctrl-M IXON: Disable Ctrl-S and Ctrl-Q
    raw_attributes.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    // OPOST: Turn off output processing
    raw_attributes.c_oflag &= ~(OPOST);
    // CS8: Disables Bitmask
    raw_attributes.c_cflag |= (CS8);
    // IEXTEN: Disable Ctrl-V ISIG: Disable Ctrl-C and Ctrl-Z
    raw_attributes.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    // Adds timeout when there is no input
    raw_attributes.c_cc[VMIN] = 0;
    raw_attributes.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &raw_attributes);
}

void disableRawMode()
{
    // Restore the original terminal attributes
    tcsetattr(0, TCSANOW, &original_attributes);
}

int main()
{
    enableRawMode();
    while (true)
    {
        char c = '\0';
        c = getchar();
        if (c == 'q')
        {
            break;
        }

        if (iscntrl(c))
        {
            printf("%d\r\n", c);
        }
        else
        {
            printf("%d ('%c')\r\n", c, c);
        }
    }
    disableRawMode();
    return 0;
}