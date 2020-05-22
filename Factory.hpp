#pragma once

#include "Vector.hpp"
namespace VECTOR_HORI_VERT {
class Factory{
public:
    virtual Vector* Create (const std::string& filename, int N)=0;
    virtual Vector* Create (const std::string& filename, const std::string& N)=0;
};
}
