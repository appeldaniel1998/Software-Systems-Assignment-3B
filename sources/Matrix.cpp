#include "Matrix.hpp"
using namespace std;

namespace zich
{
    Matrix::Matrix()
    {}
    Matrix::Matrix(std::vector<double> matAsVector, int rows, int cols)
    {
        if (rows <= 0 || cols <= 0 || rows * cols != matAsVector.size())
        {
            __throw_invalid_argument("rows or columns are negative or 0 or the dimensions do not match the vector given");
        }
        vector<vector<double>> mat;
        for (size_t i = 0; i < rows; i++)
        {
            vector<double> ithRow;
            for (size_t j = 0; j < cols; j++)
            {
                ithRow.push_back(matAsVector.at(i*size_t(cols) + j)); //appending to vector
            }
            mat.push_back(ithRow);
        }
        this->matrix = mat;
    }
    
    Matrix::Matrix(const Matrix& other) //copy constructor
    {
        vector<vector<double>> mat;
        for (size_t i = 0; i < other.matrix.size(); i++)
        {
            vector<double> ithRow;
            for (size_t j = 0; j < other.matrix[0].size(); j++)
            {
                ithRow.push_back(other.matrix.at(i).at(j));
            }
            mat.push_back(ithRow);
        }
        this->matrix = mat;
    }
    
    Matrix::~Matrix()
    {

    }
    
    bool Matrix::inputValidation(const Matrix& other) const //verifying matrices are of the same size (returning boolean)
    {
        return (this->matrix.size() == other.matrix.size() && this->matrix.at(0).size() == other.matrix.at(0).size());
    }
    
    Matrix Matrix::operator+(const Matrix& other) const //addition of 2 matrices by value
    {
        if (!(this->inputValidation(other)))
        {
            __throw_invalid_argument("The matrices are not of the same size");
        }

        Matrix answer(other);
        for (size_t i = 0; i < this->matrix.size(); i++) //iterating over the matrix
        {
            for (size_t j = 0; j < this->matrix.at(0).size(); j++)
            {
                answer.matrix.at(i).at(j) += this->matrix.at(i).at(j);
            }
        }
        return answer;
    }

    Matrix Matrix::operator+=(const Matrix& other)
    {
        *this = *this + other;
        return *this;
    }

    Matrix Matrix::operator+() const //returning a copy of the matrix
    {
        return Matrix(*this);
    }

    
    Matrix Matrix::operator-(const Matrix& other) const //subtraction of matrices (have to be of identical shape)
    {
        if (!(this->inputValidation(other)))
        {
            __throw_invalid_argument("The matrices are not of the same size");
        }

        Matrix answer(*this);
        for (size_t i = 0; i < this->matrix.size(); i++) //iterating over the matrix
        {
            for (size_t j = 0; j < this->matrix.at(0).size(); j++)
            {
                answer.matrix.at(i).at(j) -= other.matrix.at(i).at(j);
            }
        }
        return answer;
    }
    
    Matrix Matrix::operator-=(const Matrix& other)
    {
        *this = *this - other;
        return *this;
    }
    
    Matrix Matrix::operator-() const
    {
        Matrix mat(*this);
        return mat * (-1);
    }

    
    Matrix Matrix::operator++() //adding 1 to every value in the matrix - prefix
    {
        for (size_t i = 0; i < this->matrix.size(); i++)
        {
            for (size_t j = 0; j < this->matrix.at(0).size(); j++)
            {
                this->matrix.at(i).at(j) += 1;
            }
        }
        return *this;
    }
    
    Matrix Matrix::operator++(int) //subtracting 1 to every value in the matrix - postfix
    {
        Matrix temp = *this;
        ++(*this);
        return temp;
    }
    
    Matrix Matrix::operator--() //adding 1 to every value in the matrix - prefix
    {
        for (size_t i = 0; i < this->matrix.size(); i++)
        {
            for (size_t j = 0; j < this->matrix.at(0).size(); j++)
            {
                this->matrix.at(i).at(j) -= 1;
            }
        }
        return *this;
    }
    
    Matrix Matrix::operator--(int) //subtracting 1 to every value in the matrix - postfix
    {
        Matrix temp = *this;
        --(*this);
        return temp;
    }


    Matrix Matrix::operator*(const double value) const //multiplying every value in the matrix by a double number
    {
        Matrix mat(*this);
        for (size_t i = 0; i < this->matrix.size(); i++) //iterating over the matrix, updating and returning a copy of the matrix
        {
            for (size_t j = 0; j < this->matrix.at(0).size(); j++)
            {
                mat.matrix.at(i).at(j) *= value;
            }
        }
        return mat;
    }

    Matrix Matrix::operator*=(const double value)
    {
        *this = *this * value;
        return *this;
    }
    
    Matrix Matrix::operator*(const Matrix& other) const // matrix multiplication as defined in linear algebra
    {
        vector<double> arrMat(this->matrix.size() * other.matrix.at(0).size(), 0);
        Matrix ans(arrMat, this->matrix.size(), other.matrix.at(0).size()); //initializing a matrix of the correct size with zeroes in place of every value

        if (this->matrix.at(0).size() != other.matrix.size())
        {
            __throw_invalid_argument("The matrices cannot be multiplied due to their sizes");
        }

        for(size_t rows = 0; rows < this->matrix.size(); rows++) //iterating over rows of left matrix
        {
            for (size_t cols = 0; cols < other.matrix.at(0).size(); cols++) //iterating over cols of right matrix
            {
                for (size_t i = 0; i < other.matrix.size(); i++) //iterating over rows of right matrix
                {
                    ans.matrix.at(rows).at(cols) += (this->matrix.at(rows).at(i) * other.matrix.at(i).at(cols)); //updating a copy of the new matrix
                }
            }
        }
        return ans;
    }
    
    Matrix Matrix::operator*=(const Matrix& other)
    {
        *this = *this * other;
        return *this;
    }


    bool Matrix::operator==(const Matrix& other) const //matrices are equal iff every value is identical
    //Check the matrices are of the same dimentions
    {
        if (!(this->inputValidation(other)))
        {
            __throw_invalid_argument("The matrices are not of the same size");
        }

        for (size_t i = 0; i < this->matrix.size(); i++) //iterating over the matrix
        {
            for (size_t j = 0; j < this->matrix.at(0).size(); j++)
            {
                if (this->matrix.at(i).at(j) != other.matrix.at(i).at(j)) //if inequality found, return false
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool Matrix::operator!=(const Matrix& other) const //contrast to ==
    {
        return !(*this == other);
    }
    
    vector<double> Matrix::sumsCounter(const Matrix& other) const //function to calculate the sum of all elements in the respective matrices
    {
        if (!(this->inputValidation(other)))
        {
            __throw_invalid_argument("The matrices are not of the same size");
        }

        double sumThis = 0; //sum of current matrix
        double sumOther = 0; //sum of the other matrix
        for (size_t i = 0; i < other.matrix.size(); i++) //verified the matrices are of the same size, iterating over both to save runtime
        {
            for (size_t j = 0; j < other.matrix.at(0).size(); j++)
            {
                sumThis += this->matrix.at(i).at(j);
                sumOther += other.matrix.at(i).at(j);
            }
        }
        vector<double> ret = {sumThis, sumOther}; //returning a vector of size 2 containg the 2 sums
        return ret;
    }

    bool Matrix::operator<(const Matrix& other) const //inequality holds by comparison of the sum of the matrix values
    {
        vector<double> sums = (*this).sumsCounter(other);
        
        return sums.at(0) < sums.at(1);
    }

    bool Matrix::operator<=(const Matrix& other) const //inequality holds by comparison of the sum of the matrix values
    {
        vector<double> sums = (*this).sumsCounter(other);
        
        return sums.at(0) <= sums.at(1);
    }

    bool Matrix::operator>(const Matrix& other) const //inequality holds by comparison of the sum of the matrix values
    {
        vector<double> sums = (*this).sumsCounter(other);
        
        return sums.at(0) > sums.at(1);
    }
    
    bool Matrix::operator>=(const Matrix& other) const //inequality holds by comparison of the sum of the matrix values
    {
        vector<double> sums = (*this).sumsCounter(other);
        
        return sums.at(0) >= sums.at(1);
    }


    ostream& operator<<(ostream& output, const Matrix& mat) //Printing the matrix
    {
        for (size_t i = 0; i < mat.matrix.size(); i++)
        {
            output << "[";
            output << mat.matrix.at(i).at(0);
            for (size_t j = 1; j < mat.matrix.at(0).size(); j++)
            {
                output << " " << mat.matrix.at(i).at(j);
            }
            output << "]";

            if (i != mat.matrix.size() - 1) //if not the last line, print a newline character
            {
                output << endl;
            }
        }
        return output;
    }

    istream &operator>>(istream &input, Matrix &mat) //receiving the matrix as input from the user. 
    {
        string inputStr(std::istreambuf_iterator<char>(input), {});
        vector<double> matArr;
        int rows = 0;
        int cols = 0;

        while (inputStr.length() != 0)
        {
            cols = 0;
            if (inputStr.at(0) != '[')
            {
                __throw_invalid_argument("The input is not of the correct format");
            }

            string row = inputStr.substr(1, inputStr.find(']')); //row without [ and ]
            if (row.find(' ') == string::npos) //only 1 number is row
            {
                double num = stod(row.substr(0, row.length())); //converting substring to double value
                matArr.push_back(num);
                cols = 1;
            } else
            {
                double num = 0;
                while (row.length() != 0)
                {
                    if (row.find(' ') != string::npos) //if space exists in row
                    {
                        num = stod(row.substr(0, row.find(' '))); //converting substring to double value
                        row = row.substr(row.find(' ')+1, row.length()); //reducing row length
                    } else
                    {
                        num = stod(row.substr(0, row.length())); //converting substring to double value
                        row = ""; //reducing row length to 0 //exits the loop at next iteration - finished reading row
                    }
                    matArr.push_back(num);
                    cols++; //counting cols
                }
            }
            rows++; //counting rows

            if (inputStr.substr(inputStr.find(']') + 1) != "\n" && inputStr.substr(inputStr.find(']') + 1, 2) != ", ")
            {
                __throw_invalid_argument("The input is not of the correct format");
            }
            else
            {
                if (inputStr.substr(inputStr.find(']') + 1) == "\n") //finished reading the whole matrix, exits loops
                {
                    inputStr = "";
                }
                else
                {
                    inputStr = inputStr.substr(inputStr.find(']') + 3, inputStr.length()); //reducing string size, row has been read
                }
            }
        }

        mat = Matrix(matArr, rows, cols); //creating the new matrix based on the array and the rows and cols counted
        return input;
    }


    Matrix operator*(const double value, Matrix& other)
    {
        return other * value;
    }
}