#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


/*
 * Read in the location of the pixel array, the image width, and the image 
 * height in the given bitmap file.
 */
void read_bitmap_metadata(FILE *image, int *pixel_array_offset, int *width, int *height) {
    fseek(image, 10, SEEK_SET);
    if (fread(pixel_array_offset, sizeof(int), 1, image) != 1) {
        fprintf(stderr, "Error: pixel array offset can not be read.");
    }
    fseek(image, 18, SEEK_SET);
    if (fread(width, sizeof(int), 1, image) != 1) {
        fprintf(stderr, "Error: image width can not be read.");
    }
    fseek(image, 22, SEEK_SET);
    if (fread(height, sizeof(int), 1, image) != 1) {
        fprintf(stderr, "Error: image width can not be read.");
    }
}

/*
 * Read in pixel array by following these instructions:
 *
 * 1. First, allocate space for m "struct pixel *" values, where m is the 
 *    height of the image.  Each pointer will eventually point to one row of 
 *    pixel data.
 * 2. For each pointer you just allocated, initialize it to point to 
 *    heap-allocated space for an entire row of pixel data.
 * 3. Use the given file and pixel_array_offset to initialize the actual 
 *    struct pixel values. 
 * 4. Return the address of the first "struct pixel *" you initialized.
 */
struct pixel **read_pixel_array(FILE *image, int pixel_array_offset, int width, int height) {
    struct pixel **pix_arr = malloc(sizeof(struct pixel *) * height);

    int row;
    int col;
    int counter = 0;

    for (row = 0; row < height; row++) {
        pix_arr[row] = malloc(sizeof(struct pixel) * width);
    }

    fseek(image, pixel_array_offset, SEEK_SET);

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            if (fread(&pix_arr[row][col], sizeof(struct pixel), 1, image) != 1) {
                fprintf(stderr, "Error: pixel row can not be read.");
            }
            counter++;
        }
    }
    return pix_arr;
}


/*
 * Print the blue, green, and red colour values of a pixel.
 * You don't need to change this function.
 */
void print_pixel(struct pixel p) {
    printf("(%u, %u, %u)\n", p.blue, p.green, p.red);
}
