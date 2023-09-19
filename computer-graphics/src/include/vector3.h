#include <stdbool.h>
#include <stddef.h>
#include <math.h>

#ifndef VECTOR3_H
#define VECTOR3_H

/**
 * @brief A struct representing a three-dimensional vector in space.
 *
 * This struct, Vector3, defines a three-dimensional vector with components x, y, and z,
 * typically used to represent positions or directions in 3D space.
 */
typedef struct{
    float x; /** The x-component of the vector. */
    float y; /** The y-component of the vector. */
    float z; /** The z-component of the vector. */
}Vector3;

/**
 * @brief Initialize a Vector3 with all components set to zero.
 *
 * This function creates and returns a Vector3 with all components (x, y, z) set to zero.
 *
 * @return A Vector3 struct with all components initialized to zero.
 */
Vector3 vector3_initialize();

/**
 * @brief Add two Vector3 structs element-wise.
 *
 * This function takes two Vector3 structs, v1 and v2, and returns a new Vector3
 * containing the element-wise sum of their components (x, y, z).
 *
 * @param v1 The first Vector3 to be added.
 * @param v2 The second Vector3 to be added.
 * @return A new Vector3 resulting from the addition of v1 and v2.
 */
Vector3 vector3_add(Vector3 v1, Vector3 v2);

/**
 * @brief Subtract one Vector3 from another element-wise.
 *
 * This function takes two Vector3 structs, v1 and v2, and returns a new Vector3
 * containing the element-wise subtraction of v2 from v1 (v1 - v2).
 *
 * @param v1 The Vector3 from which v2 will be subtracted.
 * @param v2 The Vector3 to be subtracted from v1.
 * @return A new Vector3 resulting from the subtraction of v2 from v1.
 */
Vector3 vector3_subtract(Vector3 v1, Vector3 v2);

/**
 * @brief Scale a Vector3 by a scalar value.
 *
 * This function takes a Vector3 struct, v, and a scalar value, scalar, and returns
 * a new Vector3 with each of its components (x, y, z) multiplied by the scalar.
 *
 * @param v The Vector3 to be scaled.
 * @param scalar The scalar value to multiply each component of v.
 * @return A new Vector3 resulting from the scaling operation.
 */
Vector3 vector3_scale(Vector3 v, float scalar);

/**
 * @brief Calculate the cross product of two Vector3 structs.
 *
 * This function takes two Vector3 structs, v1 and v2, and returns a new Vector3
 * containing the cross product of v1 and v2.
 *
 * @param v1 The first Vector3 operand.
 * @param v2 The second Vector3 operand.
 * @return A new Vector3 resulting from the cross product of v1 and v2.
 */
Vector3 vector3_cross(Vector3 v1, Vector3 v2);

/**
 * @brief Calculate the dot product of two Vector3 structs.
 *
 * This function takes two Vector3 structs, v1 and v2, and returns the dot product
 * of v1 and v2, which is a scalar value.
 *
 * @param v1 The first Vector3 operand.
 * @param v2 The second Vector3 operand.
 * @return The dot product of v1 and v2 as a float.
 */
float vector3_dot(Vector3 v1, Vector3 v2);

/**
 * @brief Calculate the magnitude (length) of a Vector3.
 *
 * This function takes a Vector3 struct, v, and returns the magnitude (length) of v as a float.
 *
 * @param v The Vector3 for which to calculate the magnitude.
 * @return The magnitude (length) of the input Vector3 as a float.
 */
float vector3_magnitude(Vector3 v);

/**
 * @brief Normalize a Vector3.
 *
 * This function takes a Vector3 struct, v, and returns a new Vector3 with the same direction
 * as v but with a magnitude of 1. If the input vector has a magnitude of 0, the result
 * will be a Vector3 with everything set to 0.
 *
 * @param v The Vector3 to be normalized.
 * @return A new Vector3 with the same direction as v and a magnitude of 1.
 */
Vector3 vector3_normalize(Vector3 v);

/**
 * @brief Set the components of a Vector3.
 *
 * This function sets the components (x, y, z) of a Vector3 struct pointed to by v
 * to the specified values (x, y, z).
 *
 * @param v Pointer to the Vector3 to be modified.
 * @param x The new value for the x-component.
 * @param y The new value for the y-component.
 * @param z The new value for the z-component.
 */
void vector3_set(Vector3* v, float x, float y, float z);

/**
 * @brief Compare two Vector3 structs for equality.
 *
 * This function takes two Vector3 structs, v1 and v2, and returns true if they have
 * the same values for all components (x, y, z), indicating that they are equal. Otherwise,
 * it returns false.
 *
 * @param v1 The first Vector3 to be compared.
 * @param v2 The second Vector3 to be compared.
 * @return true if v1 and v2 are equal, false otherwise.
 */
bool vector3_equals(Vector3 v1, Vector3 v2);

/**
 * @brief Calculate the Euclidean distance between two Vector3 structs.
 *
 * This function takes two Vector3 structs, v1 and v2, and calculates the Euclidean
 * distance between them, treating each as a point in 3D space.
 *
 * @param v1 The first Vector3 representing a point in 3D space.
 * @param v2 The second Vector3 representing another point in 3D space.
 * @return The Euclidean distance between v1 and v2 as a float.
 */
float vector3_distance(Vector3 v1, Vector3 v2);

/**
 * @brief Calculate the angle between two Vector3 structs in radians.
 *
 * This function takes two Vector3 structs, v1 and v2, and calculates the angle
 * in radians between them. The result is in the range [0, pi].
 *
 * @param v1 The first Vector3 representing one direction.
 * @param v2 The second Vector3 representing another direction.
 * @return The angle between v1 and v2 in radians.
 */
float vector3_angle(Vector3 v1, Vector3 v2);

/**
 * @brief Calculate the direction vector from one Vector3 to another.
 *
 * This function takes two Vector3 structs, v_from and v_to, and calculates
 * a new Vector3 representing the direction from v_from to v_to. The resulting
 * vector points from v_from to v_to.
 *
 * @param v_from The starting Vector3 representing the initial position.
 * @param v_to The target Vector3 representing the target position.
 * @return A new Vector3 representing the direction from v_from to v_to.
 */
Vector3 vector3_direction(Vector3 v_from, Vector3 v_to);    

/**
 * @brief Project one Vector3 onto another.
 *
 * This function takes two Vector3 structs, v1 and v_onto, and calculates
 * a new Vector3 representing the projection of v1 onto the direction of v_onto.
 * The resulting vector represents the component of v1 that lies in the direction
 * of v_onto.
 *
 * @param v1 The Vector3 to be projected.
 * @param v_onto The Vector3 onto which v1 will be projected.
 * @return A new Vector3 representing the projection of v1 onto v_onto.
 */
Vector3 vector3_project(Vector3 v1, Vector3 v_onto);

/**
 * @brief Reflect a Vector3 off a surface with a given normal vector.
 *
 * This function takes two Vector3 structs, v_incident and v_normal, and calculates
 * the reflection of v_incident off a surface with the given normal vector v_normal.
 * The resulting vector represents the direction of the reflected vector.
 *
 * @param v_incident The incident Vector3 representing the incoming direction.
 * @param v_normal The normal Vector3 representing the surface's normal.
 * @return A new Vector3 representing the reflection of v_incident.
 */
Vector3 vector3_reflect(Vector3 v_incident, Vector3 v_normal);

/**
 * @brief Linearly interpolate between two Vector3 structs.
 *
 * This function takes two Vector3 structs, v_start and v_end, and a parameter t
 * in the range [0, 1] representing the interpolation factor. It returns a new Vector3
 * representing the linear interpolation between v_start and v_end based on the value of t.
 * If t is 0, the result will be v_start; if t is 1, the result will be v_end.
 *
 * @param v_start The starting Vector3.
 * @param v_end The ending Vector3.
 * @param t The interpolation factor in the range [0, 1].
 * @return A new Vector3 resulting from the linear interpolation.
 */
Vector3 vector3_lerp(Vector3 v_start, Vector3 v_end, float t);

#endif