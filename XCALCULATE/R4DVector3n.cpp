//
//  R4DVector3n.cpp
//  Revolver4DMathEngine
//
//  Created by Harold Serrano on 3/2/16.
//  Copyright © 2016 haroldserrano.com. All rights reserved.
//

#include "R4DVector3n.h"
#include "R4DQuaternion.h"
#include "Constants.h"

namespace R4DEngine {
    
#pragma mark-constructor
    
    R4DVector3n::R4DVector3n():x(0.0),y(0.0),z(0.0){};
    
    R4DVector3n::R4DVector3n(float uX,float uY,float uZ):x(uX),y(uY),z(uZ){}
    
#pragma mark-destructor
    R4DVector3n::~R4DVector3n(){}
    
    
#pragma mark-copy constructor   
    
    R4DVector3n::R4DVector3n(const R4DVector3n& v):x(v.x),y(v.y),z(v.z){}
    
    R4DVector3n& R4DVector3n::operator=(const R4DVector3n& v){
        
        x=v.x;
        y=v.y;
        z=v.z;
        
        return *this;
        
    }
    
#pragma mark-add
    
    void R4DVector3n::operator+=(const R4DVector3n& v){
        
        x+=v.x;
        y+=v.y;
        z+=v.z;
        
    }
    
    R4DVector3n R4DVector3n::operator+(const R4DVector3n& v)const{
        
        
        return R4DVector3n(x+v.x,y+v.y,z+v.z);
    }
    
#pragma mark-subtract
    void R4DVector3n::operator-=(const R4DVector3n& v){
        
        x-=v.x;
        y-=v.y;
        z-=v.z;
    }
    
    R4DVector3n R4DVector3n::operator-(const R4DVector3n& v)const{
        
        return R4DVector3n(x-v.x,y-v.y,z-v.z);
    }
    
#pragma mark-multiply scalar
    void R4DVector3n::operator*=(const float s){
        
        x*=s;
        y*=s;
        z*=s;
        
    }
    
    R4DVector3n R4DVector3n::operator*(const float s) const{
        
        return R4DVector3n(s*x,s*y,s*z);
    }
    
    
#pragma mark-divide by scalar
    //divide by scalar
    void R4DVector3n::operator /=(const float s){
        
        x=x/s;
        y=y/s;
        z=z/s;
    }
    
    R4DVector3n R4DVector3n::operator/(const float s)const{
        
        return R4DVector3n(x/s,y/s,z/s);
    }
    
#pragma mark-dot product
    float R4DVector3n::operator*(const R4DVector3n& v) const{
        
        return x*v.x+y*v.y+z*v.z;
        
    }
    
    float R4DVector3n::dot(const R4DVector3n& v) const{
        
        return x*v.x+y*v.y+z*v.z;
        
    }
    
#pragma mark-Angle between vectors
    
    float R4DVector3n::angle(const R4DVector3n& v){
        
        float theta;
        
        R4DVector3n u=v;
        R4DVector3n m=*this;
        
        theta=dot(u)/(m.magnitude()*u.magnitude());
        
        theta=RadToDegrees(acos(theta));
        
        return theta;
        
    }
    
#pragma mark-cross product
    R4DVector3n R4DVector3n::cross(const R4DVector3n& v) const{
        
        return R4DVector3n(y*v.z-z*v.y,
                           z*v.x-x*v.z,
                           x*v.y-y*v.x);
        
    }
    
    void R4DVector3n::operator %=(const R4DVector3n& v){
        
        *this=cross(v);
        
    }
    
    R4DVector3n R4DVector3n::operator %(const R4DVector3n& v) const{
        
        return R4DVector3n(y*v.z-z*v.y,
                           z*v.x-x*v.z,
                           x*v.y-y*v.x);
    }
    
#pragma mark-normalize
    void R4DVector3n::normalize(){
        
        float mag=std::sqrt(x*x+y*y+z*z);
        
        if (mag>0.0f) {
            
            //normalize it
            float oneOverMag=1.0f/mag;
            
            x=x*oneOverMag;
            y=y*oneOverMag;
            z=z*oneOverMag;
            
        }
        
    }
    
#pragma mark-conjugate
    void R4DVector3n::conjugate(){
        
        x=-1*x;
        y=-1*y;
        z=-1*z;
        
    }
    
#pragma mark-magnitude
    
    float R4DVector3n::magnitude(){
        
        float magnitude=std::sqrt(x*x+y*y+z*z);
        
        return magnitude;
        
    }
    
    float R4DVector3n::magnitudeSquare(){
        
        float magnitude=x*x+y*y+z*z;
        
        return magnitude;
    }
    
    
#pragma mark-clear
    //clear
    void R4DVector3n::zero(){
        x=0;
        y=0;
        z=0;
    }
    
    void R4DVector3n::absolute(){
        
        x=std::abs(x);
        y=std::abs(y);
        z=std::abs(z);
        
    }
    
#pragma mark-Rotate a vector about an angle using quaternions
    
    R4DVector3n R4DVector3n::rotateVectorAboutAngleAndAxis(float uAngle, R4DVector3n& uAxis){
        
        //convert our vector to a pure quaternion
        
        R4DQuaternion p(0,(*this));
        
        //normalize the axis
        uAxis.normalize();
        
        //create the real quaternion
        R4DQuaternion q(uAngle,uAxis);
        
        //convert quaternion to unit norm quaternion
        q.convertToUnitNormQuaternion();
        
        R4DQuaternion qInverse=q.inverse();
        
        R4DQuaternion rotatedVector=q*p*qInverse;
        
        return rotatedVector.v;
        
    }
 
    
#pragma mark-show
    void R4DVector3n::show(){
        
        std::cout<<"("<<x<<","<<y<<","<<z<<")"<<std::endl;
    }
    
    
    void R4DVector3n::negate(){
        
        x=-1*x;
        y=-1*y;
        z=-1*z;
    }
    
}