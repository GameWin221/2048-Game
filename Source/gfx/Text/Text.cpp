#include "gfx/Text/Text.hpp"

Shader* textShader = nullptr;

Text::Text(Font* newFont, std::string newText, float newScale, glm::vec3 newColor)
{
    this->font = newFont;
    this->text = newText;
    this->scale = newScale;
    this->color = newColor;
    this->centered = false;
    this->textBounds = glm::vec2(0);

    if (!textShader)
        textShader = new Shader("Resources/Shaders/text_vertex.glsl", "Resources/Shaders/text_fragment.glsl");

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
Text::~Text()
{
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);
};

void Text::SetString(std::string newText)
{
    this->text = newText;

    float x = 0;
    float y = 0;

    vertices.clear();
    for (auto& c : this->text)
    {
        const Character& character = this->font->characters[c];

        float x2 = x + character.pivot.x;
        float y2 = -y - character.pivot.y;
        float w = character.size.x;
        float h = character.size.y;

        x += character.advance.x;
        y += character.advance.y;

        if (!w || !h) continue;

        const glm::ivec2 atlasSize = this->font->GetAtlasSize();

        point pt = { x2, -y2, character.offset.x, character.offset.y };
        vertices.emplace_back(pt);
        pt = { x2 + w, -y2    , character.offset.x + character.size.x / atlasSize.x, character.offset.y };
        vertices.emplace_back(pt);
        pt = { x2,     -y2 - h, character.offset.x, character.offset.y + character.size.y / atlasSize.y };
        vertices.emplace_back(pt);
        pt = { x2 + w, -y2 - h, character.offset.x + character.size.x / atlasSize.x, character.offset.y + character.size.y / atlasSize.y };
        vertices.emplace_back(pt);
        pt = { x2,     -y2 - h, character.offset.x, character.offset.y + character.size.y / atlasSize.y };
        vertices.emplace_back(pt);
        pt = { x2 + w, -y2    , character.offset.x + character.size.x / atlasSize.x, character.offset.y };
        vertices.emplace_back(pt);
    }

    const Character& firstChar = this->font->characters[this->text[0]];
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

void Text::SetFont(Font* newFont)
{
    this->font = newFont;
    this->SetString(this->text);
}
Font* Text::GetFont()
{
    return this->font;
}

void Text::InitInstancing()
{
    int windowX, windowY;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &windowX, &windowY);

    const glm::mat4 proj = glm::ortho(0.0f, (float)windowX, 0.0f, (float)windowY, 0.1f, 1.5f);

    textShader->Use();
    textShader->SetMat4("projection", proj);
    textShader->SetInt("text", 0);

    glActiveTexture(GL_TEXTURE0);
}

void Text::Render()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->position, -1.0f));
    model = glm::scale(model, glm::vec3(this->scale));

    if (centered)
    {
        const glm::vec2 centerOffset = -this->textBounds / 2.0f;
        model = glm::translate(model, glm::vec3(centerOffset, 0));
    }

    textShader->SetVec3("color", this->color);
    textShader->SetMat4("model", model);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBindTexture(GL_TEXTURE_2D, this->font->GetTextureID());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}