#include  <3ds.h>
#include <citro2d.h>
int main() {
    gfxInitDefault();
    romfsInit();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C2D_Prepare();
    C2D_SpriteSheet sheet = C2D_SpriteSheetLoad("romfs:/image.t3x");
    if (!sheet) {
        printf("Failed to load sprite sheet\n");
        while (1);
    }
    C2D_Image img = C2D_SpriteSheetGetImage(sheet, 0);
    C2D_Sprite spr;
    C2D_SpriteFromImage(&spr, img);
    C2D_SpriteSetPos(&spr, 100.f, 100.f);

    while (aptMainLoop()) {
        hidScanInput();
        if (hidKeysDown() & KEY_START) {
            break;
        }
        C2D_SceneBegin(top);
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(0,0,0,255));
        C2D_DrawSprite(&spr);
        C3D_FrameEnd(0);
    }
    C2D_SpriteSheetFree(sheet);
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();

    return 0;
}