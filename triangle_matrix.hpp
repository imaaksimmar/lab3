#pragma once
#include <cmath>
#include <cstddef>
#include "sequence.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "exceptions.hpp"


template <typename T, template <typename> class Container> 
class TriangleMatrix {
    private:
    size_t size;
    Container<T>* data;

    public:

    class RowProxy
    {
        private:
        TriangleMatrix<T, Container>* matrix;
        size_t row;

        public:
        RowProxy(TriangleMatrix<T, Container>* m, size_t r)
        : matrix(m), row(r) {}

        T& operator[](size_t column) {
            if(row>=matrix->GetSize() || column>=matrix->GetSize()) {
                throw IndexOutOfRange();
            }
            if(row<column) {
                throw InvalidArgument(); 
            }

            size_t index = row*(row+1)/2 + column;
            return (*matrix->data)[index];
        }
    };

    RowProxy operator[](size_t row) {
        return RowProxy(this, row);
    }



};