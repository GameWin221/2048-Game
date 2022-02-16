#include "Font.hpp"

Font* defaultFont = nullptr;

Font::Font(std::string fontPath, int fontSize)
{
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";
    
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font\n";
    else
    {
        FT_Set_Pixel_Sizes(face, 0, fontSize);
        FT_GlyphSlot g = face->glyph;

        unsigned int roww = 0;
        unsigned int rowh = 0;
        unsigned int w = 0;
        unsigned int h = 0;
    
        for (unsigned char c = 32; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "Failed loading character: \"" << (char)c << "\"\n";
                continue;
            }
    
            if (roww + g->bitmap.width + SPACING >= ATLASMAXSIZE) {
                w = std::max(w, roww);
                h += rowh;
                roww = 0;
                rowh = 0;
            }
            roww += g->bitmap.width + 1;
            rowh = std::max(rowh, g->bitmap.rows);
        }
    
        w = std::max(w, roww);
        h += rowh + SPACING;
    
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &textureAtlas);
        glBindTexture(GL_TEXTURE_2D, textureAtlas);
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
        int ox = 0;
        int oy = 0;
    
        rowh = 0;
    
        for (unsigned char c = 32; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                continue;
    
            if (ox + g->bitmap.width + SPACING >= ATLASMAXSIZE)
            {
                oy += rowh + SPACING;
                rowh = 0;
                ox = 0;
            }
    
            glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
    
            Character character;
            character.advance = glm::fvec2(g->advance.x >> 6,
                g->advance.y >> 6);
    
            character.size = glm::fvec2(g->bitmap.width,
                g->bitmap.rows);
    
            character.pivot = glm::fvec2(g->bitmap_left,
                g->bitmap_top);
    
            character.offset = glm::fvec2(ox / (float)w,
                oy / (float)h);
    
            characters.emplace(c, character);
    
            rowh = std::max(rowh, g->bitmap.rows);
            ox += g->bitmap.width + 1;
        }
    
        this->atlasSize.x = w;
        this->atlasSize.y = h;
    }
    
    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
Font::~Font(){}

Font* Font::DefaultFont()
{
    if (!defaultFont)
        defaultFont = new Font("Fonts/Roboto-Medium.ttf", 128);

    return defaultFont;
}