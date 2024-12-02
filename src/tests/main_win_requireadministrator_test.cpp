//
// repo:            FocusT p01 monitor
// file:            main_windows_manifestfile_test.cpp
// path:			src/tests/windows_manifestfile_test/main_windows_manifestfile_test.cpp
// created on:		2024 Dec 02
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <iostream>
#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#define     MyGetCh _getch
#else
#define     MyGetCh getchar
#endif

int main(int a_argc, char* a_argv[]) {

    static_cast<void>(a_argc);
    static_cast<void>(a_argv);

    std::cout << "This application requires administrative privileges." << std::endl;

    fprintf(stdout,"Press any key to exit!");
    fflush(stdout);
    MyGetCh();

    return 0;
}
