#include "Vector.hpp"

namespace VECTOR_HORI_VERT {
  unsigned int Vector::get_length()const{
    return L;
  }
  std::string Vector::get_filename() const {
    return filename_;
  }
  Vector::Vector(const std::string& filename) {
    filename_ = filename;
    std::ofstream fil;
    fil.open(filename_.c_str(), std::ios_base::out | std::ios::trunc);
    if (!fil.is_open()) {
      throw std::invalid_argument("Error! Cannot open file " + filename_ + "!\n");
    }
    fil.close();
    znak=1;
    L=1;
    vector_.clear();
    vector_.push_back(0);
  }
  Vector::Vector(const std::string& filename, int N) {
    filename_ = filename;
    std::ofstream fil;
    fil.open(filename_.c_str(), std::ios_base::out | std::ios::trunc);
    if (!fil.is_open()) {
      throw std::invalid_argument("Error! Cannot open file " + filename_ + "!\n");
    }
    fil.close();
    if (N>=0){
        this->znak=1;
    }else{
        this->znak=-1;
    }
    N=std::abs(N);
    int tempy=1;
    for (int i=1;;i++){
        tempy*=10;
        if (tempy>N){
            this->L=i;
            break;
        }
    }
    for(int i=L-1;i>=0;i--){
        this->vector_.push_front(N%10);
        N=N/10;
    }
    while (vector_[0]==0){
        --L;
        vector_.pop_front();
    }
  }
    Vector::Vector(const std::string& filename, const std::string& N) {
        filename_ = filename;
        L=0;
        std::ofstream fil;
        fil.open(filename_.c_str(), std::ios_base::out | std::ios::trunc);
        if (!fil.is_open()) {
          throw std::invalid_argument("Error! Cannot open file " + filename_ + "!\n");
        }
        fil.close();
        if (N[0]=='-'){
            this->znak=-1;
        }else{
            this->znak=1;
        }
        if(this->znak==-1){
            for (int i=1;i<N.length();++i){
                this->vector_.push_front(N[i]-'0');
                ++L;
            }
        }else{
            for (int i=0;i<N.length();++i){
                this->vector_.push_front(N[i]-'0');
                ++L;
            }
        }
        while (vector_[0]==0){
            --L;
            vector_.pop_front();
        }

    }
  Vector::Vector(const Vector& other) {
    filename_ = other.filename_;
    L = other.L;
    for (unsigned int i = 0; i < L; i++) {
      vector_.push_back(other.vector_[i]);
    }
    this->znak = other.znak;
  }
  void Vector::operator=(const Vector& other) {
    filename_ = other.filename_;
    L= other.L;
    znak=other.znak;
    vector_.clear();
    for (int i = 0; i < L; i++) {
      vector_.push_back(other.vector_[i]);
    }
  }
  Vector::~Vector() {
    L = 0;
  }

}
