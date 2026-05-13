#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          
#include "../immutable_triangle_matrix.hpp"

TEST(ImmutableTriangleMatrix, GetSizeZero) {
    ImmutableTriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.GetSize(), 0u)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m -> m.GetSize()"
        << "\nexpected: 0";
}

TEST(ImmutableTriangleMatrix, GetSizeValue) {
    ImmutableTriangleMatrix<int, ArraySequence> m(5);

    EXPECT_EQ(m.GetSize(), 5u)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(5) -> m.GetSize()"
        << "\nexpected: 5";
}


TEST(ImmutableTriangleMatrixImmutability, AddReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1.Add(m2);

    EXPECT_EQ(m1.GetSize(), 2u)
        << "input: m1(2).Add(m2(2)) -> m1.GetSize()"
        << "\nexpected: 2 (Add не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m1(2).Add(m2(2)) -> res.GetSize()"
        << "\nexpected: 2";
}

TEST(ImmutableTriangleMatrixImmutability, ScalarMultiplyReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);
    ImmutableTriangleMatrix<int, ArraySequence> res = m.ScalarMultiply(5);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2).ScalarMultiply(5) -> m.GetSize()"
        << "\nexpected: 2 (ScalarMultiply не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2).ScalarMultiply(5) -> res.GetSize()"
        << "\nexpected: 2";
}


TEST(ImmutableTriangleMatrixMath, AddResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1.Add(m2);

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m1(2){0,0,0}.Add(m2(2){0,0,0}) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m1(2){0,0,0}.Add(m2(2){0,0,0}) -> res[0][0]"
        << "\nexpected: 0 (0+0)";
}

TEST(ImmutableTriangleMatrixMath, AddSizeMismatch) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1.Add(m2), SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
        << "\nexpected: throw SizeMismatch";
}

TEST(ImmutableTriangleMatrixMath, ScalarMultiplyResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);
    ImmutableTriangleMatrix<int, ArraySequence> res = m.ScalarMultiply(5);

    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0,0,0}.ScalarMultiply(5) -> res[0][0]"
        << "\nexpected: 0 (0*5)";
    EXPECT_EQ(res[1][1], 0)
        << "input: m(2){0,0,0}.ScalarMultiply(5) -> res[1][1]"
        << "\nexpected: 0 (0*5)";
}

TEST(ImmutableTriangleMatrixMath, NormEmpty) {
    ImmutableTriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.Norm(), 0)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m -> m.Norm()"
        << "\nexpected: 0 (пустая матрица)";
}

TEST(ImmutableTriangleMatrixMath, NormZeros) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_EQ(m.Norm(), 0)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(3) -> m.Norm()"
        << "\nexpected: 0 (матрица нулевая)";
}


