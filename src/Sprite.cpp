#include "Sprite.hpp"

const float vertices[8] = {
    -1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f,
     1.0f, -1.0f
};
const unsigned int indices[6] = {
    0, 1, 2,  
    2, 3, 0 
};

Shader* shader = nullptr;

GLuint VAO, VBO, EBO;

Sprite::Sprite(Texture* tex, glm::vec2 pos, glm::vec2 siz, glm::vec3 col)
{
    if (!shader)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        shader = new Shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    }


    this->texture = tex;

    this->position = pos;
    this->color    = col;
    this->size     = siz;
}
Sprite::~Sprite(){}

void Sprite::Render()
{
    int windowX, windowY;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &windowX, &windowY);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    proj = glm::ortho(0.0f, (float)windowX, 0.0f, (float)windowY, 0.1f, 1.5f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));

    model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.0f));
    model = glm::scale(    model, glm::vec3(this->size.x    , this->size.y    , 1.0f));

    shader->Use();
    shader->SetVec3("color", color);
    shader->SetMatrix4("view", view);
    shader->SetMatrix4("projection", proj);
    shader->SetMatrix4("model", model);
    shader->SetInt("mainTexture", 0);
    
    texture->Use(0);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}