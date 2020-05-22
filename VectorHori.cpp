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
  //VectorHori operator+(Vector& first, Vector& other);
  VectorHori operator-(Vector& first, Vector& other) {

    Vector* temp = new VectorHori(first.filename_, 1);
    temp->L=std::max(first.L,other.L);
    temp->vector_.clear();
    int mm=std::max(first.L,other.L)-std::min(first.L,other.L);
    if ((first.znak * other.znak) > 0){
        temp->znak=first.znak;
        /*for (int yy=0;yy<first.vector_.size();++yy){
            std::cout<<first.vector_[yy]<<"  ";
        }std::cout<<"-"<<std::endl;
        for (int yy=0;yy<other.vector_.size();++yy){
            std::cout<<other.vector_[yy]<<"  ";
        }*/
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
                if (first.vector_[i] > other.vector_[i]){
                    temp->znak=first.znak;
                    break;
                }
            }
        }
        for (int i=std::max(first.L,other.L)-1; i>=0; i--) {

                temp->vector_.push_front((temp->znak==first.znak ? first.vector_[i] : other.vector_[i]) -
                                         (temp->znak==first.znak ? (i-mm>=0 ? other.vector_[i-mm] : 0) : (i-mm>=0 ? first.vector_[i-mm] : 0)));

        }


        for (int i=std::max(first.L,other.L)-1;i>0;i--) {
            if (temp->vector_[i]<0){
                temp->vector_[i-1]--;
                temp->vector_[i]+=10;
            }
        }

        while ((temp->vector_[0]==0) && (temp->vector_.size()>1)){
            --temp->L;
            temp->vector_.pop_front();
        }
        /*std::cout<<"="<<std::endl;
        for (int yy=0;yy<temp->vector_.size();++yy){
            std::cout<<temp->vector_[yy]<<"  ";
        }
        std::cout<<std::endl;*/
        temp->vector_[0]=std::abs(temp->vector_[0]);
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
        temp->vector_.resize(temp->L);
        #pragma omp parallel for
        for(int i=std::max(first.L, other.L)-1;i>=0;i--){
            temp->vector_[i]=((first.L > other.L ? first.vector_[i] : (i-mm>=0 ? first.vector_[i-mm] : 0)) +
                                     (other.L > first.L ? other.vector_[i] : (i-mm>=0 ? other.vector_[i-mm] : 0)));
        }
        std::cout<<std::endl;
            const int mx=std::max(first.vector_.size(),other.vector_.size())-1;
            const int thrs=2;
            const int del=(mx+1)/thrs+((mx+1)%thrs ? 1 : 0);
            #pragma omp parallel for num_threads(thrs)
            for (int core=0;core<thrs;++core){//std::cout<<"thr_num= "<<core<<", ";
                for(int i=mx-core*del;((i>mx-(core+1)*del)&&(i>0));--i){

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
                        --i;
                    }else{
                        break;
                    }
                }
                //std::cout<<" end ";
            }
        /*for(int i=std::max(first.L,other.L)-1;i>0;i--){
            if (temp->vector_[i]>9){
                temp->vector_[i-1]++;
                temp->vector_[i]-=10;
            }
        }*/
        if(temp->vector_[0]>9){
            temp->vector_[0]-=10;
            temp->vector_.push_front(1);

            ++temp->L;
        }

        return (*temp);
    }else{/*
        for (int yy=0;yy<first.vector_.size();++yy){
            std::cout<<first.vector_[yy]<<"  ";
        }std::cout<<"+"<<std::endl;
        for (int yy=0;yy<other.vector_.size();++yy){
            std::cout<<other.vector_[yy]<<"  ";
        }*/
        (*temp)=other;
        temp->znak=-(temp->znak);
        return (first-(*temp));
     }
  }
  VectorHori::VectorHori(const std::string& filename, int N)
    : Vector(filename, N)
  {
  }
  VectorHori::VectorHori(const std::string& filename, const std::string& N)
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
