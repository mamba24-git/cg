#pragma once
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/scene.h> 
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


#include <GL/glew.h>
#include <iostream>

struct Face
{    
    GLuint index_buffer = 0;
    GLuint num_indices = 0;
};

class Object
{
public:
    Object() {}
    Object(const aiMesh* _pmesh) : pmesh_(_pmesh) {}

    void init_buffer_objects();
    void draw(int loc_a_position, int loc_a_color); // rendering 함수: 물체를 렌더링하는 함수.
    void print_info();

    std::string get_name() const                { return name_; }
    void set_name(const std::string& _name)     { name_ = _name; }

    glm::vec3 get_translate() const             { return vec_translate_; }
    glm::vec3 get_scale() const                 { return vec_scale_; }
    void set_translate(const glm::vec3& _vec)   { vec_translate_ = _vec; }
    void set_scale(const glm::vec3& _vec)       { vec_scale_ = _vec; }

    void get_rotate(glm::mat3& _mat) const      { _mat = glm::mat3_cast(quat_rotate_); }
    void get_rotate(glm::mat4& _mat) const      { _mat = glm::mat4_cast(quat_rotate_); }
    void get_rotate(glm::quat& _quat) const     { _quat = quat_rotate_; }
    void set_rotate(const glm::mat3& _mat)      { quat_rotate_ = glm::quat_cast(_mat); }
    void set_rotate(const glm::mat4& _mat)      { quat_rotate_ = glm::quat_cast(_mat); }
    void set_rotate(const glm::quat& _quat)     { quat_rotate_ = _quat; }

    glm::mat4 get_model_matrix() const;

private:

    GLuint  position_buffer; // GPU 메모리에서 vertices_buffer 위치 
    GLuint  color_buffer;    // GPU 메모리에서 color_buffer 위치
    bool    is_color = false;

    GLuint index_buffer; 
    GLuint num_indices_;

    std::vector<Face>   faces;
    const aiMesh*       pmesh_;
    std::string         name_;

    glm::vec3  vec_translate_ = glm::vec3(0.0f);
    // glm::mat4  mat_rotate;
    glm::quat  quat_rotate_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3  vec_scale_ = glm::vec3(1.0f);
};
