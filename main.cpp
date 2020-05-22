#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include "omp.h"
//#include <parallel.h>

#include <ctime>
#include "Vector.hpp"
//#include "Vector.cpp"
#include "VectorHori.hpp"
//#include "VectorHori.cpp"
#include "VectorVert.hpp"
//#include "VectorVert.cpp"
#include "Factory.hpp"
#include "FactoryHori.hpp"
#include "FactoryVert.hpp"

using namespace VECTOR_HORI_VERT;
int autotest(){
    /*try
    {
    Vector* v1=new VectorHori("Test.txt",73);
    Vector* v2=new VectorHori("Text.txt",57);
    VectorHori v4=*v1-*v2;
    VectorHori v3=*v1+*v2;
    if ( (v3.vector_[0]==1) && (v3.vector_[1]==3) && (v3.vector_[2]==0) && (v3.vector_.size()==3)
      && (v4.vector_[0]==1) && (v4.vector_[1]==6) && (v4.vector_.size()==2) ){
        delete v2;
        delete v1;
        return 0;
    }else{
        v4.Output();
        delete v2;
        delete v1;
        return 1;
    }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }*/return 0;
}
int main() {
    try {
        int aut=autotest();
        if (aut!=0){
        std::cout<<"HMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM"<<std::endl;
        return -1;
        }
        std::map < std::string, Factory* > factoryMap;
        factoryMap["Hori"] = new FactoryHori;
        factoryMap["Vert"] = new FactoryVert;
        std::vector< Vector* > vectorVector;
        const std::string inputFileName = "input.txt";
        std::ifstream inputFile(inputFileName.c_str(), std::ios_base::in);
        if (!inputFile.is_open()) {
            throw std::invalid_argument("Error! Cannot open file " + inputFileName + "!\n");
        }
        std::string tmpString;
        while (std::getline(inputFile, tmpString)) {
            std::stringstream strStream;
            strStream << tmpString;
            std::string vectorType;
            strStream >> vectorType;
            std::string fileName;
            strStream >> fileName;
            std::string el;
            strStream >> el;
            std::map< std::string, Factory* >::iterator curFactory;
            curFactory = factoryMap.find(vectorType);
            if (curFactory == factoryMap.end()) {
                throw std::invalid_argument("Error! Wrong type of+ vector in file input.txt!\n");
            }
            // std::cout<<"!"<<el<<"! ";
            Vector* curVect = curFactory->second->Create(fileName, el);
            vectorVector.push_back(curVect);
        }
        inputFile.close();
        unsigned int start_time =  clock();
        VectorHori v=(*vectorVector[0]+*vectorVector[1]);
        unsigned int end_time = clock();
        std::cout<<" : "<<" : "<<end_time - start_time<<" : "<<" : "<<std::endl;
        v.Output();
        return 0;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
