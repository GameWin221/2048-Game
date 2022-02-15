#include "Text.hpp"

struct Character {
    glm::fvec2 size;
    glm::fvec2 pivot;
    glm::fvec2 advance;
    glm::fvec2 offset;
};

FT_Library ft;
FT_Face face;

Shader* textShader = nullptr;

#define ATLASMAXSIZE 1024
#define FONTSIZE 128

int atlas_width = 0;
int atlas_height = 0;

GLuint textureAtlas;

std::map<char, Character> characters;

Text::Text(std::string newText, float newScale, glm::vec3 newColor)
{
    this->text = newText;
    this->scale = newScale;
    this->color = newColor;
    this->centered = false;

    this->textBounds = glm::vec2(0);

    if (!textShader)
    {
        textShader = new Shader("Shaders/text_vertex.glsl", "Shaders/text_fragment.glsl");

        if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";

        if (FT_New_Face(ft, "Fonts/calibri.ttf", 0, &face))
            std::cout << "ERROR::FREETYPE: Failed to load font\n";
        else 
        {
            FT_Set_Pixel_Sizes(face, 0, FONTSIZE);
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

                if (roww + g->bitmap.width + 1 >= ATLASMAXSIZE) {
                    w = std::max(w, roww);
                    h += rowh;
                    roww = 0;
                    rowh = 0;
                }
                roww += g->bitmap.width + 1;
                rowh = std::max(rowh, g->bitmap.rows);
            }

            w = std::max(w, roww);
            h += rowh;

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

                if (ox + g->bitmap.width + 1 >= ATLASMAXSIZE)
                {
                    oy += rowh;
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

            atlas_width = w;
            atlas_height = h;
        }


        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        std::cout << "Generated a " << atlas_width << " x " << atlas_height << ", " << atlas_width * atlas_height / 1024 << "kb atlas\n";
    }

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->SetString(this->text);
}
Text::~Text(){};

void Text::SetString(std::string newText)
{
    this->text = newText;

    float x = 0;
    float y = 0;

    vertices.clear();
    for (auto& c : this->text)
    {
        const Character character = characters[c];

        float x2 = x + character.pivot.x;
        float y2 = -y - character.pivot.y;
        float w = character.size.x;
        float h = character.size.y;

        x += character.advance.x;
        y += character.advance.y;

        if (!w || !h) continue;

        point pt = { x2, -y2, character.offset.x, character.offset.y };
        vertices.push_back(pt);
        pt = { x2 + w, -y2    , character.offset.x + character.size.x / atlas_width, character.offset.y };
        vertices.push_back(pt);
        pt = { x2,     -y2 - h, character.offset.x, character.offset.y + character.size.y / atlas_height };
        vertices.push_back(pt);
        pt = { x2 + w, -y2 - h, character.offset.x + character.size.x / atlas_width, character.offset.y + character.size.y / atlas_height };
        vertices.push_back(pt);
        pt = { x2,     -y2 - h, character.offset.x, character.offset.y + character.size.y / atlas_height };
        vertices.push_back(pt);
        pt = { x2 + w, -y2    , character.offset.x + character.size.x / atlas_width, character.offset.y };
        vertices.push_back(pt);
    }

    const Character firstChar = characters[this->text[0]];
    this->textBounds = glm::vec2(x, firstChar.size.y);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(point), vertices.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::string Text::GetString()
{
    return this->text;
}

void Text::InitInstancing()
{
    textShader->Use();
    
    int windowX, windowY;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &windowX, &windowY);

    glm::mat4 proj = glm::mat4(1.0f);

    proj = glm::ortho(0.0f, (float)windowX, 0.0f, (float)windowY, 0.1f, 1.5f);

    textShader->SetMat4("projection", proj);
    textShader->SetInt("text", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);
}

void Text::Render()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->position, -1.0f));
    model = glm::scale(model, glm::vec3(this->scale));

    if (centered)
    {
        const glm::vec2 centerOffset = -this->textBounds / 2.0f;
        model = glm::translate(model, glm::vec3(centerOffset, 0.0));
    }

    textShader->SetVec3("color", this->color);
    textShader->SetMat4("model", model);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}