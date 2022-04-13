#include<vector>
#include<iostream>

namespace zich
{
    class Matrix
    {
        std::vector<std::vector<double>> matrix;

        public:
            Matrix(std::vector<double> matAsVector, int rows, int cols);
            Matrix(const Matrix& other);
            ~Matrix();

            Matrix operator+(const Matrix& other) const;
            Matrix operator+=(const Matrix& other);
            Matrix operator+() const;

            Matrix operator-(const Matrix& other) const;
            Matrix operator-=(const Matrix& other);
            Matrix operator-() const;

            Matrix operator++();
            Matrix operator++(int);
            Matrix operator--();
            Matrix operator--(int);

            Matrix operator*(const double value) const;
            Matrix operator*=(const double value);
            Matrix operator*(const Matrix& other) const;
            Matrix operator*=(const Matrix& other);

            bool operator==(const Matrix& other) const;
            bool operator!=(const Matrix& other) const;
            bool operator<(const Matrix& other) const;
            bool operator<=(const Matrix& other) const;
            bool operator>(const Matrix& other) const;
            bool operator>=(const Matrix& other) const;

            friend std::ostream& operator<<(std::ostream& output, const Matrix& mat);
            friend std::istream& operator>>(std::istream& input, Matrix& mat);

        private:
            std::vector<double> sumsCounter(const Matrix& other) const;
            bool inputValidation(const Matrix& other) const;
    };
    

    Matrix operator*(const double value, Matrix& other);
};