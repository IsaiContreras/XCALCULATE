//
//  R4DQuaternion.hpp
//  Revolver4DMathEngine
//
//  Created by Harold Serrano on 3/21/16.
//  Copyright © 2016 haroldserrano.com. All rights reserved.
//

#ifndef R4DQuaternion_hpp
#define R4DQuaternion_hpp

#include <stdio.h>
#include "R4DVector3n.h"
#include "R4DMatrix3n.h"

namespace R4DEngine {
    
    class R4DQuaternion{
        
    public:
        
        /**
         *  Scalar
         */
        float s;
        
        /**
         *  Vector
         */
        R4DVector3n v;
        
        /**
         *  Constructor
         */
        R4DQuaternion();
        
        /**
         *  Constructor
         */
        R4DQuaternion(float uS,R4DVector3n& uV);
        
        
        /**
         *  Destructor
         */
        ~R4DQuaternion();
        
        /**
         *  Copy Constructor
         */
        R4DQuaternion(const R4DQuaternion & value);
        
        /**
         *  Copy Constructor
         */
        inline R4DQuaternion& operator=(const R4DQuaternion& value);
        
        /**
         @brief Addition
         
         @param q quaternion
         
         @return adds quaterions
         */
        void operator+=(const R4DQuaternion& q);
        
        
        /**
         @brief Addition
         
         @param q quaternion
         
         @return Quaternion addition
         */
        R4DQuaternion operator+(const R4DQuaternion& q)const;
        
        /**
         @brief Subtraction
         
         @param q quaterion
         
         @return quaternion subtraction
         */
        void operator-=(const R4DQuaternion& q);
        
        
        /**
         @brief Subtraction
         
         @param q quaternion
         
         @return quaternion difference
         */
        R4DQuaternion operator-(const R4DQuaternion& q)const;
        
        
        /**
         @brief Quaternion multiplication
         
         @param q quaternion
         
         @return Quaternion product
         */
        void operator*=(const R4DQuaternion& q);
        
        
        /**
         @brief Quaternion multiplication
         
         @param q quaternion
         
         @return Quaternion product
         */
        R4DQuaternion operator*(const R4DQuaternion& q)const;
        
        
        /**
         @brief Quaternion multiplication
         
         @param q quaternion
         
         @return quaternion product
         */
        R4DQuaternion multiply(const R4DQuaternion& q)const;
        
        
        /**
         @brief Quaternion-Vector multiplication
         
         @param uValue vector to multipy
         
         @return Quaternion product
         */
        R4DQuaternion operator*(const R4DVector3n& uValue)const;
        
        /**
         @brief Dot product
         
         @param q quaternion
         
         @return The dot product of two quaternions
         */
        float dot(R4DQuaternion& q);
        
        /**
         @brief Quaternion Scalar multiplication
         
         @param Value scalar
         
         @return Quaternion scalar product
         */
        void operator*=(const float value);
        
        /**
         @brief Quaternion Scalar multiplication
         
         @param value Value scalar
         
         @return Quaternion scalar product
         */
        R4DQuaternion operator*(const float value)const;
        
        /**
         @brief Norm of a quaternion
         
         @return Norm value of a quaternion
         */
        float norm();
        
        /**
         @brief Normalize(unit-norm) a quaterion
         */
        void normalize();
        
        /**
         @brief Special Unit-Norm form of quaternion
         */
        void convertToUnitNormQuaternion();
        
        /**
         @brief Conjugate
         
         @return Conjugate of a quaternion
         */
        R4DQuaternion conjugate();
        
        /**
         @brief Inverse
         
         @return Inverse of a quaternion
         */
        R4DQuaternion inverse();
        
        void inverse(R4DQuaternion& q);
        
        /**
         @brief Quaternion to Matrix
         
         @return Transforms the Quaternion to a Matrix
         */
        R4DMatrix3n transformQuaternionToMatrix3n();
        
        /**
         @brief Transforms euler angles to quaternion
         
         @param x x-angle
         @param y y-angle
         @param z z-angle
         */
        void transformEulerAnglesToQuaternion(float x,float y, float z);
        
        /**
         @brief Quaternion to Euler angle
         
         @return Transforms Quaternion to Euler angle
         */
        R4DVector3n transformQuaternionToEulerAngles();
        
        /**
         @brief Matrix to Quaternion
         
         @param uMatrix Transforms Matrix to Quaternion
         */
        void transformMatrix3nToQuaternion(R4DMatrix3n &uMatrix);
        
        /**
         @brief Prints Quaternion components
         */
        void show();
        
    };
    
}



#endif /* R4DQuaternion_hpp */
