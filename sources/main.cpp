#include <stdio.h>
#include "Matrix.hpp"

using namespace std;
using namespace zich;

int main()
{
    while (true)
    {
        cout << "Do you want to use the already generated matrices or enter manually? enter 1 for generated, 2 for manual input" << endl;
        int genMan;
        cin >> genMan;
        if (genMan == 1)
        {
            vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
            Matrix mat1(identity, 3, 3);
            vector<double> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            Matrix mat2(arr2, 3, 3);
            cout << "First generated matrix: " << endl << mat1 << endl << endl;
            cout << "Second generated matrix: " << endl << mat2 << endl;

            cout << "Do you want an operation on 1 or 2 matrices? (enter the appropriate number)" << endl;
            int numMat;
            cin >> numMat;

            
        }
        if (genMan == 2)
        {
            cout << "Do you want an operation on 1 or 2 matrices? (enter the appropriate number)" << endl;
            int numMat;
            cin >> numMat;
            if (numMat == 1)
            {
                Matrix mat1{};
                cout << "Enter the matrix in the specified format" << endl;
                cin >> mat1;

                cout << "Which operation would you like to perform? type 1 for unary +, 2 for unary minus, 3 for multiplication by a scalar" << endl;
                int oper;
            }
            else if (numMat == 2)
            {

            }
        }
    }
    return 0;
}