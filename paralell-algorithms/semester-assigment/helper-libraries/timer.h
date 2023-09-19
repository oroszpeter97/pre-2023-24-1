#ifndef TIMER_H_
#define TIMER_H_

/**
 * @file
 * @brief Timer functionality for measuring elapsed time.
 */

/**
 * @brief Starts the timer.
 */
void start_clock();

/**
 * @brief Stops the timer.
 */
void stop_clock();

/**
 * @brief Gets the elapsed time of the timer.
 *
 * @return The elapsed time in seconds.
 *
 * This function calculates and returns the elapsed time between start and stop of the timer.
 */
double get_elapsed_time();

#endif /* TIMER_H_ */
