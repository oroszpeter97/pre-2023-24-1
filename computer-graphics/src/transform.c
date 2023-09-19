#include "include/transform.h"

Transform transform_initialize() {
    Transform transform;
    transform.position = vector3_initialize();
    transform.rotation = vector3_initialize();
    vector3_set(&transform.scale, 1.0f, 1.0f, 1.0f);
    return transform;
}