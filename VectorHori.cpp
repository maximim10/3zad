#include "VectorHori.hpp"

namespace VECTOR_HORI_VERT {
  void VectorHori::Output() const {
    std::ofstream fil;
    fil.open(this->get_filename().c_str(), std::ios_base::app);
    if (!fil.is_open()) {
      throw std::invalid_argument("Error! Cannot open file " + this->get_filename() + "!\n");
    }
    fil << this-> znak << "*";
    for (unsigned int i = 0; i < this->get_length(); i++) {
      fil << this->vector_[i] << ' ';
    }
    fil << std::endl;

    fil.close();
  }
  VectorHori operator-(Vector& first, Vector& other) {
    Vector* temp = new VectorHori(first.filename_, 1);
    temp->L=std::max(first.L,other.L);
    temp->vector_.clear();
    int mm=std::max(first.L,other.L)-std::min(first.L,other.L);
    if ((first.znak * other.znak) > 0){
        temp->znak=first.znak;
        if (first.L > other.L){
            temp->znak=first.znak;
        }else if (first.L < other.L){
            temp->znak=-first.znak;
        }else{
            for(int i=0; i<other.L; i++){
                if (first.vector_[i] < other.vector_[i]){
                    temp->znak=-first.znak;
                    break;
                }
            }
        }
        for (int i=std::max(first.L,other.L)-1; i>=0; i--) {

                temp->vector_.push_back((temp->znak==first.znak ? first.vector_[i] : other.vector_[i]) -
                                (temp->znak==first.znak ? (i-mm>=0 ? other.vector_[i-mm] : 0) : (i-mm>=0 ? first.vector_[i-mm] : 0)));

        }


        for (int i=std::max(first.L,other.L)-1;i>0;i--) {
            if (temp->vector_[i]<0){
                temp->vector_[i-1]--;
                temp->vector_[i]+=10;
            }
        }
        temp->vector_[0]=std::abs(temp->vector_[0]);
        int j=0;
        for (int i=0; i<temp->L; i++){
            if (temp->vector_[i]>0){
                break;
            }else{
                j+=1;
            }
        }
        if (j>0){
            std::deque <int> vtemp;
            for (int i=0;i<temp->L-j;i++){
                vtemp.push_back(temp->vector_[i+j]);
            }
            temp->vector_.clear();
            temp->vector_=vtemp;
            temp->L=temp->L-j;
        }
        return (*temp);
    }else{
        *temp=other;
        temp->znak=-(temp->znak);
        return ((first)+*temp);
    }
  }
  VectorHori operator+(Vector& first, Vector& other) {
    Vector* temp;                                                                                                                       \
    temp = new VectorHori(first.get_filename(),1);
    temp->L=std::max(first.L, other.L);
    temp->vector_.clear();
    int mm=std::max(first.L, other.L)-std::min(first.L, other.L);
    if ((first.znak * other.znak) > 0){
        temp->znak=other.znak;
        #pragma omp parallel
        {
            #pragma omp parallel for
            for(int i=std::max(first.L, other.L)-1;i>=0;i--){
                temp->vector_.push_back((first.L > other.L ? first.vector_[i] : (i-mm>=0 ? first.vector_[i-mm] : 0)) +
                                (other.L > first.L ? other.vector_[i] : (i-mm>=0 ? other.vector_[i-mm] : 0)));
            }
        }
        #pragma omp parallel
        {
            const int mx=std::max(first.L,other.L)-1;
            const int thrs=2;
            const int del=mx/thrs+(mx%thrs ? 1 : 0);
            #pragma omp parallel for num_threads(thrs)
            for (int core=0;core<thrs;++core){
                for(int i=mx-core*del;(i>mx-(core+1)*del)&&(i>0);--i){
                    if (temp->vector_[i]>9){
                        temp->vector_[i-1]++;
                        temp->vector_[i]-=10;
                    }
                }
                int i=mx-(core+1)*del;
                while (i>0){
                    if (temp->vector_[i]>9){
                        temp->vector_[i-1]++;
                        temp->vector_[i]-=10;
                    }else{
                        break;
                    }
                }
            }
        }
        /*for(int i=std::max(first.L,other.L)-1;i>0;i--){
            if (temp->vector_[i]>9){
                temp->vector_[i-1]++;
                temp->vector_[i]-=10;
            }
        }*/
        if(temp->vector_[0]>9){
            std::deque <int> vtemp;
            for (int i=std::max(first.L, other.L);i>0;i--){
                vtemp.push_back(temp->vector_[i-1]);
            }
            vtemp[0]=1;
            vtemp[1]-=10;
            temp->vector_.clear();
            temp->vector_=vtemp;
            temp->L=temp->L+1;
        }
        return (*temp);
    }else{
        (*temp)=other;
        temp->znak=-(temp->znak);
        return (first-(*temp));
     }
  }
  VectorHori::VectorHori(const std::string& filename, int N)
    : Vector(filename, N)
  {
  }
  VectorHori::VectorHori(const std::string& filename)
    : Vector(filename)
  {
  }
  VectorHori::VectorHori(const Vector& other)
    : Vector(other)
  {
  }
  VectorHori::VectorHori(const VectorHori& other)
    : Vector(other)
  {
  }
  VectorHori::~VectorHori() {
  }

}
