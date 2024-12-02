#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

RGBA ComposeColor(RGBA acolor, RGBA bcolor, float aweight, float bweight)
{
    RGBA result_color = {};
    result_color.r = u8((acolor.r*aweight + bcolor.r*bweight));
    result_color.g = u8((acolor.g*aweight + bcolor.g*bweight));
    result_color.b = u8((acolor.b*aweight + bcolor.b*bweight));
    //end_color.a = u8((acolor.a*aweight + bcolor.b*bweight));
    result_color.a = 0;
    return (result_color);
}

void CreateCircleGradient(Image32 image)
{
    srand((u32)time(nullptr));
    //RGBA start_color = {u8(rand() % 0x100), u8(rand() % 0x100), u8(rand() % 0x100), 0};
    //RGBA end_color = {u8(rand() % 0x100), u8(rand() % 0x100), u8(rand() % 0x100), 0};

    RGBA start_color = {u8(rand()), u8(rand()), u8(rand()), 0};
    RGBA end_color = {u8(rand()), u8(rand()), u8(rand()), 0};

    float max_dist_center = sqrtf(float((image.width /2) * (image.width /2) +
                                        (image.height/2) * (image.height/2)));
    u32 half_width = image.width / 2;
    u32 half_height = image.height / 2;

    for (u32 r = 0; r < image.height; r++)
    {
        for (u32 c = 0; c < image.width; c++)
        {
            s32 dist_x = s32(half_width - c);
            s32 dist_y = s32(half_height - r);
            s32 dist_x_sq = dist_x*dist_x;
            s32 dist_y_sq = dist_y*dist_y;
            float dist_center = sqrtf(float(dist_x_sq + dist_y_sq));

            float percent_gradient = dist_center/max_dist_center;
            float start_weight = percent_gradient;
            float end_weight = 1.0f - percent_gradient;

            RGBA pixel_color = ComposeColor(start_color, end_color, start_weight, end_weight);
            image.pixels[r * image.width + c] = pixel_color;
        }
    }
}

void CreateCornerGradient(Image32 image)
{
    srand((u32)time(nullptr));
    //RGBA start_color = {u8(rand() % 0x100), u8(rand() % 0x100), u8(rand() % 0x100), 0};
    //RGBA end_color = {u8(rand() % 0x100), u8(rand() % 0x100), u8(rand() % 0x100), 0};

    RGBA start_color = {u8(rand()), u8(rand()), u8(rand()), 0};
    RGBA end_color = {u8(rand()), u8(rand()), u8(rand()), 0};

    for (uint r = 0; r < image.height; r++)
    {
        for (uint c = 0; c < image.width; c++)
        {
            /*
            u32 RedValue = u32(0xFF * r / Image.Height);
            u32 GreenValue = u32(0xFF * c / Image.Width) << 8;
            u32 BlueValue =
                u32(0xFF * (r * Image.Height + c) / (Image.Height * Image.Width)) << 16;
            u32 RGBValue = RedValue | GreenValue | BlueValue;
            printf("%08x : %08x : %08x := %08x\n", RedValue, GreenValue, BlueValue, RGBValue);
            */
            /*
            u32 RGBValue = StartColor + u32(DiffColor *
                (r * Image.Width + c) / (Image.Width * Image.Height) / 2.0f);
            */
            float percent_gradient = float(r+c+1)/float(image.height+image.width);
            float start_weight = 1.0f - percent_gradient;
            float end_weight = percent_gradient;
            //printf("SW: %.2f, EW: %.2f\n", StartWeight, EndWeight);
            RGBA pixel_color = ComposeColor(start_color, end_color, start_weight, end_weight);
            image.pixels[r * image.width + c] = pixel_color;
        }
    }
}
