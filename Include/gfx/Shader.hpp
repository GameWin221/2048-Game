#pragma once

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    GLuint ID;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use();

    void SetMat4   (const std::string& name, const glm::mat4& value) const;
    void SetVec4   (const std::string& name, const glm::vec4& value) const;
    void SetVec3   (const std::string& name, const glm::vec3& value) const;
    void SetVec2   (const std::string& name, const glm::vec2& value) const;
    void SetBool   (const std::string& name, bool      value) const;
    void SetInt    (const std::string& name, int       value) const;
    void SetFloat  (const std::string& name, float     value) const;
    void SetDouble (const std::string& name, float     value) const;

    int GetUniformPos(const std::string& name);

    const GLuint& GetShaderID() const { return this->ID; };
};
#endif