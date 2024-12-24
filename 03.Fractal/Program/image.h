#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <complex.h>

/**
 * @brief One pixel data in-place 
 */
typedef uint8_t pixel_data;

/**
 * @brief Coordinate of a pixel and dimension of an image
 */
typedef unsigned int pixel_coord;

struct image;

/**
 * @brief Image for application
 */
typedef struct image image_t, *image_p;

/**
 * @brief Returns the width of the image
 *
 * @param picture Image
 * @returns Image width
 */
pixel_coord get_width(image_p picture);

/**
 * @brief Returns the height of the image
 *
 * @param picture Image
 * @returns Image height
 */
pixel_coord get_height(image_p picture);

/**
 * @brief Create image of given width and height
 *
 * @param width,height Dimensions of an image
 * @returns an image
 */
image_p create_image(pixel_coord width, pixel_coord height);

void clear_image(image_p picture);

void free_image(image_p picture);

/**
 * @brief Saves the image in PGM format
 *
 * @param picture Image
 * @param filename Name for the new file
 * @returns Execution code: 0 in case of success, -1 in case of error
 */
int save_pgm(image_p picture, const char *filename);

/**
 * @brief Saves the image in PNG format
 *
 * @param picture Image
 * @param filename Name for the new file
 * @returns Execution code: 0 in case of success, -1 in case of error
 */
int save_png(image_p picture, const char *filename);

/**
 * @brief Set the pixel of an image to given color
 *
 * @param picture Image
 * @param x,y Pixel coordinates
 * @param color Color value
 */
void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data color);

/**
 * @brief Get the pixel of an image
 *
 * @param picture Image
 * @param x,y Pixel coordinates
 * @returns pixel Color value
 */
pixel_data get_pixel(image_p picture, pixel_coord x, pixel_coord y);

#endif // IMAGE_H_