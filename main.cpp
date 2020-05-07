#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include "omp.h"
//#include <parallel.h>

#include "Vector.hpp"
//#include "Vector.cpp"
#include "VectorHori.hpp"
#include "VectorHori.cpp"
#include "VectorVert.hpp"
//#include "VectorVert.cpp"
#include "Factory.hpp"
#include "FactoryHori.hpp"
#include "FactoryVert.hpp"

using namespace VECTOR_HORI_VERT;

int main() {

  try {
      VectorHori operator+(Vector& first, Vector& other);

    int counter=300;


    {
        //# pragma omp for
        //for (int ii=0;ii<counter;ii++){
            std::map < std::string, Factory* > factoryMap;
            //factoryMap["Hori"] = std::make_unique<FactoryHori<EL_TYPE>>();    // unexpectedly make_unique() is C++14
            factoryMap["Hori"] = new FactoryHori;
            //factoryMap["Vert"] = std::make_unique<FactoryVert<EL_TYPE>>();
            factoryMap["Vert"] = new FactoryVert;

            /* smart pointer - shared_ptr */
            std::vector< Vector* > vectorVector;
            const std::string inputFileName = "input.txt";

            /*
            * Format of input file is:
            * Hori file1.txt 1 2 3
            * Vert file2.txt 8 9 10
            */

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
              //std::cout << vectorType << std::endl;
              std::string fileName;
              strStream >> fileName;
              int el;
              strStream >> el;
              std::map< std::string, Factory* >::iterator curFactory;
              curFactory = factoryMap.find(vectorType);
              if (curFactory == factoryMap.end()) {
                throw std::invalid_argument("Error! Wrong type of+ vector in file input.txt!\n");
              }

              Vector* curVect = curFactory->second->Create(fileName, el);
              vectorVector.push_back(curVect);
            }

            inputFile.close();
            VectorVert v=(*vectorVector[0]+*vectorVector[1]);
            v.Output();
            /* range-based loop
            for(int i=0;i<vectorVector.size();i++){
                vectorVector[i]->Output();
            }*/

        //}
    }
    return 0;
  }

  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
