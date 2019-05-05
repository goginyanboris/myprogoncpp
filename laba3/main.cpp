/*Реализовать функцию заполнения двумерного массива коэффициентами треугольника Паскаля (тип элементов произвольный)*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void pas(vector<vector<T> > A, int n){

    for(int k = 0; k < n; k++){
        A[k][0] = 1;
        for (int i = 1; i <= k; i++){
            for (int j = i; j >= 1; j--){
                A[k][j] = A[k][j - 1] + A[k][j];  // заполнение треугольника
            }
        }
    }
     for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << A[i][j] << " ";  // вывод получившегося массива
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    // целочисленные типы данных
    vector<vector<int> > A(n, vector<int>(n, 0));
    vector<vector<short int> > B(n, vector<short int>(n, 0));
    vector<vector<unsigned short int> > C(n, vector<unsigned short int>(n, 0));
    vector<vector<unsigned int> > D(n, vector<unsigned int>(n, 0));
    vector<vector<long int> > E(n, vector<long int>(n, 0));
    vector<vector<unsigned long int> > F(n, vector<unsigned long int>(n, 0));

    //типы данных с плавающей точкой
    vector<vector<float> > L(n, vector<float>(n, 0.0));
    vector<vector<double> > M(n, vector<double>(n, 0.0));
    vector<vector<long double> > N(n, vector<long double>(n, 0.0));

    // вызов функции pas

    pas(A, n);
    pas(B, n);
    pas(C, n);
    pas(E, n);
    pas(F, n);

    pas(L, n);
    pas(M, n);
    pas(N, n);

    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }*/
    return 0;
}
