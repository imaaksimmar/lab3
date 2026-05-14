#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          

using namespace exceptions;
using namespace array_sequence;
using namespace list_sequence;
using namespace triangle_matrix;

TEST(TriangleMatrixExceptions, IndexOutOfRangeRow) {
    TriangleMatrix<int, ArraySequence> m(3);
    EXPECT_THROW(m[3][0], IndexOutOfRange)
        << "input: TriangleMatrix m(3) -> m[3][0]"
        << "\nexpected: throw IndexOutOfRange (строка 3 выходит за пределы)";
}

TEST(TriangleMatrixExceptions, IndexOutOfRangeColumn) {
    TriangleMatrix<int, ArraySequence> m(3);
    EXPECT_THROW(m[0][3], IndexOutOfRange)
        << "input: TriangleMatrix m(3) -> m[0][3]"
        << "\nexpected: throw IndexOutOfRange (столбец 3 выходит за пределы)";
}

TEST(TriangleMatrixExceptions, IndexOutOfRangeMessage) {
    TriangleMatrix<int, ArraySequence> m(3);
    try 
    {
        m[5][0];
        FAIL() << "input: TriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: throw IndexOutOfRange, но исключение не было брошено";
    } 
    catch(const IndexOutOfRange& e) 
    {
        std::string expected = "IndexOutOfRange: requested index 5, BUT actual size is 3";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: TriangleMatrix m(3) -> m[5][0] -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    } 
    catch(...) 
    {
        FAIL() << "input: TriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: IndexOutOfRange, но брошено другое исключение";
    }
}

TEST(TriangleMatrixExceptions, InvalidArgumentUpperTriangle) {
    TriangleMatrix<int, ArraySequence> m(3);
    EXPECT_THROW(m[0][1], InvalidArgument)

        << "input: TriangleMatrix m(3) -> m[0][1]"
        << "\nexpected: throw InvalidArgument (верхний треугольник)";
    EXPECT_THROW(m[1][2], InvalidArgument)
        << "input: TriangleMatrix m(3) -> m[1][2]"
        << "\nexpected: throw InvalidArgument (верхний треугольник)";
}

TEST(TriangleMatrixExceptions, InvalidArgumentMessage) {
    TriangleMatrix<int, ArraySequence> m(3);
    try 
    {
        m[0][2];
        FAIL() << "input: TriangleMatrix m(3) -> m[0][2]"
               << "\nexpected: throw InvalidArgument, но исключение не было брошено";
    } 
    catch(const InvalidArgument& e) 
    {
        std::string expected = "InvalidArgument: access to upper triangle is forbidden (Row: 0, Column: 2)";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: TriangleMatrix m(3) -> m[0][2] -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    } 
    catch(...) 
    {
        FAIL() << "input: TriangleMatrix m(3) -> m[0][2]"
               << "\nexpected: InvalidArgument, но брошено другое исключение";
    }
}

TEST(TriangleMatrixExceptions, SizeMismatchAdd) {
    TriangleMatrix<int, ArraySequence> m1(2);
    TriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1.Add(m2), SizeMismatch)
        << "input: TriangleMatrix m1(2).Add(TriangleMatrix m2(4))"
        << "\nexpected: throw SizeMismatch";
    EXPECT_THROW(m1+m2, SizeMismatch)
        << "input: TriangleMatrix m1(2) + TriangleMatrix m2(4)"
        << "\nexpected: throw SizeMismatch";
}

TEST(TriangleMatrixExceptions, SizeMismatchMessage) {
    TriangleMatrix<int, ArraySequence> m1(2);
    TriangleMatrix<int, ArraySequence> m2(4);
    try 
    {
        m1.Add(m2);
        FAIL() << "input: TriangleMatrix m1(2).Add(TriangleMatrix m2(4))"
               << "\nexpected: throw SizeMismatch, но исключение не было брошено";
    } 
    catch(const SizeMismatch& e) 
    {
        std::string expected = "SizeMismatch: sizes do not match (2 vs 4)";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: TriangleMatrix m1(2).Add(m2(4)) -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    } 
    catch(...) 
    {
        FAIL() << "input: TriangleMatrix m1(2).Add(TriangleMatrix m2(4))"
               << "\nexpected: SizeMismatch, но брошено другое исключение";
    }
}
