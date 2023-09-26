#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <immintrin.h>
#include <emmintrin.h>
#include <mmintrin.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <nmmintrin.h>
#include <ammintrin.h>
#include <wmmintrin.h>

static inline void getRGB(uint8_t *im, int width, int height, int nchannels, int x, int y, int *r, int *g, int *b, int *r2, int *g2, int *b2, int *r3, int *g3, int *b3, int *r4, int *g4, int *b4)
{
    unsigned char *offset = im + (x + width * y) * nchannels;
    *r = offset[0];
    *g = offset[1];
    *b = offset[2];
    *r2 = offset[4];
    *g2 = offset[5];
    *b2 = offset[6];
    *r3 = offset[8];
    *g3 = offset[9];
    *b3 = offset[10];
    *r4 = offset[12];
    *g4 = offset[13];
    *b4 = offset[14];
}

int main(int nargs, char **argv)
{
    int width, height, nchannels;
    struct timeval fin,ini;

    if (nargs < 2)
    {
        printf("Usage: %s <image1> [<image2> ...]\n", argv[0]);
    }

    // For each image
    // Bucle 0
    for (int file_i = 1; file_i < nargs; file_i++)
    {
        printf("[info] Processing %s\n", argv[file_i]);
        /****** Reading file ******/
        uint8_t *rgb_image = stbi_load(argv[file_i], &width, &height, &nchannels, 4);
        if (!rgb_image)
        {
            perror("Image could not be opened");
        }

        

        /****** Allocating memory ******/
        // - RGB2Grey
        uint8_t *grey_image = malloc(width * height);
        if (!grey_image)
        {
            perror("Could not allocate memory");
        }

        // - Filenames 
        for (int i = strlen(argv[file_i]) - 1; i >= 0; i--)
        {
            if (argv[file_i][i] == '.')
            {
                argv[file_i][i] = 0;
                break;
            }
        }

        char *grey_image_filename = 0;
        asprintf(&grey_image_filename, "%s_grey.jpg", argv[file_i]);
        if (!grey_image_filename)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

        /****** Computations ******/
        printf("[info] %s: width=%d, height=%d, nchannels=%d\n", argv[file_i], width, height, nchannels);

        if (nchannels != 3 && nchannels != 4)
        {
            printf("[error] Num of channels=%d not supported. Only three (RGB), four (RGBA) are supported.\n", nchannels);
            continue;
        }

        gettimeofday(&ini,NULL);
        // RGB to grey scale
        __m256i rgb1, rgb2, indices, test;
        __m256 rgb1_f, rgb2_f, coeff, mul1, add1, mul2, add2, add_ordered;
        __m128i res;
        __m128i vec1, vec2;
        int r, g, b, r2, g2, b2, r3, g3, b3, r4, g4, b4;
        coeff = _mm256_set_ps(0, 0.1140, 0.5870,  0.2989, 0, 0.1140, 0.5870, 0.2989);
        //coeff_f = _mm256_cvtepi32_ps(coeff);
        indices = _mm256_set_epi32(7, 3, 6, 2, 5, 1, 4, 0);
        for (int i = 0; i < width; i+=4)
        {
            for (int j = 0; j < height; j++)
            {
                getRGB(rgb_image, width, height, 4, i, j, &r, &g, &b, &r2, &g2, &b2, &r3, &g3, &b3, &r4, &g4, &b4);
                //grey_image[j * width + i] = (int)(0.2989 * r + 0.5870 * g + 0.1140 * b);
                //grey_image[j * width + i + 1] = (int)(0.2989 * r2 + 0.5870 * g2 + 0.1140 * b2);
                //printf("--%d, %d // (%d, %d, %d) // (%d, %d, %d) // (%d, %d, %d) // (%d, %d, %d)--", i, j, r, g, b, r2, g2, b2, r3, g3, b3, r4, g4, b4);                rgb1 = _mm256_set_epi32(r, g, b, 0, r2, g2, b2, 0);
                //printf("--%d/%d/%d/%d/%d/%d/%d/%d--", rgb1[0], rgb1[1], rgb1[2], rgb1[3], rgb1[4], rgb1[5], rgb1[6], rgb1[7]);
                


                // va masomenos
                rgb1 = _mm256_set_epi32((int)0, (int)b2, (int)g2, (int)r2, (int)0, (int)b, (int)g, (int)r);
                rgb2 = _mm256_set_epi32((int)0, (int)b4, (int)g4, (int)r4, (int)0, (int)b3, (int)g3, (int)r3);
                
                // Como se supone que hay que hacerlo, pero mi pc no me deja hacer loadu_epi8
                /*vec1 = _mm_loadu_epi8(rgb_image + ((i + (width * j)) * nchannels));
                vec2 = _mm_loadu_epi8(rgb_image + ((i + (width * j)) * nchannels) + 8);
                rgb1 = _mm256_cvtepi8_epi32(vec1);
                rgb2 = _mm256_cvtepi8_epi32(vec2);*/
                
                // Va masomenos
                /*vec1 = _mm_set_epi8(0,0,0,0,0,0,0,0,(int)0, (int)b2, (int)g2, (int)r2, (int)0, (int)b, (int)g, (int)r);
                vec2 = _mm_set_epi8(0,0,0,0,0,0,0,0,(int)0, (int)b4, (int)g4, (int)r4, (int)0, (int)b3, (int)g3, (int)r3);
                rgb1 = _mm256_cvtepu8_epi32(vec1);
                rgb2 = _mm256_cvtepu8_epi32(vec2);*/

                // no se por que este no va, me parecio buena idea
                /*unsigned char *offset = rgb_image + ((i + (width * j)) * nchannels);
                vec1 = _mm_loadu_si128(offset);
                vec2 = _mm_loadu_si128(offset + 8);
                rgb1 = _mm256_cvtepi8_epi32(vec1);
                rgb2 = _mm256_cvtepi8_epi32(vec2);*/


                
                rgb1_f = _mm256_cvtepi32_ps(rgb1);
                rgb2_f = _mm256_cvtepi32_ps(rgb2);
                mul1 = _mm256_mul_ps(rgb1_f, coeff);
                mul2 = _mm256_mul_ps(rgb2_f, coeff);
                add1 = _mm256_hadd_ps(mul2, mul1);
                add2 = _mm256_hadd_ps(add1, add1);
                add_ordered = _mm256_permutevar8x32_ps(add2, indices);
                res =_mm_cvtps_epi32(_mm256_extractf128_ps (add_ordered, 0));


                grey_image[(j * width) + i]       = res[0];
                grey_image[(j * width) + i + 1]   = res[1];
                grey_image[(j * width) + i + 2]   = res[2];
                grey_image[(j * width) + i + 3]   = res[3];
            }
        }

        stbi_write_jpg(grey_image_filename, width, height, 1, grey_image, 10);
        free(rgb_image);

        gettimeofday(&fin,NULL);

	printf("Tiempo: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
        free(grey_image_filename);
    }
}

void print128_num(__m256 var)
{
    uint32_t val[8];
    memcpy(val, &var, sizeof(val));
    printf("Numerical: %i %i %i %i %i %i %i %i \n", 
           val[0], val[1], val[2], val[3], val[4], val[5], 
           val[6], val[7]);
}

void print128_numi(__m256i var)
{
    uint16_t val[8];
    memcpy(val, &var, sizeof(val));
    printf("Numerical: %i %i %i %i %i %i %i %i \n", 
           val[0], val[1], val[2], val[3], val[4], val[5], 
           val[6], val[7]);
}

void print128i_num(__m128i var)
{
    uint32_t val[4];
    memcpy(val, &var, sizeof(val));
    printf("Numerical: %i %i %i %i \n", 
           val[0], val[1], val[2], val[3]);
}