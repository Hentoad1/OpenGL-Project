#pragma once

#include "pch.h"

#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504

inline void checkGLErrors() {

    bool shouldThrow = false;

    GLenum err;
    do {
        err = glGetError();

        std::string name = "undefined";


        bool hitDefault = false;
        switch (err) {
        case(GL_INVALID_ENUM):
            name = "GL_INVALID_ENUM";
            break;
        case(GL_INVALID_VALUE):
            name = "GL_INVALID_VALUE";
            break;
        case(GL_INVALID_OPERATION):
            name = "GL_INVALID_OPERATION";
            break;
        case(GL_INVALID_FRAMEBUFFER_OPERATION):
            name = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case(GL_OUT_OF_MEMORY):
            name = "GL_OUT_OF_MEMORY";
            break;
        case(GL_STACK_UNDERFLOW):
            name = "GL_STACK_UNDERFLOW";
            break;
        case(GL_STACK_OVERFLOW):
            name = "GL_STACK_OVERFLOW";
            break;
        default:
            hitDefault = true;
        }

        if (!hitDefault) {
            std::cout << "GLERROR, code: " << err << ", name:" << name << std::endl;
        }

        shouldThrow = shouldThrow || !hitDefault;
    } while (err != GL_NO_ERROR);

    if (shouldThrow) {
        throw new std::exception("OpenGL Error");
    }
    else {
        std::cout << "No errors present" << std::endl;
    }
}