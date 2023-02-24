#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstddef>

struct Asset 
{
public:
    Asset() {}

	int width, height, numComponents;
    unsigned char* data = 0;

    std::string filePath;

    virtual bool Load() {
        std::ifstream file;
        size_t size;

        file.open(filePath);

        if (!file)
            return false;

        size = file.tellg();

        file.read((char*)data, size * size);

        file.seekg(16);

        file.read((char *)&width, 4);
        file.read((char *)&height, 4);

        //width = ntohl(width);
        //height = ntohl(height);

        file.close();
        return true;
    }

    virtual void Unload() = 0;
};

#endif