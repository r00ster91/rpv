#include "stdio.h"

#include <raylib.h>

#include "main.h"
#include "viridian.h"

Color color(float r, float g, float b, float a) {
    return (Color){r * 255, g * 255, b * 255, a * 255};
}

int main(void) {
    InitWindow(SIZE, SIZE, "RPV");
    SetTargetFPS(60);
    SetExitKey(0);

    struct Viridian viridian = new_viridian();

    Texture tile = LoadTexture("grass.png");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        unsigned x, y;

        for (x = 0; x < (TILES_COUNT * TILES_COUNT) - 1; ++x) {
            for (y = 0; y < (TILES_COUNT * TILES_COUNT) - 1; ++y) {
                DrawTextureEx(
                    tile,
                    (Vector2){x * tile.width * SCALE, y * tile.height * SCALE}, 0, SCALE, WHITE
                );
            }
        }

        draw_viridian(viridian);
        update_viridian(&viridian);

        EndDrawing();
    }

    free_viridian();

    CloseWindow();

    return 0;
}

