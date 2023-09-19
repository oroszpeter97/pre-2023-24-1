#include "vector3.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

/**
 * @brief A structure representing a 3D transformation.
 *
 * This `Transform` struct defines a 3D transformation with properties including
 * position, rotation, and scale, typically used to represent transformations of
 * objects in 3D space.
 *
 * @note To use this struct, you can include "vector3.h" to access the Vector3 type.
 */
typedef struct{
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
}Transform;

/**
 * @brief Initialize a Transform struct with default values.
 *
 * This function initializes a `Transform` struct with default values:
 * - Position is set to (0, 0, 0).
 * - Rotation is set to (0, 0, 0).
 * - Scale is set to (1, 1, 1).
 *
 * @return A new `Transform` struct with default values.
 */
Transform transform_initialize();

#endif