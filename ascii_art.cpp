#include <iostream>
#include <string>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"
using namespace std;
#define OFFSET_VAR 0.45

float map(float ValueToMap, float start1, float stop1, float start2, float stop2){
    return ((ValueToMap - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}


int main(){
    string FILE_PATH;
    cout << "Input the image absolute path" << endl;
    cin >> FILE_PATH;
    const char * FILE_PATH_C_STR = FILE_PATH.c_str();

    char ASCII_TABLE[] = {'.', ',', ':', '+', '*', '?', '%', 'S', '#', '@'};

    int width, height, channels;
    unsigned char *img = stbi_load(FILE_PATH_C_STR, &width, &height, &channels, 0);
    int DOWNSCALE_FACTOR = 1;
    if (width > 200) 
        DOWNSCALE_FACTOR = width / 200;

    unsigned char *img_scaled = (unsigned char *) malloc(width * OFFSET_VAR * height);
    int w_factor, h_factor;
    w_factor = width/DOWNSCALE_FACTOR;
    h_factor = height/DOWNSCALE_FACTOR;

    stbir_resize(img, width, height, 0, img_scaled, w_factor, OFFSET_VAR * h_factor, 0,
                 STBIR_TYPE_UINT8, 1, STBIR_ALPHA_CHANNEL_NONE, 0,
                 STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
                 STBIR_FILTER_MITCHELL, STBIR_FILTER_MITCHELL,
                 STBIR_COLORSPACE_SRGB, nullptr
    );
    stbi_image_free(img);
    for (int i = 0; i < OFFSET_VAR * h_factor; i++){
        for (int j = 0; j < w_factor; j++){
            int val = (int)img_scaled[i * w_factor + j];
            int MapIndex = (int)map(val, 0, 255, 0, 9);
            cout << ASCII_TABLE[MapIndex];
        }
        cout << endl;     
    }
    
    

    free(img_scaled);
    stbi_image_free(img_scaled);
    system("pause");

    return 0;
}
