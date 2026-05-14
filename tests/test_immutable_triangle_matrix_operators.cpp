#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          
#include "../immutable_triangle_matrix.hpp"

using namespace exceptions;
using namespace array_sequence;
using namespace list_sequence;
using namespace triangle_matrix;
using namespace immutable_triangle_matrix;

TEST(ImmutableTriangleMatrixOperators, AddOperatorResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1+m2;

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m1(2){0} + m2(2){0} -> res.GetSize()"
        << "\nexpected: 2";
}

TEST(ImmutableTriangleMatrixOperators, AddOperatorOperandsUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1+m2;

    EXPECT_EQ(m1.GetSize(), 2u)
        << "input: m1(2) + m2(2) -> m1.GetSize()"
        << "\nexpected: 2 (operator+ не изменяет m1)";
    EXPECT_EQ(m2.GetSize(), 2u)
        << "input: m1(2) + m2(2) -> m2.GetSize()"
        << "\nexpected: 2 (operator+ не изменяет m2)";
}

TEST(ImmutableTriangleMatrixOperators, AddOperatorSizeMismatch) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1+m2, SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2) + ImmutableTriangleMatrix m2(4)"
        << "\nexpected: throw SizeMismatch";
}

TEST(ImmutableTriangleMatrixOperators, MultiplyOperatorResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m*3;

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2){0} *3 -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0} *3 -> res[0][0]"
        << "\nexpected: 0 (0*3)";
}

TEST(ImmutableTriangleMatrixOperators, MultiplyOperatorOriginalUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m*3;

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2){0} * 3 -> m.GetSize()"
        << "\nexpected: 2 (operator* не изменяет оригинал)";
}

TEST(ImmutableTriangleMatrixOperators, AssignOperatorCopiesValues) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(3);
    ImmutableTriangleMatrix<int, ArraySequence> m2;

    m2 = m1;

    EXPECT_EQ(m2.GetSize(), 3u)
        << "input: m1(3) -> m2 = m1 -> m2.GetSize()"
        << "\nexpected: 3";
}

TEST(ImmutableTriangleMatrixOperators, AssignOperatorSelfAssign) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    m.operator=(m);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2) -> m=m -> m.GetSize()"
        << "\nexpected: 2 (самоприсваивание не ломает матрицу)";
}
