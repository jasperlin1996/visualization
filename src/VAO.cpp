#include "VAO.h"

// VAO VAOManagement::generateVAO(vector<pair<PositionVec3, NormalVec3> > vertexData){
//     VAO myVAO;
//     GLuint vbo;
//     const int DIMENSION = 3;
//     // GLuint ebo;
//     // vector<int> index(vertexData.size(), 0);
//     // for(int i = 0; i < vertexData.size(); i++){
//     //     index[i] = i;
//     // }

//     glGenVertexArrays(1, &myVAO.vao);
//     glGenBuffers(1, &vbo);

//     glBindVertexArray(myVAO.vao);

//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(vertexData[0]), &vertexData[0], GL_STATIC_DRAW);
// 	for(int i = 0; i < sizeof(vertexData.size())/DIMENSION; i++){
// 		glEnableVertexAttribArray(i);
// 		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData[0]), (GLvoid*)(sizeof(PositionVec3)*i));
// 	}
    
//     glEnableVertexAttribArray(0);
//     glBindVertexArray(0);

//     myVAO.count = vertexData.size();

//     return myVAO;
// }


// VAO VAOManagement::generateVAO(vector<PositionVec3> vertexData){
//     VAO myVAO;
//     GLuint vbo;
//     const int DIMENSION = 3;

//     glGenVertexArrays(1, &myVAO.vao);
//     glGenBuffers(1, &vbo);

//     glBindVertexArray(myVAO.vao);

//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(vertexData[0]), &vertexData[0], GL_STATIC_DRAW);
// 	for(int i = 0; i < sizeof(vertexData.size())/DIMENSION; i++){
// 		glEnableVertexAttribArray(i);
// 		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData[0]), (GLvoid*)(sizeof(PositionVec3)*i));
// 	}
    
//     glEnableVertexAttribArray(0);
//     glBindVertexArray(0);

//     myVAO.count = vertexData.size();

//     return myVAO;
// }

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
    // cout << "VAO count: " << myVAO.count << endl;

    return myVAO;
}

void VAOManagement::drawVAO(vector<VAO> vao, Shader *myShader){
    for(int i = 0; i < vao.size(); i++){
        glUniform3fv(glGetUniformLocation(myShader->ID, "color"), 1, glm::value_ptr(glm::vec3(0.25f, 0.45f, 0.25f)));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(vao[i].vao);
        glDrawArrays(GL_TRIANGLES, 0, vao[i].count);
        glBindVertexArray(0);

        glUniform3fv(glGetUniformLocation(myShader->ID, "color"), 1, glm::value_ptr(glm::vec3(0.3f, 0.5f, 0.3f)));
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(vao[i].vao);
        glDrawArrays(GL_TRIANGLES, 0, vao[i].count);
        glBindVertexArray(0);
    }
}


void VAOManagement::drawVAO(vector<VAO> vao, GLenum render_mode = GL_TRIANGLES, GLenum rasterize_mode = GL_FILL){
    for(int i = 0; i < vao.size(); i++){
        // cout << "vao.size(): " << vao.size() << endl;
        // glUniform3fv(glGetUniformLocation(myShader->ID, "color"), 1, glm::value_ptr(glm::vec3(0.25f, 0.45f, 0.25f)));
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glBindVertexArray(vao[i].vao);
        // glDrawArrays(GL_TRIANGLES, 0, vao[i].count);
        // glBindVertexArray(0);

        // glUniform3fv(glGetUniformLocation(myShader->ID, "color"), 1, glm::value_ptr(glm::vec3(0.3f, 0.5f, 0.3f)));
        glBindVertexArray(vao[i].vao);
        glPolygonMode(GL_FRONT_AND_BACK, rasterize_mode);
        glDrawArrays(render_mode, 0, vao[i].count);
        glBindVertexArray(0);
    }
}