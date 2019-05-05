/*Необходимо реализовать шаблон списка L, который содержит объекты произвольного типа.
Список должен обладать свойствами и функциями из пункта 1, а также необходимым набором конструкторов и деструкторов.

1. Добавление(Только в конец); Удаление(Только с конца); Индексация - Есть

Поместить в список объекты типа D из пункта 2 и реализовать требуемые действия,
попутно написав требуемые функции для класса D.

2. D – комплексные числа. Реализовать быструю сортировку.

Добавить необходимый набор классов ошибок (иерархия классов не менее 2-х уровней) и их обработку.*/

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

// классы ошибок
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
struct element //Структура с инфополями и адресным полем
{
 Tin x; //Инфополе, значения из x будут передаваться в список
 element *Next; //Адресное поле
 unsigned long int num = 0; //индекс
};
template<typename Tin>
class List //Класс Список
{
 element<Tin> *Head; //Указатель на последний активный элемент или просто голова списка
 public:

  List() //Конструктор и инициализация указателя пустым значением
  {
    Head = NULL;
  }

 ~List(){ //Деструктор.
    while (Head != NULL)  //Пока по адресу не пусто
     {
        element<Tin> *temp = Head->Next; //Временная переменная для хранения адреса следующего элемента
        delete Head; //Освобождаем адрес обозначающий начало
        Head = temp; //Меняем адрес на следующий
     }
 }
 void operator +(Tin*);//прототип метода класса в котором мы перегрузим оператор +
 void operator --();
 void Show(); //Функция для отображения списка на экране
 void ReadM(); // функция переписи списка
 // void quickSort(vector<Tin> &, int , int );
};


template<typename Tin>                            // добавление элемента х в конец
void List<Tin>::operator +(Tin *x)
{
 element<Tin> *temp = new element<Tin>; // При каждом вызове выделяется память
 temp->x = *x; // Записываем x в элемент структуры  element (в x структуры element)
 temp->Next = Head; // Указываем, что след. элемент это объект по адресу Head
 if(Head != NULL){
    temp->num = Head->num + 1;
 }
 Head = temp; // Указываем, что последний активный элемент это только что введенный

}
template<typename Tin>                             // удаление элемента с конца
void List<Tin>::operator --()
{
    if(Head == NULL){
        throw DelemptyListException();
    }
    else{
    element<Tin> *temp = Head->Next; //Временная переменная для хранения адреса следующего элемента
    delete Head; //Освобождаем адрес обозначающий начало
    Head = temp; //Меняем адрес на следующий
    }
}

template<typename Tin>                              //Функция отображения списка на экране
void List<Tin>::Show()
{
 element<Tin> *temp = Head; //Определяем указатель, который изначально равен адресу начала списка

 while (temp != NULL) //До тех пор пока не встретит пустое значение
 {
  cout<< temp->num << ". " << temp->x << endl; //Выведет элемент x из списка
  temp = temp->Next; //Указываем, что далее нам нужен следующий элемент
 }
 cout << endl;
}

template<typename Tin>
double abs(Tin a){
    double b = sqrt((a.real()*a.real()) + (a.imag()*a.imag()));
    return b;
}

template<typename Tin>                            // быстрая сортировка
void quickSort(vector<Tin> &A, int left, int right)
{
    int i = left, j = right;
    double pivot;
    Tin tmp;
    pivot = abs( A[(left + right) / 2] );
    /* перестановки */
    while (i <= j) {
        while (abs( A[i] ) < pivot){
            i++;
        }
        while (abs( A[j] ) > pivot){
            j--;
        }
        if (i <= j) {
            tmp = A[i];
            A[i] = A[j]; // меняем местами элементы
            A[j] = tmp;
            i++;
            j--;
        }
    }

    /* рекурсия */
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
        while (temp != NULL) //перепишем список в массив
        {
            A.insert(A.begin(), temp->x);
            cout<< temp->num << ". " << temp->x << endl ; //Выведет элемент x из списка
            temp = temp->Next;
        }
        cout << endl << "Сортируем..." << endl << endl;
        quickSort(A, 0, A.size() - 1); // сортируем массив
        for(int i =0; i < A.size(); i++){
            cout << A[i] << " ";
        }
        cout << endl;

     // перепись списка
        temp = Head;
        int l = 0;
        while (temp != NULL) //элементы отсортированного массива запишем в temp->x
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
  complex<double> x; //Элементы вводимые в список
  List<complex<double> > lst; //Переменная, тип которой список

while(N != 0)
 {
  setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
  cout << "Введите 0 для завершения работы, 1 - для добавления х в список, 2 - для удаления элемента, 3 - для быстрой сортировки списка" << endl;
  cin >> N; //Ввод действия с клавиатуры
  if (N == 1){
    cout << "Введите действительную и мнимую части: ";
    cin >> a >> b ;
    x.real() = a;
    x.imag() = b;
    lst + &x;
    lst.Show(); //Вывод списка на экран
  }
  else if (N == 2){
        try{
            --lst;
           lst.Show(); //Вывод списка на экран
        }
        catch(DelemptyListException){
            cout << "Ошибка: Удаление из пустого списка" << endl;
        }

  }
  else{
    try{
        lst.ReadM(); // qsort
        lst.Show(); //Вывод списка на экран
    }
    catch(ReademptyListException){
      cout << "Ошибка: Чтение пустого списка" << endl;
    }

  }
 }
return 0;
}
