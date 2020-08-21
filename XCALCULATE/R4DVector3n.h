//
//  R4DVector3n.hpp
//  Revolver4DMathEngine
//
//  Created by Harold Serrano on 3/2/16.
//  Copyright © 2016 haroldserrano.com. All rights reserved.
//

#ifndef R4DVector3n_hpp
#define R4DVector3n_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>

namespace R4DEngine {
    
    class R4DVector3n{
        
    private:
        
    public:
        
        /*!
         *  @brief  x vector component
         */
        float x;
        
        /*!
         *  @brief  y vector component
         */
        
        float y;
        
        /*!
         *  @brief  z vector component
         */
        
        float z;
        
#pragma mark-constructors
        
        /**
         @brief  Constructor to create a 3D vector with zero vector components.
         
         */
        R4DVector3n();
        
        
        /**
         @brief  Constructor to create a 3D vector with x,y, and z components
         
         @param uX x component
         @param uY y component
         @param uZ z component
         
         @return Creates a vector with the given x,y and z components
         
         */
        R4DVector3n(float uX,float uY,float uZ);

#pragma mark-destructors        
        /**
         @brief  3D vector desctructor
         
         */
        ~R4DVector3n();
        
#pragma mark-copy constructors
        
        /*!
         *  @brief  Copy constructor for 3D vector
         *
         *  @param a 3D vector to copy
         *
         *  @return Copies the values of the vector
         */
        R4DVector3n(const R4DVector3n& v);
        
        /*!
         *  @brief  Copy constructor for 3D vector
         *
         *  @param a 3D vector to copy
         *
         *  @return Copies the values of the vector
         *
         */
        R4DVector3n& operator=(const R4DVector3n& v);
        
        
#pragma mark-add
        
        /*!
         *  @brief  It calculates the addition of two vectors.
         *
         *  @param v Vector to add.
         *
         *  @return Resultant of two vectors.
         *
         */
        void operator+=(const R4DVector3n& v); //add vectors
        
        /*!
         *  @brief  Calculates the addition of two vectors.
         *
         *  @param v 3D vector to add
         *
         *  @return Returns a third vector representing the addition of two 3D vectors
         *
         */
        R4DVector3n operator+(const R4DVector3n& v)const; //add vectors
        
#pragma mark-subraction
        
        /*!
         *  @brief  Calculates the subtraction of two vectors.
         *
         *  @param v 3D vector to subtract
         *
         *  @return Subtraction result of two vectors
         *
         */
        void operator-=(const R4DVector3n& v); //subtract vectors
        
        /*!
         *  @brief  Calculates the subtraction of two vectors.
         *
         *  @param v 3D vector to subtract
         *
         *  @return Returns a third vector representing the subtraction of two 3D vectors
         *
         */
        
        R4DVector3n operator-(const R4DVector3n& v)const; //subtract vectors
        
#pragma mark-multiplication
        
        /*!
         *  @brief  Multiply vector by scalar
         *
         *  @param s Scalar
         *
         *  @return Product of multiplication
         *
         */
        void operator*=(const float s);
        
        /*!
         *  @brief  Multiply vector by scalar
         *
         *  @param s Scalar
         *
         *  @return Vector representing product
         *
         */
        R4DVector3n operator*(const float s)const;
        
        
#pragma mark-division
        
        /*!
         *  @brief  Division of vector by scalar
         *
         *  @param s Scalar
         *
         *  @return Quotient of division
         *
         */
        void operator /=(const float s);
        
        /*!
         *  @brief  Division of vector by scalar
         *
         *  @param s Scalar
         *
         *  @return Quotient of division
         *
         */
        R4DVector3n operator/(const float s)const;
        
#pragma mark-dot product
        
        /*!
         *  @brief  Calculate dot product
         *
         *  @param v Vector
         *
         *  @return Dot product result
         *
         */
        float operator*(const R4DVector3n& v) const;
        
        /*!
         *  @brief  Calculate dot product
         *
         *  @param v Vector
         *
         *  @return Dot product result
         *
         */
        float dot(const R4DVector3n& v) const;
        
        /*!
         *  @brief  Calculates the angle between vectors
         *
         *  @param v Vector
         *
         *  @return Returns the angle between vectors in degrees
         *
         */
        float angle(const R4DVector3n& v);
        
#pragma mark-cross product
        
        /*!
         *  @brief  Calculate cross product
         *
         *  @param v Vector
         *
         *  @return Cross product result
         *
         */
        void operator %=(const R4DVector3n& v);
        
        /*!
         *  @brief  Calculate cross product
         *
         *  @param v Vector
         *
         *  @return Cross product result
         *
         */
        R4DVector3n operator %(const R4DVector3n& v) const;
        
        /*!
         *  @brief  Calculate cross product
         *
         *  @param v Vector
         *
         *  @return Cross product result
         *
         */
        
        R4DVector3n cross(const R4DVector3n& v) const;
        
        /*!
         *  @brief  Conjugate the vector
         *
         */
        void conjugate();
        
        /*!
         *  @brief  Normalize the vector
         *
         */
        void normalize();
        
        /*!
         *  @brief  Calculate magnitude of vector
         *
         *  @return Magnitude value
         *
         */
        
        float magnitude();
        
        /*!
         *  @brief  Calculate the magnitude square of vector
         *
         *  @return Magnitude squared value
         *
         */
        float magnitudeSquare();
        
        
        /*!
         *  @brief  Convert vector to a zero vector
         *
         */
        void zero();
        
        /*!
         *  @brief  Calculate absolute value of vector
         *
         */
        void absolute();
        
        /**
         @brief Rotate a vector about an angle using quaternions
         
         @param uAngle angle to rotate
         @param uAxis  axis to rotate about
         
         @return Vector rotation
         */
        R4DVector3n rotateVectorAboutAngleAndAxis(float uAngle, R4DVector3n& uAxis);
        
        /*!
         *  @brief  Print vector components
         *
         */
        
        void show();
        
        //Negate all components
        void negate();
        

    };
    
}

#endif /* R4DVector3n_hpp */
