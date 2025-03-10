#include <renderer/skybox.h>

#include <stb_image.h>

Skybox CreateSkybox() {
    return Skybox{
        new float[24] {
            // Coordinates
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f
        },
        new unsigned int[36] {
            // Right
            1,2,6,
            6,5,1,
            // Left
            0,4,7,
            7,3,0,
            // Top
            4,5,6,
            6,7,4,
            // Bottom
            0,3,2,
            2,1,0,
            // Back
            0,1,5,
            5,4,0,
            // Front
            3,7,6,
            6,2,3
        }
    };
}

void InitSkybox(Skybox& skybox) {
    glGenVertexArrays(1, &skybox.skyboxVAO);

	glGenBuffers(1, &skybox.skyboxVBO);
	glGenBuffers(1, &skybox.skyboxEBO);

	glBindVertexArray(skybox.skyboxVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, skybox.skyboxVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox.skyboxVertices), &skybox.skyboxVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skybox.skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skybox.skyboxIndices), &skybox.skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::string facesCubemap[6] = 
    {
        "./res/skybox/right.jpg",
        "./res/skybox/left.jpg",
        "./res/skybox/top.jpg",
        "./res/skybox/bottom.jpg",
        "./res/skybox/front.jpg",
        "./res/skybox/back.jpg"
    };

    skybox.cubemapTexture;

    glGenTextures(1, &skybox.cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else {

        }
    }
}
void RenderSkybox(Skybox& skybox) {
    glBindVertexArray(skybox.skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.cubemapTexture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}