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
    enum AssetType {
        IMAGE,
        TEXT
    } _type;

    Asset() {}

	int width, height, numComponents;
    unsigned char* data = 0;

    std::string filePath;

    Asset(std::string path, AssetType type) {
        filePath = path;
        if (!LoadFile(filePath)) {
            std::cerr << "Failed to load file: " << filePath << std::endl;
        }
    }

    bool LoadFile(std::string path) {
        switch(_type) {
            case IMAGE:
                return ReadAsImage();
                break;
            default:
                return ReadAsText();
                break;
        }
        return true;
    }
private:
    bool ReadAsText();
    bool ReadAsImage();
};

#endif