#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <ctime>
#include "Vector.hpp"
namespace VECTOR_HORI_VERT {

  class VectorHori  : public Vector {
protected:

  public:
    using Vector::operator=;
    void Output() const override;
    friend VectorHori operator+(Vector& first, Vector& second);
    friend VectorHori operator-(Vector& first, Vector& second);
    VectorHori(const std::string& filename, int N);
    VectorHori(const std::string& filename);
    VectorHori(const std::string& filename, const std::string& N);
    VectorHori(const Vector& other);
    VectorHori(const VectorHori& other);
    ~VectorHori();
  };
  VectorHori operator+(Vector& first, Vector& other);
VectorHori operator-(Vector& first, Vector& other);
}
