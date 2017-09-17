/**********
 * NAME: Morgan Campbell
 * DATE: 9/10/17
 * PROJECT: Assignment 1
 * EMAIL: up85972@umbc.edu
 * DESCRIPTION: This program takes files containing bone forest and pose informa
 * tion, and outputs the locations of the joints in the kinematic hierarchy.
**********/

#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include "slVector.H"

//Bone, represents single joint on model
//constructs with weight, parent, and xyz-to-parent offsets
class Joint
{
    private:
        int weight, parent;
        double xoff, yoff, zoff;
        
    public:
        Joint();
        Joint(int w, int p, double x, double y, double z)
            : weight(w),
             parent(p),
             xoff(x),
             yoff(y), 
             zoff(z)
        {
        }
};

//Class to hold kinematic hierarchy
//
class KH{

    public:
        KH(char *bf, char *pf, char *out);
        std::vector<std::vector<double> > poses;
        std::vector<Joint> bones;
    private:
        int x; 
        
};


void readInputs(char *bf, char *pf, std::vector<std::vector<double> > &mat, std::vector<Joint> bones) {

    //read poses from dmat file
    std::ifstream in(pf, std::ios::in);
    int cols, rows;
    
    in>>cols>>rows;
    
    std::cout << cols << " " << rows << std::endl;
    
    mat.resize(cols);
    
    std::cout << mat.size();
    
    for(int i = 0; i < cols; i++) {
    
        mat[i].resize(rows);
        for(int j = 0; j < rows; j++) {
        
            in>>mat[i][j];
        }
    }
    
    //read model from bf file
    std::ifstream bin(bf, std::ios::in);
    int w, p;
    double x, y, z;
    
    while(bin != NULL) {
        bin>>w>>p>>x>>y>>z;
        
        std::cout << x  << " " << y << " " << z << std::endl;
        
        Joint nxt = Joint(w, p, x, y, z);
        bones.push_back(nxt);
    }
    
}

//Default bone constructor
Joint::Joint() {
    return;
}

KH::KH(char *bf, char *pf, char *out) {
    readInputs(bf, pf, poses, bones);
    

}

int main(int argc, char *argv[]){
    std::cout << *argv << std::endl;
    KH kine = KH(argv[1], argv[2], argv[3]);
   
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 69; j++) {
        
        }
    }
    return 0;
}


































