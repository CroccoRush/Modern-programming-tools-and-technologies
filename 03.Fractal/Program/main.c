#include <stdio.h>
#include "image.h"
#include "fractal.h"

int main() {
    // Создаем изображение 300x300
    image_p img = create_image(300, 300);

    // Очищаем изображение
    clear_image(img);

    // Рисуем множество Жюлиа
    draw_julia(img, -0.8 + 0.156 * I);
    save_pgm(img, "julia.pgm");
    save_png(img, "julia.png");  // Сохраняем в формате PNG

    // Очищаем изображение
    clear_image(img);

    // Рисуем ковер Серпинского
    draw_sierpinski(img, 0, 0, 300);
    save_pgm(img, "sierpinski.pgm");
    save_png(img, "sierpinski.png");  // Сохраняем в формате PNG

    // Освобождаем ресурсы
    free_image(img);

    return 0;
}