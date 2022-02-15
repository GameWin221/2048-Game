/*
#pragma once

#ifndef FONT_HPP
#define FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

struct Character {
    glm::fvec2 size;
    glm::fvec2 pivot;
    glm::fvec2 advance;
    glm::fvec2 offset;
};

class Font
{
private:
    FT_Library ft;
    FT_Face face;

    #define ATLASMAXSIZE 1024
    #define FONTSIZE 128

    int atlas_width = 0;
    int atlas_height = 0;

    GLuint textureAtlas;

    std::map<char, Character> characters;

public:
	Font();
	~Font();
};

#endif
*/