/*���������� ����������� ������ ������ L, ������� �������� ������� ������������� ����.
������ ������ �������� ���������� � ��������� �� ������ 1, � ����� ����������� ������� ������������� � ������������.

1. ����������(������ � �����); ��������(������ � �����); ���������� - ����

��������� � ������ ������� ���� D �� ������ 2 � ����������� ��������� ��������,
������� ������� ��������� ������� ��� ������ D.

2. D � ����������� �����. ����������� ������� ����������.

�������� ����������� ����� ������� ������ (�������� ������� �� ����� 2-� �������) � �� ���������.*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <set>
#include <complex>
#include <clocale>

using namespace std;

// ������ ������
class DelemptyListException : public exception
{
public:

	virtual const char * what() const throw()
	{
		return "\nCannot delete from empty list.\n";
	}
};

class ReademptyListException : public DelemptyListException
{
public:

	virtual const char * what() const throw()
	{
		return "\nCannot read empty list.\n";
	}
};

/*class lastElementElemException : public emptyListException
{
public:

	virtual const char * what() const throw()
	{
		return "\nAttempt to get previous-to-head or next-to-tail element.\n";
	}
};*/


template<typename Tin>
struct element //��������� � ���������� � �������� �����
{
 Tin x; //��������, �������� �� x ����� ������������ � ������
 element *Next; //�������� ����
 unsigned long int num = 0; //������
};
template<typename Tin>
class List //����� ������
{
 element<Tin> *Head; //��������� �� ��������� �������� ������� ��� ������ ������ ������
 public:

  List() //����������� � ������������� ��������� ������ ���������
  {
    Head = NULL;
  }

 ~List(){ //����������.
    while (Head != NULL)  //���� �� ������ �� �����
     {
        element<Tin> *temp = Head->Next; //��������� ���������� ��� �������� ������ ���������� ��������
        delete Head; //����������� ����� ������������ ������
        Head = temp; //������ ����� �� ���������
     }
 }
 void operator +(Tin*);//�������� ������ ������ � ������� �� ���������� �������� +
 void operator --();
 void Show(); //������� ��� ����������� ������ �� ������
 void ReadM(); // ������� �������� ������
 // void quickSort(vector<Tin> &, int , int );
};


template<typename Tin>                            // ���������� �������� � � �����
void List<Tin>::operator +(Tin *x)
{
 element<Tin> *temp = new element<Tin>; // ��� ������ ������ ���������� ������
 temp->x = *x; // ���������� x � ������� ���������  element (� x ��������� element)
 temp->Next = Head; // ���������, ��� ����. ������� ��� ������ �� ������ Head
 if(Head != NULL){
    temp->num = Head->num + 1;
 }
 Head = temp; // ���������, ��� ��������� �������� ������� ��� ������ ��� ���������

}
template<typename Tin>                             // �������� �������� � �����
void List<Tin>::operator --()
{
    if(Head == NULL){
        throw DelemptyListException();
    }
    else{
    element<Tin> *temp = Head->Next; //��������� ���������� ��� �������� ������ ���������� ��������
    delete Head; //����������� ����� ������������ ������
    Head = temp; //������ ����� �� ���������
    }
}

template<typename Tin>                              //������� ����������� ������ �� ������
void List<Tin>::Show()
{
 element<Tin> *temp = Head; //���������� ���������, ������� ���������� ����� ������ ������ ������

 while (temp != NULL) //�� ��� ��� ���� �� �������� ������ ��������
 {
  cout<< temp->num << ". " << temp->x << endl; //������� ������� x �� ������
  temp = temp->Next; //���������, ��� ����� ��� ����� ��������� �������
 }
 cout << endl;
}

template<typename Tin>
double abs(Tin a){
    double b = sqrt((a.real()*a.real()) + (a.imag()*a.imag()));
    return b;
}

template<typename Tin>                            // ������� ����������
void quickSort(vector<Tin> &A, int left, int right)
{
    int i = left, j = right;
    double pivot;
    Tin tmp;
    pivot = abs( A[(left + right) / 2] );
    /* ������������ */
    while (i <= j) {
        while (abs( A[i] ) < pivot){
            i++;
        }
        while (abs( A[j] ) > pivot){
            j--;
        }
        if (i <= j) {
            tmp = A[i];
            A[i] = A[j]; // ������ ������� ��������
            A[j] = tmp;
            i++;
            j--;
        }
    }

    /* �������� */
    if (left < j){
        quickSort(A, left, j);
    }
    if (i < right){
        quickSort(A, i, right);
    }
}

template<typename Tin>
void List<Tin>::ReadM()
{
    if(Head == NULL){
        throw ReademptyListException();
    }
    else{
    element<Tin> *temp = Head;
    vector<Tin> A;
    Tin tmp;
        while (temp != NULL) //��������� ������ � ������
        {
            A.insert(A.begin(), temp->x);
            cout<< temp->num << ". " << temp->x << endl ; //������� ������� x �� ������
            temp = temp->Next;
        }
        cout << endl << "���������..." << endl << endl;
        quickSort(A, 0, A.size() - 1); // ��������� ������
        for(int i =0; i < A.size(); i++){
            cout << A[i] << " ";
        }
        cout << endl;

     // �������� ������
        temp = Head;
        int l = 0;
        while (temp != NULL) //�������� ���������������� ������� ������� � temp->x
        {
            temp->x = A[l] ;
            temp = temp->Next;
            l++;
        }
    }


}


int main()
{
  int N = 5;;
  double a, b;
  complex<double> x; //�������� �������� � ������
  List<complex<double> > lst; //����������, ��� ������� ������

while(N != 0)
 {
  setlocale(LC_CTYPE, "rus"); // ����� ������� ��������� ������
  cout << "������� 0 ��� ���������� ������, 1 - ��� ���������� � � ������, 2 - ��� �������� ��������, 3 - ��� ������� ���������� ������" << endl;
  cin >> N; //���� �������� � ����������
  if (N == 1){
    cout << "������� �������������� � ������ �����: ";
    cin >> a >> b ;
    x.real() = a;
    x.imag() = b;
    lst + &x;
    lst.Show(); //����� ������ �� �����
  }
  else if (N == 2){
        try{
            --lst;
           lst.Show(); //����� ������ �� �����
        }
        catch(DelemptyListException){
            cout << "������: �������� �� ������� ������" << endl;
        }

  }
  else{
    try{
        lst.ReadM(); // qsort
        lst.Show(); //����� ������ �� �����
    }
    catch(ReademptyListException){
      cout << "������: ������ ������� ������" << endl;
    }

  }
 }
return 0;
}
