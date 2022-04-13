#include "doctest.h"
#include "Matrix.hpp"

using namespace zich;
using namespace std;

TEST_CASE("incorrect inputs")
{
    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    SUBCASE("Negative numbers of rows or columns")
    {
        CHECK_THROWS(Matrix a(identity, -3, 3));  //first number negative (if positive then correct)
        CHECK_THROWS(Matrix a(identity, 3, -3));  //second number negative (if positive then correct)
        CHECK_THROWS(Matrix a(identity, -3, -3));  //both numbers negative (if positive then correct)

        CHECK_THROWS(Matrix a(identity, -3, 4));  //first number negative (the dimention is incorrect too)
        CHECK_THROWS(Matrix a(identity, 4, -3));  //second number negative (if positive then correct)
        CHECK_THROWS(Matrix a(identity, -4, -4));  //both numbers negative (if positive then correct)
    }
    SUBCASE("incorrect dimention of rows*cols == vector.length")
    {
        CHECK_THROWS(Matrix a(identity, 3, 4));  // 3 variations of incorrect dimentions
        CHECK_THROWS(Matrix a(identity, 3, 2));  
        CHECK_THROWS(Matrix a(identity, 5, 6));
    }
}

TEST_CASE("Correct input - correct answers")
{
    SUBCASE("Addition + equals")
    {
        vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        vector<double> addition = {2, 0, 0, 0, 2, 0, 0, 0, 2};
        Matrix firstMat(identity, 3, 3);
        Matrix secondMat(identity, 3, 3);
        Matrix thirdMat(addition, 3, 3);
        CHECK_NOTHROW(firstMat + secondMat);
        CHECK(firstMat + secondMat == thirdMat);
        firstMat += secondMat;
        CHECK(firstMat == thirdMat);
        CHECK(secondMat != thirdMat);

        vector<double> firstVect = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        vector<double> secondVect = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        vector<double> ansVect = {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13};
        firstMat = Matrix(firstVect, 3, 4);
        secondMat = Matrix(secondVect, 3, 4); //same matrix as previous line
        thirdMat = Matrix(ansVect, 3, 4);
        CHECK(firstMat + secondMat == thirdMat);
        secondMat += firstMat;
        CHECK(secondMat == thirdMat);

        firstVect = {1, 2, -3, 4, 5, 6.5, 7, 8, 9, 10, -11, 12};
        vector<double> plusPlusVect = {2, 3, -2, 5, 6, 7.5, 8, 9, 10, 11, -10, 13};
        secondVect = {3, -6.7, 9, 12, -15, 18, 21, 24, 27, 30.3, 33, -36.125};
        ansVect = {4, -4.7, 6, 16, -10, 24.5, 28, 32, 36, 40.3, 22, -24.125};
        firstMat = Matrix(firstVect, 4, 3);
        secondMat = Matrix(secondVect, 4, 3);
        thirdMat = Matrix(ansVect, 4, 3);
        CHECK(firstMat + secondMat == thirdMat); //following 3 tests are basically the same, slight variation in syntax for assurances
        CHECK(secondMat + firstMat == thirdMat);
        CHECK(firstMat + secondMat == secondMat + firstMat);
        secondMat += firstMat;
        CHECK(secondMat == thirdMat);
        secondMat = +firstMat;
        CHECK(secondMat == firstMat);

        Matrix plusPlusMat(plusPlusVect, 4, 3);
        Matrix OriginMat(firstVect, 4, 3);
        CHECK(OriginMat++ != plusPlusMat);
        CHECK(OriginMat == plusPlusMat);

        plusPlusMat = Matrix(plusPlusVect, 4, 3);
        OriginMat = Matrix(firstVect, 4, 3);
        CHECK(++OriginMat == plusPlusMat);

    }

    SUBCASE("Subtraction + equals")
    {
        vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        vector<double> zeroes = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        Matrix identityMat(identity, 3, 3);
        Matrix zeroesMat(zeroes, 3, 3);
        CHECK(identityMat - identityMat == zeroesMat);
        CHECK(identityMat - zeroesMat == identityMat);
        CHECK(zeroesMat == -zeroesMat);
        identityMat -= identityMat;
        CHECK(identityMat == zeroesMat);

        vector<double> moreComplexVect = {3, -6.7, 9, 12, -15, 18, 21, 24, 27, 30.3, 33, -36.125};
        vector<double> ansVect = {-3, 6.7, -9, -12, 15, -18, -21, -24, -27, -30.3, -33, 36.125};
        zeroes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        Matrix mat(moreComplexVect, 3, 4);
        Matrix ansMat(ansVect, 3, 4);
        Matrix zeroesBigger(zeroes, 3, 4);
        CHECK(-mat == ansMat);
        CHECK(-mat - ansMat == zeroesBigger);


        vector<double> firstVect = {1, 2, -3, 4, 5, 6.5, 7, 8, 9, 10, -11, 12}; //checking -- before matrix and after matrix.
        //Using the same vectors as with ++
        vector<double> plusPlusVect = {2, 3, -2, 5, 6, 7.5, 8, 9, 10, 11, -10, 13};
        Matrix plusPlusMat(plusPlusVect, 4, 3);
        Matrix OriginMat(firstVect, 4, 3);
        CHECK(plusPlusMat-- != OriginMat);
        CHECK(plusPlusMat == OriginMat);
    }

    SUBCASE("multiplication + equals")
    {
        vector<double> firstVect = {1, 2, -3, 4, 5, 6.5, 7, 8, 9, 10, -11, 12};
        vector<double> ansFirstVect = {3, 6, -9, 12, 15, 19.5, 21, 24, 27, 30, -33, 36};
        Matrix mat1(firstVect, 3, 4);
        Matrix ansMat1(ansFirstVect, 3, 4);

        CHECK(mat1 * 3 == ansMat1);
        CHECK(3 * mat1 == ansMat1);
        CHECK(mat1 * 3 == 3 * mat1);

        CHECK(mat1 * -3 == -ansMat1);
        CHECK((-3) * mat1 == -ansMat1);
    }
}