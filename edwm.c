#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

HMODULE edwmDLL;
HHOOK hook;
FARPROC ShellProc;

void ctrl_c(int sig) {
    fprintf(stdout, "Closing Edwm\n");
    if (hook) {
        UnhookWindowsHookEx(hook);
    }

    if (edwmDLL) {
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
        fprintf(stderr, "Hook is null: %p\n", hook);
        FreeLibrary(edwmDLL);
        UnhookWindowsHookEx(hook);
        return 1;
    }
    fprintf(stdout, "Running Edwm -- It tiles all new created windows\n");

    signal(SIGINT, ctrl_c);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    fprintf(stdout, "Closing Edwm\n");

    if (hook) {
        UnhookWindowsHookEx(hook);
    }

    if (edwmDLL) {
        FreeLibrary(edwmDLL);
    }

    return 0;
}