#include "include/FontRenderer.h"
#include <iostream>

int FontRenderer::FontWidth[256] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    4,  // SPACE
    2,  // !
    4,  // "
    6,  // #
    6,  // $
    7,  // %
    8,  // &
    2,  // '
    4,  // (
    4,  // )
    8,  // *
    6,  // +
    3,  // ,
    4,  // -
    2,  // .
    5,  // /
    6,  // 0
    4,  // 1
    6,  // 2
    6,  // 3
    7,  // 4
    6,  // 5
    6,  // 6
    6,  // 7
    6,  // 8
    6,  // 9
    3,  // :
    4,  // ;
    5,  // <
    6,  // =
    5,  // >
    6,  // ?
    8,  // @
    6,  // A
    6,  // B
    6,  // C
    6,  // D
    6,  // E
    5,  // F
    6,  // G
    6,  // H
    4,  // I
    6,  // J
    6,  // K
    5,  // L
    8,  // M
    7,  // N
    6,  // O
    6,  // P
    6,  // Q
    6,  // R
    6,  // S
    6,  // T
    6,  // U
    6,  // V
    7,  // W
    6,  // X
    6,  // Y
    6,  // Z
    4,  // [
    5,  // \ 
    4,  // ]
    6,  // ^
    5,  // _
    3,  // '
    6,  // a
    6,  // b
    6,  // c
    6,  // d
    6,  // e
    6,  // f
    6,  // g
    6,  // h
    2,  // i
    5,  // j
    5,  // k
    4,  // l
    6,  // m
    6,  // n
    6,  // o
    6,  // p
    6,  // q
    6,  // r
    6,  // s
    5,  // t
    6,  // u
    6,  // v
    6,  // w
    6,  // x
    6,  // y
    6,  // z
    5,  // {
    2,  // |
    5,  // }
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8
};


float FontRenderer::pixelx = 1.0f / 2048;
float* FontRenderer::data = (float*)malloc(sizeof(float) * 20);



FontRenderer::FontRenderer() {
    shader = new Shader("src/Application/FontRenderer/res/Shaders/2d.vert", "src/Application/FontRenderer/res/Shaders/2d.frag");
    texture = new Texture("src/Application/FontRenderer/res/fonts.png",GL_RGBA);
    m_batch = new FontBatch(100 * 20 * sizeof(float));
}

float* FontRenderer::getFontVertices(unsigned char ch, float startx, float starty, float scale) {
    
	float xr = (float)Window::GetWidth() / (float)Window::GetHeight();
	float yr = (float)Window::GetHeight() / (float)Window::GetWidth();
    
    float vertices[] = {
		startx,                                     starty,                         0.0f,           (pixelx * 8 * ch),                                  1.0f,
		(startx + FontWidth[ch] * scale),           starty,                         0.0f,           (pixelx * 8 * ch) + (FontWidth[ch] * pixelx),       1.0f,
        (startx + FontWidth[ch] * scale),           starty - 8 * scale,       0.0f,           (pixelx * 8 * ch) + (FontWidth[ch] * pixelx),       0.0f,
        startx,                                     starty - 8 * scale,       0.0f,           (pixelx * 8 * ch),                                  0.0f
    };
    memcpy(data, vertices, 20 * sizeof(float));
    return data;
}

void FontRenderer::PrintString(std::string str, float x, float y, float scale, float degree, glm::vec3 rotationaxis) {
    shader->Bind();
    glm::mat4 projection = glm::mat4(1.0f);
    float xr = (float)Window::GetWidth() / (float)Window::GetHeight();
    float yr = (float)Window::GetHeight() / (float)Window::GetWidth();
    projection = glm::ortho(-xr, xr, -1.0f, 1.0f);
    shader->SetMat4("projection", projection);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, texture->get());
    shader->Set1i("tex", 2);
    int strwidth = getStringPixelWidth(str);
    float startx = -((strwidth * scale) / 2);
    float starty = 4 * scale;
    int index = 0;
    if (str.compare(temp_str) != 0 || scale != temp_scale) {
        //m_batch->Delete();
        //delete m_batch;
        //m_batch = new FontBatch(100 * 20 * sizeof(float));
        m_batch->CleanVertices();
        while (str[index]) {
            m_batch->AddQuad(getFontVertices(str[index], startx, starty, scale));
            startx += FontWidth[str[index]] * scale;
            index++;
        }
        temp_str = str;
        temp_scale = scale;
    }
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::rotate(model, glm::radians(degree), rotationaxis);
    shader->SetMat4("model", model);
    m_batch->Render(shader);
}

void FontRenderer::PrintString(std::string str, float x, float y, float scale) {
    PrintString(str, x, y, scale, 0.0f, glm::vec3(1.0f));
}

void FontRenderer::Delete() {
    texture->Delete();
    shader->Delete();
    m_batch->Delete();
    delete m_batch;
    delete texture;
    delete shader;
}

void FontRenderer::Free() {
    free(data);
}

unsigned int FontRenderer::getStringPixelWidth(std::string str) {
    unsigned int value = 0;
    int index = 0;
    while (str[index]) {
        value += FontWidth[str[index]];
        index++;
    }
    return value;
}