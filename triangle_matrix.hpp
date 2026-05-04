#pragma once
#include <cmath>
#include <cstddef>
#include "sequence.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "exceptions.hpp"

enum class StorageType { array, list };

template <typename T, typename <class T> Container>
class TriangleMatrix {
    private:
    size_t size;
    StorageType currentStorage;
    Container<T>* data;

    public:
    TriangleMatrix() 
    : size(0), currentStorage(StorageType::array), data(new ArraySequence<T>()) {}

    TriangleMatrix(size_t n, StorageType type = StorageType::array) 
    : size(n), currentStorage(type)
    {
        if(type == StorageType::array) {///////
            data = new ArraySequence<T>();
        }
        else {
            data = new ListSequence<T>();
        }
        for(size_t i=0; i<size; ++i) {
            for(size_t j=0; j<=i; ++j) {
                data->Append(T());
            }
        }
    }

    TriangleMatrix(const TriangleMatrix& other)
    : size(other.size), currentStorage(other.currentStorage)
    {
        if(currentStorage == StorageType::array) {
            data = new ArraySequence<T>(*(ArraySequence<T>*)other.data);
        }
        else {
            data = new ListSequence<T>(*(ListSequence<T>*)other.data);
        }
    }

    ~TriangleMatrix() { delete data; }

    size_t GetSize() const { return size; }

    T Get(size_t row, size_t column) const 
    {
        if(row>=size || column>=size) {
            throw IndexOutOfRange();/////// 
        }
        if(row<column) {
            return T();
        }
        size_t index = row*(row+1)/2 + column;
        return data->Get(index);
        
        
    }

    void Set(size_t row, size_t column, T value) 
    {
        if(row>=size || column>=size) {
            throw IndexOutOfRange();
        }
        if(row<column) {
            if(value != T()) { throw InvalidArgument(); } 
        return;
        }

        size_t index = row*(row+1)/2 + column;
        data->Set(index, value);
    }

    TriangleMatrix<T>* Add(const TriangleMatrix<T>& other) 
    {
        if(this->size != other.size) { throw SizeMismatch(); }

        for(size_t i=0; i<this->data->GetLength(); i++) {
            T value1 = this->data->Get(i);
            T value2 = other.data->Get(i);
            this->data->Set(i, value1+value2);
        }
        return this;
    }
    
    TriangleMatrix<T>* ScalarMultiply(T scalar) 
    {
        for(size_t i=0; i<this->data->GetLength(); i++) {
            T newValue = this->data->Get(i) * scalar;
            this->data->Set(i, newValue);
        }
        return this;

    }

    T Norm() const 
    {
        T maxNorm = T();

        for(size_t i=0; i<this->size; i++) {
            T current = T();
            for(size_t j=0; j<=i; j++) {
                current += std::abs(this->Get(i,j));
            }
            if(current>maxNorm) { maxNorm = current; }
        }
        return maxNorm;

    }

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other) 
    {
        if(this == &other) { return *this; }

        delete data;
        size = other.size;
        currentStorage = other.currentStorage;

        if(currentStorage == StorageType::array ) {
            data = new ArraySequence<T>(*(ArraySequence<T>*)other.data);
        }
        else {
            data = new ListSequence<T>(*(ListSequence<T>*)other.data);
        }
        return *this;
    }

    TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const
    {
        TriangleMatrix<T> result(*this);
        result.Add(other);
        return result;
    }

    TriangleMatrix<T> operator*(T scalar) const
    {
        TriangleMatrix<T> result(*this);
        result.ScalarMultiply(scalar);  
        return result;
    }
    ///operator[] instead of get|set



};