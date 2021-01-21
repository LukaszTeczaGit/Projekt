#include <iostream>
#include <windows.h>

using namespace std;

int nr_gry;

TCHAR NPath[MAX_PATH];

void startup()
{
    STARTUPINFO startInfo = { 0 };

    PROCESS_INFORMATION processInfo = { 0 };

    GetCurrentDirectory(MAX_PATH, NPath);

    BOOL bSuccess = CreateProcess(TEXT(".\\kik\\Project1.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startInfo, &processInfo);
    if (bSuccess) {
        cout << "Udalo sie";
    }
    else {
        cout << "Nie udalo sie!";
    }
}

void exitOrGoToMainMenu();

void showMenu() {
    std::cout << "\nWpisz numer gry w ktora chcecie zagrac!\n";
    cout << "1.Kolko i krzyzyk\n2.Snake\n3.Quiz\n4.Pogoda\n";
    cin >> nr_gry;
    if (nr_gry == 1) {
        startup();
        exitOrGoToMainMenu();

    }
    else if (nr_gry == 2) {
        system("snake.exe");
        exitOrGoToMainMenu();
    }
    else if (nr_gry == 3) {
        system("Quiz.exe");
        exitOrGoToMainMenu();
    }
    else if (nr_gry == 4) {
        system("pogoda.exe");
        exitOrGoToMainMenu();
    }
}

void exitOrGoToMainMenu() {
    cout << endl << "Wpisz 'q' aby wyjsc, 'g' aby powrocic do menu glownego" << endl;
    while (true) {
        string quit;
        cout << endl;
        cin >> quit;
        if (quit == "q") {
            exit(1);
        }
        else if (quit == "g") {
            showMenu();
        }
    }
}

int main()
{
    showMenu();
}


