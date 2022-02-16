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

#define ATLASMAXSIZE 1024

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

public:
    std::map<char, Character> characters;

    glm::ivec2 atlasSize;
    GLuint textureAtlas;

    static Font* DefaultFont();

	Font(std::string fontPath, int fontSize);
	~Font();
};

#endif