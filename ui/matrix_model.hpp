#pragma once
#include <cstddef>
#include <QString>
#include "triangle_matrix.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"


class MatrixModel {
    public:
        virtual ~MatrixModel() = default;

        virtual size_t GetSize() const = 0;
        virtual double GetElement(int i, int j) const = 0;
        virtual void SetElement(int i, int j, double value)  = 0;
        virtual double Norm() const = 0;
        virtual double Reduce(double initial) const = 0;

        virtual MatrixModel& Add(const MatrixModel& other) = 0;
        virtual MatrixModel& ScalarMultiply(double scalar) = 0;
        virtual MatrixModel& Map() = 0;  
        virtual MatrixModel& Where() = 0;

        virtual MatrixModel* AddNew(const MatrixModel& other) const = 0;
        virtual MatrixModel* MultiplyNew(double scalar) const = 0;
        virtual MatrixModel* MapNew() const = 0;
        virtual MatrixModel* WhereNew() const = 0;
};


static int multiplyByTwoInt(int x) { return x*2; }
static double multiplyByTwoDouble(double x) { return x*2.0; }

static bool isEvenInt(int x) { return x%2==0; }
static bool isEvenDouble(double x) { return (int)x%2==0; }

static int addInts(int a, int b) { return a+b; }
static double addDoubles(double a, double b) { return a+b; }


template <typename T, template <typename> class Container>
class MatrixAdapter : public MatrixModel {
    triangle_matrix::TriangleMatrix<T, Container> matrix; 
public:
    MatrixAdapter(int n) : matrix(n) {}
    MatrixAdapter(const triangle_matrix::TriangleMatrix<T, Container>& m) : matrix(m) {}

    size_t GetSize() const override { return matrix.GetSize(); }
    double GetElement(int i, int j) const override { return (double)matrix[i][j]; }
    void SetElement(int i, int j, double val) override { matrix[i][j] = (T)val; }
    double Norm() const override { return (double)matrix.Norm(); }

    double Reduce(double initial) const override {
        if constexpr (std::is_same_v<T, int>) {
            return (double)matrix.Reduce(addInts, (int)initial);
        }
        else {
            return (double)matrix.Reduce(addDoubles, (double)initial);
        }
    }

    MatrixModel& Add(const MatrixModel& other) override {
        triangle_matrix::TriangleMatrix<T, Container> tmp(matrix.GetSize());
        int n = (int)matrix.GetSize();
        for(int i=0; i<n; i++)
            for(int j=0; j<=i; j++)
                tmp[i][j] = (T)other.GetElement(i, j);
        matrix.Add(tmp);
        return *this; 
    }

    MatrixModel& ScalarMultiply(double scalar) override {
        matrix.ScalarMultiply((T)scalar);
        return *this; 
    }

    MatrixModel& Map() override {
        if constexpr (std::is_same_v<T, int>) matrix = matrix.Map(multiplyByTwoInt);
        else matrix = matrix.Map(multiplyByTwoDouble);
        return *this; 
    }

    MatrixModel& Where() override {
        if constexpr (std::is_same_v<T, int>) matrix = matrix.Where(isEvenInt);
        else matrix = matrix.Where(isEvenDouble);
        return *this; 
    }

    MatrixModel* AddNew(const MatrixModel& other) const override {
        triangle_matrix::TriangleMatrix<T, Container> tmp(matrix.GetSize());
        int n = (int)matrix.GetSize();
        for(int i=0; i<n; i++)
            for(int j=0; j<=i; j++)
                tmp[i][j] = (T)other.GetElement(i, j);
        return new MatrixAdapter<T, Container>(matrix + tmp);
    }

    MatrixModel* MultiplyNew(double scalar) const override {
        return new MatrixAdapter<T, Container>(matrix*(T)scalar);
    }

    MatrixModel* MapNew() const override {
        if constexpr (std::is_same_v<T, int>) return new MatrixAdapter<T, Container>(matrix.Map(multiplyByTwoInt));
        else return new MatrixAdapter<T, Container>(matrix.Map(multiplyByTwoDouble));
    }

    MatrixModel* WhereNew() const override {
        if constexpr (std::is_same_v<T, int>) return new MatrixAdapter<T, Container>(matrix.Where(isEvenInt));
        else return new MatrixAdapter<T, Container>(matrix.Where(isEvenDouble));
    }
};


inline MatrixModel* createModel(const QString& type, const QString& container, int n) {
    if(type=="int" && container=="ArraySequence") { 
        return new MatrixAdapter<int, array_sequence::ArraySequence>(n);
    }

    if(type=="int" && container=="ListSequence") { 
        return new MatrixAdapter<int, list_sequence::ListSequence>(n);
    }

    if(type=="double" && container=="ArraySequence") {
        return new MatrixAdapter<double, array_sequence::ArraySequence>(n);
    }
        
    return new MatrixAdapter<double, list_sequence::ListSequence>(n);
}