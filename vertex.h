#pragma once 

#include "glm/glm.hpp"
/************************************************************
 * Class de sommet de base
 ************************************************************/
class Vertex {
public:
    inline Vertex (const glm::vec3 & p, const glm::vec3 & n, const glm::vec2 & t) : p (p), n (n), t (t) {}
    inline virtual ~Vertex () {}
    inline Vertex & operator= (const Vertex & v) {
        p = v.p;
        n = v.n;
        t = v.t;
        return (*this);
    }
    glm::vec3 p;
    glm::vec3 n;
    glm::vec2 t;
};

