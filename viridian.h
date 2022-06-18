#ifndef VIRIDIAN_H
#define VIRIDIAN_H

struct ViridianTextures {
    Texture up;
    Texture down;
    Texture left;
    Texture right;
};

#define VIRIDIAN_SHADOW_SIZE 4
#define VIRIDIAN_SPEED       200

enum ViridianDir {
    VIRIDIAN_DIR_UP,
    VIRIDIAN_DIR_DOWN,
    VIRIDIAN_DIR_LEFT,
    VIRIDIAN_DIR_RIGHT,
};

enum ViridianState {
    VIRIDIAN_STATE_STANDING,
    VIRIDIAN_STATE_WALKING,
};

struct Viridian {
    float x;
    float y;
    enum ViridianDir dir;
    enum ViridianState state;
    _Bool running;
};

struct Viridian new_viridian();
void free_viridian();
void draw_viridian(const struct Viridian viridian);
void update_viridian(struct Viridian *viridian);

#endif /* VIRIDIAN_H */
