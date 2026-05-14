#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          
#include "../immutable_triangle_matrix.hpp"

using namespace exceptions;
using namespace array_sequence;
using namespace list_sequence;
using namespace triangle_matrix;
using namespace immutable_triangle_matrix;

static bool isEvenImmut(int x) { return x%2 == 0; }
static int doubleItImmut(int x) { return x*2; }

TEST(ImmutableTriangleMatrixImmutability, WhereReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Where(isEvenImmut);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2).Where(x%2==0) -> m.GetSize()"
        << "\nexpected: 2 (Where не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2).Where(x%2==0) -> res.GetSize()"
        << "\nexpected: 2";
}

TEST(ImmutableTriangleMatrixImmutability, MapReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Map(doubleItImmut);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2).Map(x*2) -> m.GetSize()"
        << "\nexpected: 2 (Map не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2).Map(x*2) -> res.GetSize()"
        << "\nexpected: 2";
}


static int immutMultiplyByTen(int x) { return x*10; }

TEST(ImmutableTriangleMatrixFunctional, MapResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Map(immutMultiplyByTen);

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2){0,0,0}.Map(x*10) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0,0,0}.Map(x*10) -> res[0][0]"
        << "\nexpected: 0 (0*10)";
}

TEST(ImmutableTriangleMatrixFunctional, MapOriginalUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    m.Map(immutMultiplyByTen);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2){0}.Map(x*10) -> m.GetSize()"
        << "\nexpected: 2 (Map не изменяет оригинал)";
    EXPECT_EQ(m[0][0], 0)
        << "input: m(2){0}.Map(x*10) -> m[0][0]"
        << "\nexpected: 0 (Map не изменяет оригинал)";
}

static int immutSumReducer(int acc, int val) { return acc+val; }

TEST(ImmutableTriangleMatrixFunctional, ReduceSum) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    int sum = m.Reduce(immutSumReducer, 0);

    EXPECT_EQ(sum, 0)
        << "input: m(2){0,0,0}.Reduce(a+b, 0)"
        << "\nexpected: 0 (0+0+0)";
}

TEST(ImmutableTriangleMatrixFunctional, WhereResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Where(isEvenImmut);

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2){0,0,0}.Where(x%2==0) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0,0,0}.Where(x%2==0) -> res[0][0]"
        << "\nexpected: 0 (0 чётное -> остаётся)";
}

TEST(ImmutableTriangleMatrixFunctional, WhereOriginalUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    m.Where(isEvenImmut);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2){0}.Where(x%2==0) -> m.GetSize()"
        << "\nexpected: 2 (Where не изменяет оригинал)";
}
