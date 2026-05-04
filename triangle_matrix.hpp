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

    class Iterator {
    private:
        TriangleMatrix<T, Container>* matrix; 
        size_t row;                          
        size_t rowStartIndex;                

    public:
        Iterator(TriangleMatrix<T, Container>* m, size_t r)
        : matrix(m), row(r) {
            rowStartIndex = row * (row + 1) / 2; 
        }

        T& operator[](size_t column) {
            if(row>=matrix->GetSize() || column>=matrix->GetSize()) {
                throw IndexOutOfRange();
            }
            if(row<column) {
                throw InvalidArgument(); 
            }
            return (*matrix->data)[rowStartIndex + column];
        }
    };

    
    class ConstIterator {
    private:
        const TriangleMatrix<T, Container>* matrix;
        size_t row;
        size_t rowStartIndex;

    public:
        ConstIterator(const TriangleMatrix<T, Container>* m, size_t r)
        : matrix(m), row(r) {
            rowStartIndex = row * (row + 1) / 2;
        }

    
        T operator[](size_t column) const {
            if(row>=matrix->GetSize() || column>=matrix->GetSize()) {
                throw IndexOutOfRange();
            }
            if(row<column) {
                return T(); 
            }
            return (*matrix->data)[rowStartIndex + column];
        }
    };

    Iterator operator[](size_t row) { return Iterator(this, row); }
    ConstIterator operator[](size_t row) const { return ConstIterator(this, row); }

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


};