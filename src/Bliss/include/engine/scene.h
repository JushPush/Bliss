#ifndef SCENE_H
#define SCENE_H

#include "manager.h"

class Scene {
public:
    virtual void Init() = 0;

    virtual void Input() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif