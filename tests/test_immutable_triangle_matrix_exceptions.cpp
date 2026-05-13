#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          
#include "../immutable_triangle_matrix.hpp"

TEST(ImmutableTriangleMatrixExceptions, IndexOutOfRangeRow) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_THROW(m[3][0], IndexOutOfRange)
        << "input: ImmutableTriangleMatrix m(3) -> m[3][0]"
        << "\nexpected: throw IndexOutOfRange (строка 3 выходит за пределы)";
}

TEST(ImmutableTriangleMatrixExceptions, IndexOutOfRangeColumn) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_THROW(m[0][3], IndexOutOfRange)
        << "input: ImmutableTriangleMatrix m(3) -> m[0][3]"
        << "\nexpected: throw IndexOutOfRange (столбец 3 выходит за пределы)";
}


TEST(ImmutableTriangleMatrixExceptions, IndexOutOfRangeMessage) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);
    try
    {
        m[5][0];
        FAIL() << "input: ImmutableTriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: throw IndexOutOfRange, но исключение не было брошено";
    }
    catch(const IndexOutOfRange& e)
    {
        std::string expected = "IndexOutOfRange: requested index 5, BUT actual size is 3";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: ImmutableTriangleMatrix m(3) -> m[5][0] -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    }
    catch(...)
    {
        FAIL() << "input: ImmutableTriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: IndexOutOfRange, но брошено другое исключение";
    }
}

TEST(ImmutableTriangleMatrixExceptions, UpperTriangleReturnsDefault) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_EQ(m[0][1], 0)
        << "input: ImmutableTriangleMatrix m(3) -> m[0][1]"
        << "\nexpected: 0 (верхний треугольник возвращает T() )";
    EXPECT_EQ(m[0][2], 0)
        << "input: ImmutableTriangleMatrix m(3) -> m[0][2]"
        << "\nexpected: 0 (верхний треугольник возвращает T() )";
    EXPECT_EQ(m[1][2], 0)
        << "input: ImmutableTriangleMatrix m(3) -> m[1][2]"
        << "\nexpected: 0 (верхний треугольник возвращает T() )";
}

TEST(ImmutableTriangleMatrixExceptions, SizeMismatchAdd) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1.Add(m2), SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
        << "\nexpected: throw SizeMismatch";
    EXPECT_THROW(m1+m2, SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2) + ImmutableTriangleMatrix m2(4)"
        << "\nexpected: throw SizeMismatch";
}

TEST(ImmutableTriangleMatrixExceptions, SizeMismatchMessage) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);
    try
    {
        m1.Add(m2);
        FAIL() << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
               << "\nexpected: throw SizeMismatch, но исключение не было брошено";
    }
    catch(const SizeMismatch& e)
    {
        std::string expected = "SizeMismatch: sizes do not match (2 vs 4)";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: ImmutableTriangleMatrix m1(2).Add(m2(4)) -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    }
    catch(...)
    {
        FAIL() << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
               << "\nexpected: SizeMismatch, но брошено другое исключение";
    }
}
