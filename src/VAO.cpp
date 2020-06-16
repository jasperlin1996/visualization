#include "VAO.h"

VAO VAOManagement::generateVAO(vector<float> vertexData){
    cout << "generate VAO: " << vertexData.size() << '\n';

    VAO myVAO;
    GLuint vbo;
    const int DIMENSION  = 3;
    const int ATTRIBUTES = 2;

    glGenVertexArrays(1, &(myVAO.vao));
    glGenBuffers(1, &vbo);

    glBindVertexArray(myVAO.vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(vertexData[0]), vertexData.data(), GL_STATIC_DRAW);
    // position only
	for(int i = 0; i < ATTRIBUTES; i++){
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, DIMENSION * ATTRIBUTES * sizeof(float), (GLvoid*)(DIMENSION * sizeof(float)*i));
		glEnableVertexAttribArray(i);
	}
    
    glBindVertexArray(0);

    myVAO.count = vertexData.size() / (DIMENSION * ATTRIBUTES);

    return myVAO;
}

// Version 3
void VAOManagement::drawVAO(vector<VAO> &vao, bool use_texture, vector<Texture> &textures, GLenum render_mode = GL_TRIANGLES, GLenum rasterize_mode = GL_FILL){
    int texture_counter = 0;
    for(size_t i = 0; i < vao.size(); i++){
        glBindVertexArray(vao[i].vao);
        if (use_texture) {
            for(size_t j = 0; use_texture && j < textures.size(); j++){
                glActiveTexture(GL_TEXTURE0 + j + texture_counter);
                glBindTexture(textures[j].target, textures[j].textures);
            }
        }

        glPolygonMode(GL_FRONT_AND_BACK, rasterize_mode);
        glDrawArrays(render_mode, 0, vao[i].count);

        // unbind texture
        if (use_texture) {
            for(size_t j = 0; use_texture && j < textures.size(); j++){
                glActiveTexture(GL_TEXTURE0 + j + texture_counter);
                glBindTexture(textures[j].target, 0);
            }
        }
        // unbind vao
        glBindVertexArray(0);

        if (use_texture) texture_counter += textures.size();
    }
}

// Version 1
// void VAOManagement::drawVAO(vector<VAO> vao, Shader *myShader){
//     for(int i = 0; i < vao.size(); i++){
//         glUniform3fv(glGetUniformLocation(myShader->ID, "color"), 1, glm::value_ptr(glm::vec3(0.25f, 0.45f, 0.25f)));
//         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//         glBindVertexArray(vao[i].vao);
//         glDrawArrays(GL_TRIANGLES, 0, vao[i].count);
//         glBindVertexArray(0);

//         glUniform3fv(glGetUniformLocation(myShader->ID, "color"), 1, glm::value_ptr(glm::vec3(0.3f, 0.5f, 0.3f)));
//         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//         glBindVertexArray(vao[i].vao);
//         glDrawArrays(GL_TRIANGLES, 0, vao[i].count);
//         glBindVertexArray(0);
//     }
// }


// Version 2
// void VAOManagement::drawVAO(vector<VAO> &vao, GLenum render_mode, GLenum rasterize_mode){
//     for(int i = 0; i < vao.size(); i++){
//         glBindVertexArray(vao[i].vao);
//         glPolygonMode(GL_FRONT_AND_BACK, rasterize_mode);
//         glDrawArrays(render_mode, 0, vao[i].count);
//         glBindVertexArray(0);
//     }
// }