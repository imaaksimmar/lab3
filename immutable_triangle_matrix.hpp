#pragma once
#include <cmath>
#include <cstddef>
#include "sequence.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "exceptions.hpp"

template <typename T, template <typename> class Container>
class ImmutableTriangleMatrix {
public:
    class ConstProxy {
    private:
        const ImmutableTriangleMatrix<T, Container>* matrix;
        size_t row;
        size_t rowStartIndex;

    public:
        ConstProxy(const ImmutableTriangleMatrix<T, Container>* m, size_t r)
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
    
    ConstProxy operator[](size_t row) const { return ConstProxy(this, row); }

private:
    size_t size;
    Container<T>* data;
    ImmutableTriangleMatrix(size_t s, Container<T>* newData) 
    : size(s), data(newData) {}

public:
    ImmutableTriangleMatrix() 
    : size(0), data(new Container<T>()) {}

    ImmutableTriangleMatrix(size_t n) 
    : size(n), data(new Container<T>())
    {
        for(size_t i=0; i<size; ++i) {
            for(size_t j=0; j<=i; ++j) {
                data->Append(T());
            }
        }
    }

    ImmutableTriangleMatrix(const ImmutableTriangleMatrix& other)
    : size(other.size), data(new Container<T>(*other.data)) {}

    ~ImmutableTriangleMatrix() { delete data; }

    size_t GetSize() const { return size; }

    ImmutableTriangleMatrix Add(const ImmutableTriangleMatrix& other) const 
    { 
        if(this->size != other.size) { throw SizeMismatch(this->size, other.size); }

        Container<T>* newData = new Container<T>(*this->data);
        size_t index = 0; 
        for(size_t i=0; i<this->size; i++) { 
            for(size_t j=0; j<=i; j++) {
                (*newData)[index] = (*newData)[index] + other[i][j];
                index++; 
            }
        }
        return ImmutableTriangleMatrix(this->size, newData);
    }
    

    ImmutableTriangleMatrix ScalarMultiply(T scalar) const 
    {
        Container<T>* newData = new Container<T>(*this->data);
        size_t index = 0;
        for(size_t i=0; i<this->size; i++) {
            for (size_t j=0; j<=i; j++) {
                (*newData)[index] = (*newData)[index] * scalar;
                index++;
            }
        }
        return ImmutableTriangleMatrix(this->size, newData);
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

    ImmutableTriangleMatrix operator+(const ImmutableTriangleMatrix& other) const
    {
        return this->Add(other);
    }

    ImmutableTriangleMatrix operator*(T scalar) const 
    {
        return this->ScalarMultiply(scalar);
    }

    ImmutableTriangleMatrix& operator=(const ImmutableTriangleMatrix& other) 
    {
        if(this == &other) { return *this; }

        delete data;
        size = other.size;
        data = new Container<T>(*other.data);

        return *this;
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

    ImmutableTriangleMatrix Where(bool (*predicate)(T)) const 
    {
        Container<T>* newData = new Container<T>(*this->data);
        
        size_t index = 0;
        for(size_t i=0; i<this->size; i++) {
            for(size_t j=0; j<=i; j++) {
                if (!predicate((*this)[i][j])) {
                    (*newData)[index] = T();
                }
                index++;
            }
        }   
        return ImmutableTriangleMatrix(this->size, newData);
    }

    template <typename U>
    ImmutableTriangleMatrix<U, Container> Map(U (*mapper)(T)) const 
    {
        Container<U>* newData = new Container<U>();
        for(size_t i=0; i<this->size; i++) {
            for(size_t j=0; j<=i; j++) {
                newData->Append(mapper((*this)[i][j]));
            }
        }
        return ImmutableTriangleMatrix<U, Container>(this->size, newData);
    }

};