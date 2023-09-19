/**
 * @brief Structure representing a range in an array.
 *
 * The Range struct defines a range within an array. It includes the lower and upper bounds
 * of the range, as well as additional fields for storing the index of the minimum and maximum
 * values within the range, the sum of values, and the product of values.
 */
typedef struct {
    int lower_range;
    int upper_range;
    int min_index;
    int max_index;
    int sum;
    long double prod;
} Range;
