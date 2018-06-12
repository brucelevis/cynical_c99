//
// Created by temdisponivel on 11/06/2018.
//

#include "text.h"

#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_truetype.h"
#include "file.h"

#undef STB_TRUETYPE_IMPLEMENTATION

void load_font(
        const char *font_path, 
        float size, 
        material_t *material,
        font_t *dest
) {
    stbtt_fontinfo font;

    

    uint len;
    byte *file_data = read_file_data_alloc(font_path, &len);
    ASSERT(file_data);

    bool result = stbtt_InitFont(&font, file_data, stbtt_GetFontOffsetForIndex(file_data, 0));
    ASSERT(result);

    byte *buffer = malloc(sizeof(int) * (1024 * 1024));
    for (int character = INITIAL_CHARACTER; character < MAX_CHARACTERS; ++character) {
        int width, height, x_offset, y_offset;
        
        byte *data = stbtt_GetCodepointBitmap(
                &font,
                0,
                stbtt_ScaleForPixelHeight(&font, size),
                character,
                &width,
                &height,
                &x_offset,
                &y_offset
        );

        image_t image;
        image.size = vec2_make(width, height);
        image.data = buffer;

        const int pitch = (width * 4);
        byte *src_data = data;
        byte *dest_data = image.data + (height - 1) * pitch;
        for (int i = 0; i < height; ++i) {

            uint *dest = (uint *) dest_data;

            for (int j = 0; j < width; ++j) {

                byte alpha = *src_data++;
                uint pixel_color = (
                        (alpha << 24) |
                        (alpha << 16) |
                        (alpha << 8) |
                        (alpha << 0)
                );
                *dest++ = pixel_color;
            }
            dest_data -= pitch;
        }

        texture_t texture;
        create_texture(&image, &texture);

        code_point_t code_point;
        code_point.texture = texture;
        code_point.offset = vec2_make(x_offset, y_offset);
        dest->code_points[character] = code_point;

        stbtt_FreeBitmap(data, 0);
    }
    
    free(buffer);
    
    dest->material = material;

    free_file_data(file_data);
}

void draw_string(const font_t *font, const char *string, vec2_t position) {
    transform_t transform;
    trans_identity(&transform);
    transform.position = VEC3_FROM_VEC2(position);
    
    material_t *material = font->material;
    texture_renderer_t renderer_helper;
    
    int len = strlen(string);
    for (int i = 0; i < len; ++i) {
        char character = string[i];
        code_point_t code_point = font->code_points[(int) character];
        create_texture_renderer(&code_point.texture, material, &renderer_helper);
        draw_texture_renderer(&renderer_helper, &transform);
        
        transform.position.x += 32;//code_point.texture.size.width + code_point.offset.width;
        //transform.position.y = position.y + code_point.offset.height;
    }
}