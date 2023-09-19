#include "include/vector3.h"

Vector3 vector3_initialize() {
    Vector3 v;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    return v;
}

Vector3 vector3_add(Vector3 v1, Vector3 v2) {
    Vector3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

Vector3 vector3_subtract(Vector3 v1, Vector3 v2) {
    Vector3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

Vector3 vector3_scale(Vector3 v, float scalar) {
    Vector3 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;
}

Vector3 vector3_cross(Vector3 v1, Vector3 v2) {
    Vector3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

float vector3_dot(Vector3 v1, Vector3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float vector3_magnitude(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 vector3_normalize(Vector3 v) {
    float magnitude = vector3_magnitude(v);
    
    if (magnitude != 0.0f) {
        Vector3 result;
        result.x = v.x / magnitude;
        result.y = v.y / magnitude;
        result.z = v.z / magnitude;
        return result;
    } else {
        return vector3_initialize();
    }
}

void vector3_set(Vector3* v, float x, float y, float z) {
    if (v != NULL) {
        v->x = x;
        v->y = y;
        v->z = z;
    }
}

bool vector3_equals(Vector3 v1, Vector3 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

float vector3_distance(Vector3 v1, Vector3 v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

float vector3_angle(Vector3 v1, Vector3 v2) {
    float dotProduct = vector3_dot(v1, v2);
    float magnitude1 = vector3_magnitude(v1);
    float magnitude2 = vector3_magnitude(v2);

    if (magnitude1 > 0.0f && magnitude2 > 0.0f) {
        // Calculate the cosine of the angle
        float cosTheta = dotProduct / (magnitude1 * magnitude2);

        // Clamp the cosine value to the valid range [-1, 1] to avoid numerical issues
        cosTheta = fmaxf(-1.0f, fminf(1.0f, cosTheta));

        // Calculate the angle in radians using the arccosine function
        return acosf(cosTheta);
    } else {
        return 0.0f;
    }
}

Vector3 vector3_direction(Vector3 v_from, Vector3 v_to) {
    Vector3 direction;
    direction.x = v_to.x - v_from.x;
    direction.y = v_to.y - v_from.y;
    direction.z = v_to.z - v_from.z;
    return direction;
}

Vector3 vector3_project(Vector3 v1, Vector3 v_onto) {
    float dotProduct = vector3_dot(v1, v_onto);
    float magnitudeSquared = v_onto.x * v_onto.x + v_onto.y * v_onto.y + v_onto.z * v_onto.z;

    if (magnitudeSquared > 0.0f) {
        // Calculate the projection vector using dot product and normalization
        Vector3 projection;
        float scaleFactor = dotProduct / magnitudeSquared;
        projection.x = v_onto.x * scaleFactor;
        projection.y = v_onto.y * scaleFactor;
        projection.z = v_onto.z * scaleFactor;
        return projection;
    } else {
        return vector3_initialize();
    }
}

Vector3 vector3_reflect(Vector3 v_incident, Vector3 v_normal) {
    // Calculate the dot product between incident vector and normal vector
    float dotProduct = vector3_dot(v_incident, v_normal);

    // Calculate the reflection vector
    Vector3 reflection;
    reflection.x = v_incident.x - 2.0f * dotProduct * v_normal.x;
    reflection.y = v_incident.y - 2.0f * dotProduct * v_normal.y;
    reflection.z = v_incident.z - 2.0f * dotProduct * v_normal.z;

    return reflection;
}

Vector3 vector3_lerp(Vector3 v_start, Vector3 v_end, float t) {
    // Clamp t to the range [0, 1]
    t = fmaxf(0.0f, fminf(1.0f, t));

    // Calculate the interpolated vector
    Vector3 result;
    result.x = v_start.x + (v_end.x - v_start.x) * t;
    result.y = v_start.y + (v_end.y - v_start.y) * t;
    result.z = v_start.z + (v_end.z - v_start.z) * t;
    
    return result;
}