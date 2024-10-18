#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

void showHelp() {
    printf("\nUsage:\n\tcbt text\n");
}

void copyText(const char *text) {
    if (OpenClipboard(HWND_DESKTOP)) {
        size_t size = strlen(text) + 1;
        auto block = GlobalAlloc(GMEM_MOVEABLE, size);
        auto blockPtr = GlobalLock(block);
        memcpy(blockPtr, text, size);
        GlobalUnlock(block);
        
        EmptyClipboard();

        if (SetClipboardData(CF_TEXT, block))
            printf("Text '%s' has been copied\n", text);
        else
            printf("Unable to copy text, error %d\n", GetLastError());

        GlobalFree(block);
        CloseClipboard();
    } else {
        printf("Unable to open the clipboard.\n");
    }
}

int main(int argCount, char *args[]) {
    printf("Clipboard command line tool\nCopytight (c) 2024 by Evgeny Tukh\n");

    if (argCount > 1) {
        for (size_t i = 1; i < argCount; ++i) {
            auto arg = args[i];

            if (arg[0] == '/' || arg[0] == '-') {
                switch (tolower(arg[1])) {
                    case 'h':
                        showHelp();
                        return 0;
                    default:
                        printf("Unknown argument %s\n", arg);
                        return 1;
                }
            } else {
                copyText(arg);
            }
        }
    } else {
        printf("At least you should present text to copy.\n");
    }

    return 0;
}
