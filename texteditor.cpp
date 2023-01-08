#include <iostream>
#include <string>
#include <termios.h>
using namespace std;

int main()
{
    while (true)
    {
        // Save the current terminal attributes
        termios old_attributes;
        tcgetattr(0, &old_attributes);

        // Set the terminal to raw mode
        termios raw_attributes = old_attributes;
        raw_attributes.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(0, TCSANOW, &raw_attributes);

        // Read a character from the terminal
        char c = getchar();

        // Restore the original terminal attributes
        tcsetattr(0, TCSANOW, &old_attributes);

        if (c == 'q')
        {
            break;
        }
        cout << c;
    }

    return 0;
}