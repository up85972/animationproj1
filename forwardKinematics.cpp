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
#include <string.h>
#include <sstream>
#include "slVector.H"
#include "slMatrix.H"

//Bone, represents single joint on model
//constructs with weight, parent, and xyz-to-parent offsets
class Joint{
    public:
        Joint();
        Joint(int w, int p, double x, double y, double z)
            : weight(w),
             parent(p),
             xoff(x),
             yoff(y), 
             zoff(z),
             pos(x, y, z)
        {
        }
        SlVector3 pos;
        SlVector3 calcPos(std::vector<Joint> bones, int rot);
        int weight, parent;
        double xoff, yoff, zoff;
};


//Class to hold kinematic hierarchy
//
class KH{

    public:
        KH(char *bf, char *pf);
        void printH();
        void createPose(char *out);
        SlMatrix3x3 calcT(int node);
        std::vector<std::vector<double> > poses;
        std::vector<Joint> localbones, worldbones;
        std::vector<SlVector3> eulA;
};

//
void readInputs(char *bf, char *pf, std::vector<std::vector<double> > &mat, std::vector<Joint> &bones) {

    //read poses from dmat file
    std::ifstream in(pf, std::ios::in);
    int cols, rows;
    in>>cols>>rows;
    
    mat.resize(cols);
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
    SlVector3 offset;
    
    while(bin != NULL) {
        bin>>w>>p>>x>>y>>z;
        bones.push_back(Joint(w, p, x, y, z));
    }
}


//Default bone constructor
Joint::Joint() {
    return;
}

//
KH::KH(char *bf, char *pf) {
    //get model and figures from cmd
    readInputs(bf, pf, poses, localbones);

    //initialize worldspace
    Joint temp;
    for(int i = 0; i < localbones.size(); i++) {
        temp = localbones[i];
        temp.pos = localbones[i].calcPos(localbones, 0);
        worldbones.push_back(temp);
    }
    
}

//Calculate worldspace coords for target joint
SlVector3 Joint::calcPos(std::vector<Joint> localbones, int rot) {
    if(this->parent == -1) {
        return this->pos;
    }
    
    return (this->pos + localbones[this->parent].calcPos(localbones, 0));
}

//print out kinematic hierarchy
void KH::printH() {

    for(int i = 0; i < worldbones.size(); i++) {
        std::cout << worldbones[i].pos << std::endl;
    }
}


//create files containing world-coordinate positions of model
void KH::createPose(char *out) {
    
    SlVector3 euler;
    SlMatrix3x3 transform;
    std::ofstream outF;
    char *fn = out;
    
    SlVector3 angle;
    //initialize pose vectors
    for(int i = 0; i < poses.size(); i++) {
        
        //initialize pose vectors
        
        
        eulA.resize(poses[i].size() / 3);
        
        fn[sizeof(out) + 1] = (char)i;
        std::cout << fn;
        outF.open(fn, std::ofstream::out);
        for(int j = 0; j < poses[i].size(); j++) {
            angle = SlVector3(poses[i][j], poses[i][j+1], poses[i][j+2]);
            angle *= M_PI / 180.0;
            eulA[j/3] = angle;
            std::cout << calcT(j/3);
            euler = worldbones[localbones[j/3].parent].pos + localbones[j/3].pos * calcT(j/3) ;
            
            outF << j/3 - 1 << " " << euler[0] << " " << euler[1] << " " 
                 << euler[2]<< std::endl;
            
            j += 2;
        }
    }
}

//Calculate rotations of target node, traversing parents
SlMatrix3x3 KH::calcT(int node) {
    
    SlVector3 mods;
    SlMatrix3x3 transform;
    //std::cout << eulA.size();
    if(localbones[node].parent == -1) { 
        mods = eulA[node];
        SlEulerAngToMatrixXYZ(mods, transform);
        
        return transform;
    }
    else {
        mods = eulA[node];
        SlEulerAngToMatrixXYZ(mods, transform);
        
        return (transform * calcT(localbones[node].parent));
    }
}

//
int main(int argc, char *argv[]){
    KH kine = KH(argv[1], argv[2]);
    
    kine.printH();
    
    kine.createPose(argv[3]);
    return 0;
}


































