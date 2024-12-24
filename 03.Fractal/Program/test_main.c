#include <stdio.h>
#include "../YY.utest/utest.h"
#include "image.h"
#include "fractal.h"

struct ImageTestFixture {
    image_p i;
};

UTEST_F_SETUP(ImageTestFixture) {
    utest_fixture->i = create_image(300, 300);
    ASSERT_NE((void *) utest_fixture->i, NULL);
}

UTEST_F_TEARDOWN(ImageTestFixture) {
    free_image(utest_fixture->i);
    remove("test.pgm");
    remove("test.png");
}

UTEST_F(ImageTestFixture, Set_Get_Pixel1) {
    set_pixel(utest_fixture->i, 10, 10, 10);
    ASSERT_EQ(10, get_pixel(utest_fixture->i, 10, 10));
}

UTEST_F(ImageTestFixture, ClearImage2) {
    clear_image(utest_fixture->i);
    ASSERT_EQ(0, get_pixel(utest_fixture->i, 10, 10));
}

UTEST_F(ImageTestFixture, Julia) {
    clear_image(utest_fixture->i);
    draw_julia(utest_fixture->i, -0.8 + 0.156 * I);
    ASSERT_EQ(0, get_pixel(utest_fixture->i, 0, 0));
    ASSERT_EQ(255, get_pixel(utest_fixture->i, 150, 150));
}

UTEST_F(ImageTestFixture, Sierpinski) {
    clear_image(utest_fixture->i);
    draw_sierpinski(utest_fixture->i, 0, 0, 300);
    ASSERT_EQ(255, get_pixel(utest_fixture->i, 0, 0));
    ASSERT_EQ(0, get_pixel(utest_fixture->i, 150, 150));
}

UTEST_F(ImageTestFixture, SavePGM) {
    clear_image(utest_fixture->i);
    int code = save_pgm(utest_fixture->i, "test.pgm");
    ASSERT_EQ(0, code);
    FILE *file = fopen("test.pgm", "r");
    ASSERT_TRUE(file);
    fclose(file);
}

UTEST_F(ImageTestFixture, SavePNG) {
    clear_image(utest_fixture->i);
    int code = save_png(utest_fixture->i, "test.png");
    ASSERT_EQ(0, code);
    FILE *file = fopen("test.png", "r");
    ASSERT_TRUE(file);
    fclose(file);
}

UTEST_MAIN();