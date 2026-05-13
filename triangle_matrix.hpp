#pragma once
#include <cmath>
#include <cstddef>
#include "sequence.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "exceptions.hpp"


template <typename T, template <typename> class Container> 
class TriangleMatrix {
    public:
    class Proxy {
    private:
        TriangleMatrix<T, Container>* matrix; 
        size_t row;                          
        size_t rowStartIndex;                

    public:
        Proxy(TriangleMatrix<T, Container>* m, size_t r)
        : matrix(m), row(r) { 
            rowStartIndex = row*(row+1)/2; 
        }
             
        T& operator[](size_t column) {
            if(row>=matrix->GetSize()) {
                throw IndexOutOfRange(row, matrix->GetSize());
            }
            if(column>=matrix->GetSize()) {
                throw IndexOutOfRange(column, matrix->GetSize());
            }
            if(row<column) {
                throw InvalidArgument(row, column); 
            }
            return (*matrix->data)[rowStartIndex + column];
        }
    };
    
    class ConstProxy {
    private:
        const TriangleMatrix<T, Container>* matrix;
        size_t row;
        size_t rowStartIndex;

    public:
        ConstProxy(const TriangleMatrix<T, Container>* m, size_t r)
        : matrix(m), row(r) {
            rowStartIndex = row*(row+1)/2; 
        }

        T operator[](size_t column) const {
            if(row>=matrix->GetSize()) {
                throw IndexOutOfRange(row, matrix->GetSize());
            }
            if(column>=matrix->GetSize()) {
                throw IndexOutOfRange(column, matrix->GetSize());
            }
            if(row<column) {
                return T();
            }
            return (*matrix->data)[rowStartIndex + column];
        }
    };

    Proxy operator[](size_t row) { return Proxy(this, row); }
    ConstProxy operator[](size_t row) const { return ConstProxy(this, row); }

    private:
    size_t size;
    Container<T>* data;

    public:
    TriangleMatrix() 
    : size(0), data(new Container<T>()) {}

    TriangleMatrix(size_t n) 
    : size(n), data(new Container<T>())
    {
        for(size_t i=0; i<size; ++i) {
            for(size_t j=0; j<=i; ++j) {
                data->Append(T());
            }
        }
    }

    TriangleMatrix(const TriangleMatrix& other)
    : size(other.size), data(new Container<T>(*other.data)) {}

    ~TriangleMatrix() { delete data; }

    size_t GetSize() const { return size; }

    TriangleMatrix<T, Container>* Add(const TriangleMatrix<T, Container>& other) 
    {
        if(this->size != other.size) { throw SizeMismatch(this->size, other.size); }

        for(size_t i=0; i<this->size; i++) {
            for(size_t j=0; j<=i; j++) {
                (*this)[i][j] = (*this)[i][j] + other[i][j];
            }
        }
        return this;
    }
    
    TriangleMatrix<T, Container>* ScalarMultiply(T scalar) 
    {
        for(size_t i=0; i<this->size; i++) {
            for(size_t j=0; j<=i; j++) {
                (*this)[i][j] = (*this)[i][j] * scalar;
            }
        }
        return this;

    }

    T Norm() const 
    {
        T maxNorm = T();
        for(size_t i=0; i<this->size; i++) {
            T current = T();
            for(size_t j=0; j<=i; j++) {
                current += std::abs((*this)[i][j]);
            }
            if(current>maxNorm) { maxNorm = current; }
        }
        return maxNorm;

    }

    TriangleMatrix<T, Container>& operator=(const TriangleMatrix<T, Container>& other) 
    {
        if(this == &other) { return *this; }

        delete data;
        size = other.size;
        data = new Container<T>(*(other.data));

        return *this;
    }

    TriangleMatrix<T, Container> operator+(const TriangleMatrix<T, Container>& other) const
    {
        TriangleMatrix<T, Container> result(*this);
        result.Add(other);
        return result;
    }

    TriangleMatrix<T, Container> operator*(T scalar) const
    {
        TriangleMatrix<T, Container> result(*this);
        result.ScalarMultiply(scalar);
        return result;
    }
    
    template <typename U>
    TriangleMatrix<U, Container> Map(U (*mapper)(T)) const 
    {
        TriangleMatrix<U, Container> result(this->size);
        for(size_t i=0; i<this->size; i++) {
            for(size_t j=0; j<=i; j++) {
                result[i][j] = mapper((*this)[i][j]);
            }
        }
        return result;
    }

    TriangleMatrix<T, Container> Where(bool (*where)(T)) const 
    {
        TriangleMatrix<T, Container> result(this->size);
        for(size_t i=0; i<this->size; i++) {
            for(size_t j=0; j<=i; j++) {
                if(where((*this)[i][j])) {
                    result[i][j] = (*this)[i][j];
                }
            }
        }
        return result;
    }

    template <typename U>
    U Reduce(U (*reducer)(U, T), U initialValue) const
    {
        U result = initialValue;
        for(size_t i=0; i<this->size; i++) {
            for(size_t j=0; j<=i; j++) {
                result = reducer(result, (*this)[i][j]);
            }
        }
        return result;
    }

};