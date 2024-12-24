#include "fractal.h"
#include "image.h"
#include <complex.h>

#define MAX_ITER 100

// Функция для рисования множества Жюлиа
void draw_julia(image_p picture, double complex c) {
    pixel_coord width = get_width(picture);
    pixel_coord height = get_height(picture);

    for (pixel_coord y = 0; y < height; y++) {
        for (pixel_coord x = 0; x < width; x++) {
            double complex z = ((double)x / width - 0.5) * 3 + ((double)y / height - 0.5) * 3 * I;
            int iter = 0;

            while (cabs(z) < 2 && iter < MAX_ITER) {
                z = z * z + c;
                iter++;
            }

            pixel_data color = (pixel_data)(iter * 255 / MAX_ITER);
            set_pixel(picture, x, y, color);
        }
    }
}

// Функция для рисования ковра Серпинского
void draw_sierpinski(image_p picture, pixel_coord x, pixel_coord y, pixel_coord size) {
    if (size == 1) {
        set_pixel(picture, x, y, 255);
        return;
    }

    pixel_coord new_size = size / 3;

    for (pixel_coord i = 0; i < 3; i++) {
        for (pixel_coord j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            draw_sierpinski(picture, x + i * new_size, y + j * new_size, new_size);
        }
    }
}