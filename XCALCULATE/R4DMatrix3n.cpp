//
//  R4DMatrix3n.cpp
//  Revolver4DMathEngine
//
//  Created by Harold Serrano on 3/10/16.
//  Copyright © 2016 haroldserrano.com. All rights reserved.
//

#include "R4DMatrix3n.h"
#include "Constants.h"

namespace R4DEngine {
    

#pragma mark-constructor
    
    R4DMatrix3n::R4DMatrix3n(){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        
        for (int i=0; i<9; i++) {
            matrixData[i]=0.0f;
        }
        
        matrixData[0]=matrixData[4]=matrixData[8]=1.0f;
        
    };
    
 
    R4DMatrix3n::R4DMatrix3n(float m0,float m3,float m6,float m1,float m4,float m7,float m2,float m5,float m8){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        matrixData[0]=m0;
        matrixData[3]=m3;
        matrixData[6]=m6;
        
        matrixData[1]=m1;
        matrixData[4]=m4;
        matrixData[7]=m7;
        
        matrixData[2]=m2;
        matrixData[5]=m5;
        matrixData[8]=m8;
        
    };
    
#pragma mark-copy constructor
    R4DMatrix3n& R4DMatrix3n::operator=(const R4DMatrix3n& value){
        
        for (int i=0; i<9; i++) {
            matrixData[i]=value.matrixData[i];
        }
        
        return *this;
    };
   
    
#pragma mark-destructor
    R4DMatrix3n::~R4DMatrix3n(){
    
    }
    
    
#pragma mark-matrix addition
    R4DMatrix3n R4DMatrix3n::operator+(const R4DMatrix3n &m) const{
        
        R4DMatrix3n n;
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        n.matrixData[0]=matrixData[0]+m.matrixData[0];
        n.matrixData[3]=matrixData[3]+m.matrixData[3];
        n.matrixData[6]=matrixData[6]+m.matrixData[6];
        
        n.matrixData[1]=matrixData[1]+m.matrixData[1];
        n.matrixData[4]=matrixData[4]+m.matrixData[4];
        n.matrixData[7]=matrixData[7]+m.matrixData[7];
        
        n.matrixData[2]=matrixData[2]+m.matrixData[2];
        n.matrixData[5]=matrixData[5]+m.matrixData[5];
        n.matrixData[8]=matrixData[8]+m.matrixData[8];
        
        return n;
    }
    
    void R4DMatrix3n::operator+=(const R4DMatrix3n &m){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        matrixData[0]+=m.matrixData[0];
        matrixData[3]+=m.matrixData[3];
        matrixData[6]+=m.matrixData[6];
        
        matrixData[1]+=m.matrixData[1];
        matrixData[4]+=m.matrixData[4];
        matrixData[7]+=m.matrixData[7];
        
        matrixData[2]+=m.matrixData[2];
        matrixData[5]+=m.matrixData[5];
        matrixData[8]+=m.matrixData[8];
        
    }
    
#pragma mark-matrix scalar multiplication
    R4DMatrix3n R4DMatrix3n::operator*(const float s) const{
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        R4DMatrix3n n;
        
        n.matrixData[0]=matrixData[0]*s;
        n.matrixData[3]=matrixData[3]*s;
        n.matrixData[6]=matrixData[6]*s;
        
        n.matrixData[1]=matrixData[1]*s;
        n.matrixData[4]=matrixData[4]*s;
        n.matrixData[7]=matrixData[7]*s;
        
        n.matrixData[2]=matrixData[2]*s;
        n.matrixData[5]=matrixData[5]*s;
        n.matrixData[8]=matrixData[8]*s;
        
        return n;
        
    }
    
    void R4DMatrix3n::operator*=(const float s){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        matrixData[0]*=s;
        matrixData[3]*=s;
        matrixData[6]*=s;
        
        matrixData[1]*=s;
        matrixData[4]*=s;
        matrixData[7]*=s;
        
        matrixData[2]*=s;
        matrixData[5]*=s;
        matrixData[8]*=s;
        
    }
    
    
#pragma mark-vector transformation
   
    R4DVector3n R4DMatrix3n::operator*(const R4DVector3n & v) const{
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        return R4DVector3n(matrixData[0]*v.x+matrixData[3]*v.y+matrixData[6]*v.z,
                           matrixData[1]*v.x+matrixData[4]*v.y+matrixData[7]*v.z,
                           matrixData[2]*v.x+matrixData[5]*v.y+matrixData[8]*v.z);
        
    }
    
    
    R4DVector3n R4DMatrix3n::transformVectorByMatrix(const R4DVector3n& v) const{
        
        return (*this)*v;
    }
    
#pragma mark-matrix multiplication
  
    R4DMatrix3n R4DMatrix3n::operator*(const R4DMatrix3n& m) const{
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        
        
        return R4DMatrix3n(matrixData[0]*m.matrixData[0]+ matrixData[3]*m.matrixData[1]+matrixData[6]*m.matrixData[2],
                           matrixData[0]*m.matrixData[3]+ matrixData[3]*m.matrixData[4]+matrixData[6]*m.matrixData[5],
                           matrixData[0]*m.matrixData[6]+ matrixData[3]*m.matrixData[7]+matrixData[6]*m.matrixData[8],
                           
                           matrixData[1]*m.matrixData[0]+ matrixData[4]*m.matrixData[1]+matrixData[7]*m.matrixData[2],
                           matrixData[1]*m.matrixData[3]+ matrixData[4]*m.matrixData[4]+matrixData[7]*m.matrixData[5],
                           matrixData[1]*m.matrixData[6]+ matrixData[4]*m.matrixData[7]+matrixData[7]*m.matrixData[8],
                           
                           matrixData[2]*m.matrixData[0]+ matrixData[5]*m.matrixData[1]+matrixData[8]*m.matrixData[2],
                           matrixData[2]*m.matrixData[3]+ matrixData[5]*m.matrixData[4]+matrixData[8]*m.matrixData[5],
                           matrixData[2]*m.matrixData[6]+ matrixData[5]*m.matrixData[7]+matrixData[8]*m.matrixData[8]);
        
    }
    
    
    void R4DMatrix3n::operator*=(const R4DMatrix3n& m){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        float t1;
        float t2;
        float t3;
        
        t1=matrixData[0]*m.matrixData[0]+ matrixData[3]*m.matrixData[1]+matrixData[6]*m.matrixData[2];
        t2=matrixData[0]*m.matrixData[3]+ matrixData[3]*m.matrixData[4]+matrixData[6]*m.matrixData[5];
        t3=matrixData[0]*m.matrixData[6]+ matrixData[3]*m.matrixData[7]+matrixData[6]*m.matrixData[8];
        
        matrixData[0]=t1;
        matrixData[3]=t2;
        matrixData[6]=t3;
        
        t1=matrixData[1]*m.matrixData[0]+ matrixData[4]*m.matrixData[1]+matrixData[7]*m.matrixData[2];
        t2=matrixData[1]*m.matrixData[3]+ matrixData[4]*m.matrixData[4]+matrixData[7]*m.matrixData[5];
        t3=matrixData[1]*m.matrixData[6]+ matrixData[4]*m.matrixData[7]+matrixData[7]*m.matrixData[8];
        
        matrixData[1]=t1;
        matrixData[4]=t2;
        matrixData[7]=t3;
        
        
        t1=matrixData[2]*m.matrixData[0]+ matrixData[5]*m.matrixData[1]+matrixData[8]*m.matrixData[2];
        t2=matrixData[2]*m.matrixData[3]+ matrixData[5]*m.matrixData[4]+matrixData[8]*m.matrixData[5];
        t3=matrixData[2]*m.matrixData[6]+ matrixData[5]*m.matrixData[7]+matrixData[8]*m.matrixData[8];
        
        matrixData[2]=t1;
        matrixData[5]=t2;
        matrixData[8]=t3;
        
    }
    
#pragma mark-matrix identity
    
    void R4DMatrix3n::setMatrixAsIdentityMatrix(){
        
        for (int i=0; i<9; i++) {
            matrixData[i]=0.0f;
        }
        
        matrixData[0]=matrixData[4]=matrixData[8]=1.0f;
        
    }
    
    
#pragma mark-matrix inverse
    
    void R4DMatrix3n::setMatrixAsInverseOfGivenMatrix(const R4DMatrix3n& m){
     
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        
        float t1=m.matrixData[0]*m.matrixData[4];
        float t2=m.matrixData[0]*m.matrixData[7];
        float t3=m.matrixData[3]*m.matrixData[1];
        float t4=m.matrixData[6]*m.matrixData[1];
        float t5=m.matrixData[3]*m.matrixData[2];
        float t6=m.matrixData[6]*m.matrixData[2];
        
        //calculate the determinant
        
        float det=(t1*m.matrixData[8]-t2*m.matrixData[5]-t3*m.matrixData[8]+t4*m.matrixData[5]+t5*m.matrixData[7]-t6*m.matrixData[4]);
        
        //make sure the det is non-zero
        if (det==0.0) return;
        
        float invd=1.0f/det;
        
        float m0=(m.matrixData[4]*m.matrixData[8]-m.matrixData[7]*m.matrixData[5])*invd;
        float m3=-(m.matrixData[3]*m.matrixData[8]-m.matrixData[6]*m.matrixData[5])*invd;
        
        float m6=(m.matrixData[3]*m.matrixData[7]-m.matrixData[6]*m.matrixData[4])*invd;
        
        float m1=-(m.matrixData[1]*m.matrixData[8]-m.matrixData[7]*m.matrixData[2])*invd;
        
        float m4=(m.matrixData[0]*m.matrixData[8]-t6)*invd;
        
        float m7=-(t2-t4)*invd;
        
        float m2=(m.matrixData[1]*m.matrixData[5]-m.matrixData[4]*m.matrixData[2])*invd;
        
        float m5=-(m.matrixData[0]*m.matrixData[5]-t5)*invd;
        
        float m8=(t1-t3)*invd;
        
        matrixData[0]=m0;
        matrixData[3]=m3;
        matrixData[6]=m6;
        
        matrixData[1]=m1;
        matrixData[4]=m4;
        matrixData[7]=m7;
        
        matrixData[2]=m2;
        matrixData[5]=m5;
        matrixData[8]=m8;
    }
    
    
    R4DMatrix3n R4DMatrix3n::getInverseOfMatrix() const{
        
        R4DMatrix3n result;
        result.setMatrixAsInverseOfGivenMatrix(*this);
        return result;
    }
    

    void R4DMatrix3n::invertMatrix(){
        
        setMatrixAsInverseOfGivenMatrix(*this);
    }
    
#pragma mark-matrix determinant
    
    float R4DMatrix3n::getMatrixDeterminant() const{
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        float t1=matrixData[0]*matrixData[4];
        float t2=matrixData[0]*matrixData[7];
        float t3=matrixData[3]*matrixData[1];
        float t4=matrixData[6]*matrixData[1];
        float t5=matrixData[3]*matrixData[2];
        float t6=matrixData[6]*matrixData[2];
        
        //calculate the determinant
        
        float det=(t1*matrixData[8]-t2*matrixData[5]-t3*matrixData[8]+t4*matrixData[5]+t5*matrixData[7]-t6*matrixData[4]);
        
        return det;
    }
    
#pragma mark-matrix transpose
    
    void R4DMatrix3n::setMatrixAsTransposeOfGivenMatrix(const R4DMatrix3n& m){
        
        //3x3 Matrix
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        //3x3 transpose
        //  0   1   2
        //  3   4   5
        //  6   7   8
        
        matrixData[0]=m.matrixData[0];
        matrixData[3]=m.matrixData[1];
        matrixData[6]=m.matrixData[2];
        
        matrixData[1]=m.matrixData[3];
        matrixData[4]=m.matrixData[4];
        matrixData[7]=m.matrixData[5];
        
        matrixData[2]=m.matrixData[6];
        matrixData[5]=m.matrixData[7];
        matrixData[8]=m.matrixData[8];
        
    }
    
    
    R4DMatrix3n R4DMatrix3n::getTransposeOfMatrix() const{
        
        R4DMatrix3n result;
        result.setMatrixAsTransposeOfGivenMatrix(*this);
        return result;
        
    }
    
    
#pragma mark-invert and transpose the matrix
    
    void R4DMatrix3n::invertAndTransposeMatrix(){
     
        //3x3 Matrix
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        //3x3 transpose
        //  0   1   2
        //  3   4   5
        //  6   7   8
        
        //find the deteminant
        
        float det=matrixData[0]*(matrixData[4]*matrixData[8]-matrixData[5]*matrixData[7])-matrixData[3]*(matrixData[1]*matrixData[8]-matrixData[2]*matrixData[7])+ matrixData[6]*(matrixData[1]*matrixData[5]-matrixData[2]*matrixData[4]);
        
        //get the transpose of the original matrix
        R4DMatrix3n transpose;
        
        transpose.matrixData[0]=matrixData[0];
        transpose.matrixData[1]=matrixData[3];
        transpose.matrixData[2]=matrixData[6];
        
        transpose.matrixData[3]=matrixData[1];
        transpose.matrixData[4]=matrixData[4];
        transpose.matrixData[5]=matrixData[7];
        
        transpose.matrixData[6]=matrixData[2];
        transpose.matrixData[7]=matrixData[5];
        transpose.matrixData[8]=matrixData[8];
        
        //3x3 Matrix
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        //find the adjoing and divide it by the det(M)
        float m11,m12,m13,m21,m22,m23,m31,m32,m33;
        
        m11=+(transpose.matrixData[4]*transpose.matrixData[8]-transpose.matrixData[5]*transpose.matrixData[7])/det;
        m12=-(transpose.matrixData[1]*transpose.matrixData[8]-transpose.matrixData[2]*transpose.matrixData[7])/det;
        m13=+(transpose.matrixData[1]*transpose.matrixData[5]-transpose.matrixData[2]*transpose.matrixData[4])/det;
        
        m21=-(transpose.matrixData[3]*transpose.matrixData[8]-transpose.matrixData[5]*transpose.matrixData[6])/det;
        m22=+(transpose.matrixData[0]*transpose.matrixData[8]-transpose.matrixData[2]*transpose.matrixData[6])/det;
        m23=-(transpose.matrixData[0]*transpose.matrixData[5]-transpose.matrixData[2]*transpose.matrixData[3])/det;
        
        m31=+(transpose.matrixData[3]*transpose.matrixData[7]-transpose.matrixData[4]*transpose.matrixData[6])/det;
        m32=-(transpose.matrixData[0]*transpose.matrixData[7]-transpose.matrixData[1]*transpose.matrixData[6])/det;
        m33=+(transpose.matrixData[0]*transpose.matrixData[4]-transpose.matrixData[1]*transpose.matrixData[3])/det;
        
        R4DMatrix3n preResult;
        
        preResult.matrixData[0]=m11;
        preResult.matrixData[1]=m21;
        preResult.matrixData[2]=m31;
        
        preResult.matrixData[3]=m12;
        preResult.matrixData[4]=m22;
        preResult.matrixData[5]=m32;
        
        preResult.matrixData[6]=m13;
        preResult.matrixData[7]=m23;
        preResult.matrixData[8]=m33;
        
        //transpose the matrix
        //3x3 Matrix
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        //3x3 transpose
        //  0   1   2
        //  3   4   5
        //  6   7   8
        
        matrixData[0]=preResult.matrixData[0];
        matrixData[1]=preResult.matrixData[3];
        matrixData[2]=preResult.matrixData[6];
        
        matrixData[3]=preResult.matrixData[1];
        matrixData[4]=preResult.matrixData[4];
        matrixData[5]=preResult.matrixData[7];
        
        matrixData[6]=preResult.matrixData[2];
        matrixData[7]=preResult.matrixData[5];
        matrixData[8]=preResult.matrixData[8];
    }
    
#pragma mark-Transform matrix about axis

    void R4DMatrix3n::makeRotationMatrixAboutXAxisByAngle(float uAngle){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        uAngle=DegreesToRad(uAngle);
        
        (*this).setMatrixAsIdentityMatrix();
        
        R4DMatrix3n m(1.0,0.0,0.0,
                      0.0,cos(uAngle),-sin(uAngle),
                      0.0,sin(uAngle),cos(uAngle));
        
        *this=m*(*this);
        
    }
    
    void R4DMatrix3n::makeRotationMatrixAboutYAxisByAngle(float uAngle){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        uAngle=DegreesToRad(uAngle);
        (*this).setMatrixAsIdentityMatrix();
        
        R4DMatrix3n m(cos(uAngle),0.0,sin(uAngle),
                      0.0,1.0,0.0,
                      -sin(uAngle),0.0,cos(uAngle));
        
        *this=m*(*this);
        
    }
    
    void R4DMatrix3n::makeRotationMatrixAboutZAxisByAngle(float uAngle){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        uAngle=DegreesToRad(uAngle);
        (*this).setMatrixAsIdentityMatrix();
        
        R4DMatrix3n m(cos(uAngle),-sin(uAngle),0.0,
                      sin(uAngle),cos(uAngle),0.0,
                      0.0,0.0,1.0);
        
        *this=m*(*this);
    }
    
#pragma mark-transform matrix by axis
    
    void R4DMatrix3n::transformMatrixAboutXAxisByAngle(float uAngle){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        uAngle=DegreesToRad(uAngle);
        
        R4DMatrix3n m(1.0,0.0,0.0,
                      0.0,cos(uAngle),-sin(uAngle),
                      0.0,sin(uAngle),cos(uAngle));
        
        *this=m*(*this);
        
    }
    
    void R4DMatrix3n::transformMatrixAboutYAxisByAngle(float uAngle){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        uAngle=DegreesToRad(uAngle);
        
        R4DMatrix3n m(cos(uAngle),0.0,sin(uAngle),
                      0.0,1.0,0.0,
                      -sin(uAngle),0.0,cos(uAngle));
        
        *this=m*(*this);
        
        
    }
    
    void R4DMatrix3n::transformMatrixAboutZAxisByAngle(float uAngle){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        uAngle=DegreesToRad(uAngle);
        
        R4DMatrix3n m(cos(uAngle),-sin(uAngle),0.0,
                      sin(uAngle),cos(uAngle),0.0,
                      0.0,0.0,1.0);
        
        *this=m*(*this);
    }
    
    
#pragma mark-debug
    void R4DMatrix3n::show(){
        
        // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
        //	0	3	6
        //	1	4	7
        //	2	5	8
        
        std::cout<<"["<<matrixData[0]<<","<<matrixData[3]<<","<<matrixData[6]<<","<<std::endl;
        std::cout<<matrixData[1]<<","<<matrixData[4]<<","<<matrixData[7]<<","<<std::endl;
        std::cout<<matrixData[2]<<","<<matrixData[5]<<","<<matrixData[8]<<"]"<<std::endl;
    }
    
}