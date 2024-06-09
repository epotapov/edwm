#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

HMODULE edwmDLL;
HHOOK hook;
FARPROC ShellProc;

void ctrl_c(int sig) {
    if (hook != NULL) {
        UnhookWindowsHookEx(hook);
        FreeLibrary(edwmDLL);
    }
    exit(0);
}


int main() {
    edwmDLL = LoadLibraryW(L"edwmDLL");

    if (edwmDLL == NULL) {
        fprintf(stderr, "DLL failed to load: %d\n", GetLastError());
        return 1;
    }

    ShellProc = GetProcAddress(edwmDLL, "ShellProc");

    if (ShellProc == NULL) {
        fprintf(stderr, "Could not get address of ShellProc: %d\n", GetLastError());
        FreeLibrary(edwmDLL);
        return 1;
    }

    hook = SetWindowsHookExW(WH_SHELL, (HOOKPROC)ShellProc, edwmDLL, 0);

    if (hook == NULL) {
        fprintf(stderr, "Hook is null: %p", hook);
        FreeLibrary(edwmDLL);
        UnhookWindowsHookEx(hook);
        return 1;
    }
    printf("%d\n", hook);

    signal(SIGINT, ctrl_c);
    while (1) {}
    return 0;
}