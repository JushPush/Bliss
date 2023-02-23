#include <engine/asset.h>

#include <stb_image.h>

bool Asset::ReadAsText() {
    std::ifstream file(filePath);
    size_t size = 0;

    if (!file) {
        std::cerr << "Unable to load file: " << filePath << std::endl;
        return false;
    }

    size = file.tellg();

    file.read((char*)data, size * size);

    file.close();
    
    return true;
}

bool Asset::ReadAsImage() {
    unsigned char* data = stbi_load((filePath).c_str(), &width, &height, &numComponents, 4);
    if (data == NULL)
        return false;
    
    return true;
}