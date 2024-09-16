// Smashscii.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE ||
        hStdout == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
            MB_OK);
        return 1;
    }


    if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
    {
        MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"),
            TEXT("Console Error"), MB_OK);
        return 1;
    }

    std::cout << csbiInfo.dwSize.X << std::endl;
}

//  [ O ]
//  [-|-]
//  [/ \]
