#include <3ds.h>
#include <citro2d.h>

int main() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init();
    C2D_Prepare();

    C2D_Target* top = C2D_GetScreenTarget(GFX_TOP);

    C2D_FontBuf* font = C2D_FontBufNewDefault();
    C2D_Text text;
    C2D_TextParse(&text, font, "Hello, World!");

    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(0,0,0,255));
        C2D_SceneBegin(top);
        C2D_DrawText(&text, C2D_AlignCenter, C2D_ScreenCenter().x, C2D_ScreenCenter().y, 0.0f, 1.0f, 1.0f);
        C3D_FrameEnd(0);
    }

    C2D_FontBufDelete(font);
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}