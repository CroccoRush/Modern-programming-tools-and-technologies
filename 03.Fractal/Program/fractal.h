#ifndef _FRACTAL_H_
#define _FRACTAL_H_

#include "image.h"

/**
 * @brief Draws empty fractal, assuming image is clean
 *
 * @param picture Image
 */
void empty_fractal(image_p picture);

/**
 * @brief Draws Julia set
 *
 * @param picture Image
 * @param c Complex parameter for Julia set
 */
void draw_julia(image_p picture, double complex c);

/**
 * @brief Draws Sierpinski carpet
 *
 * @param picture Image
 * @param x Start x coordinate
 * @param y Start y coordinate
 * @param size Size of the carpet
 */
void draw_sierpinski(image_p picture, pixel_coord x, pixel_coord y, pixel_coord size);

#endif // _FRACTAL_H_