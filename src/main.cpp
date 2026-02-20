#include <3ds.h>
#include <cstdio>   // for printf
#include <cstdlib>  // for exit, etc.

int main() {
    // Initialize graphics on top/bottom screens
    gfxInitDefault();
    consoleInit(GFX_TOP, nullptr); // console output on top screen

    printf("why is kiki so fat\n");
    // Main loop
    while (aptMainLoop()) {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        // Exit if START is pressed
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;
    }

    gfxExit();
    return 0;
}