#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          

int MultiplyByTen(int x) { return x*10; }

TEST(TriangleMatrixFunctional, MapResult) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 3;

    TriangleMatrix<int, ArraySequence> res = m.Map(MultiplyByTen);
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m{1,2,3}.Map(x*10) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 10)
        << "input: m{1,2,3}.Map(x*10) -> res[0][0]"
        << "\nexpected: 10 (1*10)";
    EXPECT_EQ(res[1][0], 20)
        << "input: m{1,2,3}.Map(x*10) -> res[1][0]"
        << "\nexpected: 20 (2*10)";
    EXPECT_EQ(res[1][1], 30)
        << "input: m{1,2,3}.Map(x*10) -> res[1][1]"
        << "\nexpected: 30 (3*10)";
}

TEST(TriangleMatrixFunctional, MapOriginalUnchanged) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 3;

    m.Map(MultiplyByTen);
    EXPECT_EQ(m[0][0], 1)
        << "input: m{1,2,3}.Map(x*10) -> m[0][0]"
        << "\nexpected: 1 (Map не изменяет оригинал)";
    EXPECT_EQ(m[1][0], 2)
        << "input: m{1,2,3}.Map(x*10) -> m[1][0]"
        << "\nexpected: 2 (Map не изменяет оригинал)";
    EXPECT_EQ(m[1][1], 3)
        << "input: m{1,2,3}.Map(x*10) -> m[1][1]"
        << "\nexpected: 3 (Map не изменяет оригинал)";
}

int SumReducer(int acc, int val) { return acc+val; }

TEST(TriangleMatrixFunctional, ReduceSum) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 2; 
    m[1][0] = 3; 
    m[1][1] = 4;

    int sum = m.Reduce(SumReducer, 0);
    EXPECT_EQ(sum, 9)
        << "input: m{2,3,4}.Reduce(a+b, 0)"
        << "\nexpected: 9 (2+3+4)";
}


bool IsTwoDivided(int x) { return x%2==0; }

TEST(TriangleMatrixFunctional, WhereResult) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 4;

    TriangleMatrix<int, ArraySequence> res = m.Where(IsTwoDivided);
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m{1,2,4}.Where(x%2==0) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m{1,2,4}.Where(x%2==0) -> res[0][0]"
        << "\nexpected: 0 (1 нечётное -> заменяется на 0)";
    EXPECT_EQ(res[1][0], 2)
        << "input: m{1,2,4}.Where(x%2==0) -> res[1][0]"
        << "\nexpected: 2 (2 чётное -> остаётся)";
    EXPECT_EQ(res[1][1], 4)
        << "input: m{1,2,4}.Where(x%2==0) -> res[1][1]"
        << "\nexpected: 4 (4 чётное -> остаётся)";
}

TEST(TriangleMatrixFunctional, WhereOriginalUnchanged) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 4;
    m.Where(IsTwoDivided);

    EXPECT_EQ(m[0][0], 1)
        << "input: m{1,2,4}.Where(x%2==0) -> m[0][0]"
        << "\nexpected: 1 (Where не изменяет оригинал)";
    EXPECT_EQ(m[1][0], 2)
        << "input: m{1,2,4}.Where(x%2==0) -> m[1][0]"
        << "\nexpected: 2 (Where не изменяет оригинал)";
    EXPECT_EQ(m[1][1], 4)
        << "input: m{1,2,4}.Where(x%2==0) -> m[1][1]"
        << "\nexpected: 4 (Where не изменяет оригинал)";
}