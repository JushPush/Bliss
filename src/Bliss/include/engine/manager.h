#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include "object.h"

class Manager {
public:
    virtual void Input(double time);
    virtual void Update(double time);
    virtual void Render();
};

class ObjectManager : Manager {
public:
    std::vector<Object*> objects;

    void Input(double time) {
        for (Object* _obj : objects) {
            _obj->Input();
        }
    }

    void Update(double time) {
        for (Object* _obj : objects) {
            _obj->Update();
        }
    }

    void Render() {
        for (Object* _obj : objects) {
            _obj->Render();
        }
    }
};

#endif