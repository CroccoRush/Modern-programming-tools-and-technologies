#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <png.h>
#include "image.h"

// Структура для хранения изображения
struct image {
    pixel_coord width, height;
    pixel_data *data;
};

pixel_coord get_width(image_p picture) {
    return picture->width;
}

pixel_coord get_height(image_p picture) {
    return picture->height;
}

// Создание изображения
image_p create_image(pixel_coord width, pixel_coord height) {
    image_t *v = malloc(sizeof(image_t));
    v->width = width;
    v->height = height;
    v->data = malloc(sizeof(pixel_data) * width * height);
    return v;
}

// Очистка изображения
void clear_image(image_p picture) {
    memset(picture->data, 0, sizeof(pixel_data) * picture->width * picture->height);
}

// Установка пикселя
void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data color) {
    assert(x >= 0 && y >= 0 && x < picture->width && y < picture->height);
    picture->data[picture->width * y + x] = color;
}

// Получение пикселя
pixel_data get_pixel(image_p picture, pixel_coord x, pixel_coord y) {
    assert(x >= 0 && y >= 0 && x < picture->width && y < picture->height);
    return picture->data[picture->width * y + x];
}

// Сохранение изображения в формате PGM
int save_pgm(image_p picture, const char *filename) {
    FILE *to = fopen(filename, "w");
    if (!to) return -1;

    fprintf(to, "P2\n%u %u\n255\n", picture->width, picture->height);

    pixel_data *p = picture->data;
    for (pixel_coord y = 0; y < picture->height; y++) {
        for (pixel_coord x = 0; x < picture->width; x++) {
            fprintf(to, "%u%c", *(p++), x == picture->width - 1 ? '\n' : ' ');
        }
    }

    fclose(to);
    return 0;
}

// Функция для сохранения изображения в формате PNG
int save_png(image_p picture, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        return -1;  // Ошибка открытия файла
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        return -1;  // Ошибка создания структуры
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, NULL);
        fclose(fp);
        return -1;  // Ошибка создания информационной структуры
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return -1;  // Ошибка записи
    }

    png_init_io(png, fp);

    // Установка заголовка изображения
    png_set_IHDR(png, info, picture->width, picture->height, 8, PNG_COLOR_TYPE_GRAY,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // Запись данных изображения
    png_bytep row = (png_bytep)malloc(3 * picture->width * sizeof(png_byte));
    for (pixel_coord y = 0; y < picture->height; y++) {
        for (pixel_coord x = 0; x < picture->width; x++) {
            row[x] = picture->data[y * picture->width + x];
        }
        png_write_row(png, row);
    }
    free(row);

    png_write_end(png, NULL);
    png_destroy_write_struct(&png, &info);
    fclose(fp);

    return 0;
}

// Освобождение ресурсов изображения
void free_image(image_p picture) {
    free(picture->data);
    free(picture);
}