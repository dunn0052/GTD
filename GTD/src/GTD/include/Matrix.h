#pragma once
#include <tuple>
#include <iostream>
#include <math.h>

/* Welcome to template heck.. */
namespace mat
{

    /* LET THE MACRO GAMES BEGIN */

#define CURRENT_ELEMENT mElements[m_index][n_index]

#define LOOP_M_ELEMENTS( OPERATION ) \
    for (size_t m_index = 0; m_index < this->m; m_index++)\
    {\
        OPERATION\
    }\

#define LOOP_N_ELEMENTS( OPERATION ) \
    for (size_t n_index = 0; n_index < this->n; n_index++)\
    {\
        OPERATION\
    }\

#define LOOP_ALL_ELEMENTS( OPERATION ) \
    do{\
        LOOP_M_ELEMENTS( LOOP_N_ELEMENTS( OPERATION ))\
    }while(false)

#define OPERATE_ALL_ELEMENTS( OPERATION ) LOOP_ALL_ELEMENTS( this->CURRENT_ELEMENT OPERATION )
#define PERFORM( OPERATION ) OPERATE_ALL_ELEMENTS( OPERATION; ); return *this; 

    template<typename T, size_t M, size_t N>
    class Matrix
    {
    protected:
        T mElements[M][N] = { 0 };

    public:
        const size_t m = M;
        const size_t n = N;

    public:

        Matrix() {};
        
        /* need to copy all elements individually */
       // Matrix(const T& ele) { memset(mElements, ele, sizeof(mElements)); }
        Matrix(const T elements[M][N]) { memcpy(mElements, elements, sizeof(mElements)); }
        Matrix(const std::array<T, M * N> elements) { memcpy(mElements, elements.data(), sizeof(mElements)); }
        ~Matrix() {};

        /* copy ops */
        Matrix(const Matrix& copy) { OPERATE_ALL_ELEMENTS(= copy.CURRENT_ELEMENT; ); }
        Matrix& operator =(const Matrix& copy) { OPERATE_ALL_ELEMENTS(= copy.CURRENT_ELEMENT; ); return *this; }
        Matrix& operator =(const T* elements) { memccpy(mElements, elements, sizeof(mElements)); }

        /* multi-dim accessor*/
        const T* operator [](const size_t& index) const
        {
            return mElements[index];
        }

        T& operator ()(const size_t& row, const size_t& column)
        {
            return mElements[row][column];
        }

        std::tuple<size_t, size_t> dim(void)
        {
            return std::tuple<size_t, size_t>(M, N);
        }

        size_t size(void)
        {
            return M * N;
        }

        /* op overloads */


        /* adds another matrix */
        Matrix& operator +=(const Matrix& rhs)
        {
            PERFORM(+= rhs.CURRENT_ELEMENT;);
        }
        
        Matrix& operator -=(const Matrix& rhs)
        {
            PERFORM(-= rhs.CURRENT_ELEMENT;);
        }

        /* operate a single element to all elements of mat */
        Matrix& operator +=(const T& ele)
        {
            PERFORM(+= ele;);
        }

        Matrix& operator -=(const T& ele)
        {
            PERFORM(-= ele;);
        }

        Matrix& operator *=(const T& ele)
        {
            PERFORM(*= ele;);
        }

        Matrix& operator /=(const T& ele)
        {
            PERFORM(/= ele;);
        }

        /* set all element values to an element  */
        Matrix& operator =(const T& ele)
        {
            PERFORM(= ele;);
        }

        /* functions */

        void print(void)
        {
            LOOP_M_ELEMENTS(LOOP_N_ELEMENTS(std::cout << '|' << CURRENT_ELEMENT; ) std::cout << '|' << std::endl;);
        }
};
    /* static matrix functions */

    template<typename T, size_t M, size_t N>
    static Matrix<T, M, N> operator + (const Matrix<T, M, N>& lhs, const Matrix<T, M, N>& rhs)
    {
        Matrix<T, M, N> sum(lhs);
        return sum += rhs;
    }


    template<typename T, size_t M, size_t N>
    static Matrix<T, M, N> operator - (const Matrix<T, M, N>& lhs, const Matrix<T, M, N>& rhs)
    {
        Matrix<T, M, N> sum(lhs);
        return sum -= rhs;
    }

    /* naive matrix multiplication implementation */
    template<typename T, size_t M, size_t N>
    static Matrix<T, M, N> operator * (const Matrix<T, M, N>& lhs, const Matrix<T, N, M>& rhs)
    {
        Matrix<T, M, N> product(0);
        for (size_t row = 0; row < M; row++)
        {
            for (size_t column = 0; column < N; column++)
            {
                for (size_t index = 0; index < M; index++)
                {
                    product[row][column] += lhs[index][column] * rhs[column][index];
                }
            }
        }
    }

    template <typename T, size_t M>
    class MatI : public Matrix<T, M, M>
    {
    public:
        MatI() { OPERATE_ALL_ELEMENTS(= n_index == m_index ? (T)1 : (T)0; ); }
        MatI(T ele) { OPERATE_ALL_ELEMENTS(= n_index == m_index ? ele : (T)0; ); }
        ~MatI() = default;
    };

    /* useful matrices */

    template <typename T, size_t N>
    using MatSquare = Matrix<T, N, N>;

    template <typename T>
    using Mat1 = MatSquare<T, 1>;

    template <typename T>
    using Mat2 = MatSquare<T, 2>;

    template <typename T>
    using Mat3 = MatSquare<T, 3>;

    template <typename T>
    using Mat4 = MatSquare<T, 4>;

    /* vectors */
#define VEC_ELE( INDEX ) this->mElements[0][INDEX]
#define VX VEC_ELE( 0 )
#define VY VEC_ELE( 1 )
#define VZ VEC_ELE( 2 )
#define CURRENT_VEC_ELE VEC_ELE(m_index)
#define LOOP_ALL_VEC_ELE( OPERATION ) LOOP_M_ELEMENTS( CURRENT_VEC_ELE OPERATION )

    template <class T, size_t M>
    class Vector : public Matrix<T, 1, M>
    {
    public:
        Vector() { memset(this->mElements, 0, sizeof(this->mElements)); }
        Vector(T elements[M])
        {
            memcpy(this->mElements, elements, sizeof(this->mElements));
        }

        T Norm(size_t p) const
        {
            T sum = pow(VX, p);
            for (size_t index = 1; index < M; index++)
            {
                sum += pow(VEC_ELE(index), p);
            }

            return pow(sum, 1 / p);
        }

        T Mag() const
        {
            return Norm(2);
        } const

        /* sometimes you can get away without the sqrt */
        T Mag2() const
        {
            T sum = VX * VX;
            for (size_t index = 1; index < M; index++)
            {
                sum += VEC_ELE(index) * VEC_ELE(index);
            }
            return sum;
        }

        Vector<T, M> Unit() const
        {
            T mag1 = 1 / Mag();
            T elements[M] = { 0 };
            LOOP_N_ELEMENTS(elements[n_index] = VEC_ELE(n_index) * mag1;);
            return Vector<T, M>(elements);

        }

        static T dot(Vector<T, M>& lhs, Vector<T, M>& rhs);

    };

    template <typename T>
    class Vec2 : public Vector<T, 2>
    {
    public:
        Vec2(const T& x_ele, const T& y_ele) { VX = x_ele; VY = y_ele; }
        Vec2() { VX = (T)0; VY = (T)0; }
        T x(void) const { return VX; } const
        void x(const T& ele) { VX = ele; }
        T y(void) const { return VY; } const
        void y(const T& ele) { VY = ele; }
    };

    template <typename T>
    class Vec3 : public Vector<T, 3>
    {
    public:
        Vec3(const T& x_ele, const T& y_ele, const T& z_ele) { VX = x_ele; VY = y_ele; VZ = z_ele; }
        T x(void) const { return VX; } const
        void x(const T& ele) { VX = ele; }
        T y(void) const { return VY; } const
        void y(const T& ele) { VY = ele; }
        T  z(void) const { return VZ; }
        void z(const T& ele) { VZ = ele; }
    };

    template <typename T>
    class Vec2U : public Vec2<T>
    {
        Vec2U(float& theta) { VX = (T)cos(theta), VY = (T)sin(theta); }
        Vec2U(Vec2<T>& vec) { T mag = vec.Mag(); VX = vec.x() / mag; VY / mag; }
        T Mag() const { return (T)1; }

    };

    template <typename T>
    class Vec3U : public Vec3<T>
    {
        /* spherical */
        Vec3U(float& theta, float& phi) { VX = (T)sin(theta) * (T)cos(phi); VY = (T)sin(theta) * (T)sin(theta); VZ = (T)cos(theta); }
        /* cylindrical -- maybe exclude later as cannot be sure to be unit */
        Vec3U(T& r, float& phi) 
        { 
            VX = r * (T)sin(phi); 
            VY = (T)cos(phi); 
            VZ = sqrt(r * r - 1);
            if ((T)-1 > r > (T)1)
            {
                std::cout << "Vec3U: r = " << r << " has a maginitude greater than 1" << std::endl;
            }
        }
        Vec3U(Vec3<T>& vec) { T mag = vec.Mag(); VX = vec.x() / mag; VY / mag; VZ / mag; }
        T Mag() const  { return (T)1; }

    };

    template<typename T, size_t M>
    static T Vector<T,M>::dot(Vector<T, M>& lhs, Vector<T, M>& rhs)
    {
        T lMag = lhs.Mag();
        T rMag = rhs.Mag();
        T sum = (lhs.mElements[0][0] / lMag) * (rhs.mElements[0][0] / rMag);
        for (size_t m_index = 1; m_index < M; m_index++)
        {
            sum += (lhs.mElements[0][m_index] / lMag) * (rhs.mElements[0][m_index] / rMag);
        }
        return sum;
    }

    template<typename T>
    static T dot(Vec2U<T>& lhs, Vec2U<T>& rhs)
    {
        return lhs.x() * rhs.x() + lhs.y() * rhs.y();
    }

    template<typename T>
    static T dot(Vec3U<T>& lhs, Vec3U<T>& rhs)
    {
        return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
    }

#undef LOOP_ALL_ELEMENTS
#undef OPERATE_ALL_ELEMENTS
#undef CURRENT_ELEMENT
#undef VEC_ELE
#undef PERFORM
}