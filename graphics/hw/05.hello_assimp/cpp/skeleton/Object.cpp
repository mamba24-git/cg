#include "Object.h"

void Object::init_buffer_objects() 
{
    // TODO
    std::vector<GLfloat> positions;
    std::vector<GLfloat> colors;
    std::vector<GLuint>  indices;
    if (!pmesh_) {
        std::cerr << "[ERROR] Object::init_buffer_objects: pmesh_ is nullptr!" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < pmesh_->mNumVertices; ++i) {
        
        aiVector3D v = pmesh_->mVertices[i];
        positions.push_back(v.x);
        positions.push_back(v.y);
        positions.push_back(v.z);

        if (pmesh_->mColors[0] != NULL) {
            aiColor4D c = pmesh_->mColors[0][i];
            colors.push_back(c.r);
            colors.push_back(c.g);
            colors.push_back(c.b);
            colors.push_back(c.a);
            is_color = true;
        } else {
            colors.push_back(0.5f);
            colors.push_back(0.5f);
            colors.push_back(0.5f);
            colors.push_back(1.0f);
            is_color = false;
        }
    }

    indices.clear();
    for (unsigned int i = 0; i < pmesh_->mNumFaces; ++i) {
        const aiFace& face = pmesh_->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
        
        Face f;
        f.index_buffer = 0;  
        f.num_indices = face.mNumIndices;
        faces.push_back(f);
    }

    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), positions.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

    
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    num_indices_ = indices.size();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

glm::mat4 Object::get_model_matrix() const
{
    glm::mat4 mat_model = glm::mat4(1.0f);
    
    // TODO
    mat_model = glm::translate(mat_model, vec_translate_);
    mat_model *= glm::mat4_cast(quat_rotate_);
    mat_model = glm::scale(mat_model, vec_scale_);

    return mat_model;
}

void Object::draw(int loc_a_position, int loc_a_color)
{
    std::cout << "draw() called: index_buffer=" << index_buffer << ", num_indices_=" << num_indices_ << std::endl;
   
    // TODO
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(loc_a_color);
    glVertexAttribPointer(loc_a_color, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    glDrawElements(GL_TRIANGLES, num_indices_, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_color);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
    
void Object::print_info()
{
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << pmesh_->mNumVertices << std::endl;
    for (unsigned int i = 0; i < pmesh_->mNumVertices; ++i)
    {
        aiVector3D vertex = pmesh_->mVertices[i];
        std::cout << "  vertex  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;

        if (pmesh_->mColors[0] != NULL)
        {
            aiColor4D color = pmesh_->mColors[0][i];
            std::cout << "  color  (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
        }
    }
}
