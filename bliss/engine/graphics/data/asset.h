#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstddef>

class Asset {
public:
    Asset() {};
    Asset(const std::string& fileName);

    ~Asset() {
    };

    virtual void Init() {};
    virtual void Bind() {};
    virtual void Render() {};
    virtual void Unload() {};
};

#endif