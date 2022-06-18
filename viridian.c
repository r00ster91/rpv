#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "raylib.h"

#include "main.h"
#include "helpers.h"
#include "viridian.h"

/* Returns 0 if any of the textures are invalid. */
static _Bool viridian_textures_valid(const struct ViridianTextures textures) {
    if (!textures.up.id) return 0;
    if (!textures.down.id) return 0;
    if (!textures.left.id) return 0;
    if (!textures.right.id) return 0;
    return 1;
}

static void free_viridian_textures(const struct ViridianTextures textures) {
    UnloadTexture(textures.up);
    UnloadTexture(textures.down);
    UnloadTexture(textures.left);
    UnloadTexture(textures.right);
}

static struct ViridianTextures textures_standing;
static struct ViridianTextures textures_walking;

static Texture get_current_texture(const struct Viridian viridian) {
    switch (viridian.state) {
        case VIRIDIAN_STATE_STANDING:
            switch (viridian.dir) {
                case VIRIDIAN_DIR_UP: return textures_standing.up;
                case VIRIDIAN_DIR_DOWN: return textures_standing.down;
                case VIRIDIAN_DIR_LEFT: return textures_standing.left;
                case VIRIDIAN_DIR_RIGHT: return textures_standing.right;
            }
            unreachable();
        case VIRIDIAN_STATE_WALKING:
            switch (viridian.dir) {
                case VIRIDIAN_DIR_UP: return textures_walking.up;
                case VIRIDIAN_DIR_DOWN: return textures_walking.down;
                case VIRIDIAN_DIR_LEFT: return textures_walking.left;
                case VIRIDIAN_DIR_RIGHT: return textures_walking.right;
            }
            unreachable();
    }
    unreachable();
}

struct Viridian new_viridian() {
    textures_standing.up = LoadTexture("viridian/standing/up.png");
    textures_standing.down = LoadTexture("viridian/standing/down.png");
    textures_standing.left = LoadTexture("viridian/standing/left.png");
    textures_standing.right = LoadTexture("viridian/standing/right.png");
    if (!viridian_textures_valid(textures_standing))
        panic("invalid texture");

    textures_walking.up = LoadTexture("viridian/walking/up.png");
    textures_walking.down = LoadTexture("viridian/walking/down.png");
    textures_walking.left = LoadTexture("viridian/walking/left.png");
    textures_walking.right = LoadTexture("viridian/walking/right.png");
    if (!viridian_textures_valid(textures_walking))
        panic("invalid texture");

    struct Viridian viridian = {
        .dir = VIRIDIAN_DIR_DOWN,
        .state = VIRIDIAN_STATE_STANDING,
    };
    viridian.x = SIZE / 2 - (get_current_texture(viridian).width * SCALE) / 2;
    viridian.y = SIZE / 2 - (get_current_texture(viridian).height * SCALE) / 2;
    return viridian;
}

void free_viridian() {
    free_viridian_textures(textures_standing);
    free_viridian_textures(textures_walking);
}

void draw_viridian(const struct Viridian viridian) {
    static const unsigned center = SIZE / 2;

    struct Vector vec = { 0, 0 };
    if (viridian.x > center)
        vec.x += 1;
    if (viridian.x < center)
        vec.x -= 1;
    if (viridian.y > center)
        vec.y += 1;
    if (viridian.y < center)
        vec.y -= 1;

    /* draw shadow */
    DrawTextureEx(
        get_current_texture(viridian),
        (Vector2){
            viridian.x + vec.x * VIRIDIAN_SHADOW_SIZE,
            viridian.y + vec.y * VIRIDIAN_SHADOW_SIZE,
        }, 0, SCALE, color(0, 0, 0, 0.5)
    );

    DrawTextureEx(
        get_current_texture(viridian),
        (Vector2){viridian.x, viridian.y}, 0, SCALE, WHITE
    );
}

/* Returns 1 if there was any movement-related input. */
static _Bool handle_movement_input(struct Viridian *viridian) {
    struct Vector vec = { 0, 0 };
    if (IsKeyDown('W')) {
        viridian->dir = VIRIDIAN_DIR_UP;
        vec.y -= 1;
    }
    if (IsKeyDown('S')) {
        viridian->dir = VIRIDIAN_DIR_DOWN;
        vec.y += 1;
    }
    if (IsKeyDown('A')) {
        viridian->dir = VIRIDIAN_DIR_LEFT;
        vec.x -= 1;
    }
    if (IsKeyDown('D')) {
        viridian->dir = VIRIDIAN_DIR_RIGHT;
        vec.x += 1;
    }
    viridian->running = IsKeyDown(KEY_LEFT_SHIFT);

    float delta = GetFrameTime();
    const float speed = (viridian->running ? VIRIDIAN_SPEED * 2 : VIRIDIAN_SPEED) * delta;
    viridian->x += vec.x * speed;
    viridian->y += vec.y * speed;

    return (vec.x == 0 && vec.y == 0) ? 0 : 1;
}

void update_viridian(struct Viridian *viridian) {
    _Bool movement = handle_movement_input(viridian);

    if (movement) {
        static unsigned time = 0;
        // This should rely on delta time
        time += 1;
        if (time % (viridian->running ? 4 : 8) == 0) {
            switch (viridian->state) {
                case VIRIDIAN_STATE_STANDING:
                    viridian->state = VIRIDIAN_STATE_WALKING;
                    break;
                case VIRIDIAN_STATE_WALKING:
                    viridian->state = VIRIDIAN_STATE_STANDING;
                    break;
            }
        }
    } else {
        viridian->state = VIRIDIAN_STATE_STANDING;
    }
}
