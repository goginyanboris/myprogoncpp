// CardsList.cpp: определяет точку входа для консольного приложения.
/*Создать класс Карточка (библиотечная, кадрова и т.п.).
    - Создать список (однонаправленный или двунаправленный) из карточек (хранить первый и/или последний элемент, например).
    - Реализовать следующие функции:
        · создание пустого списка
        · создание элемента списка (данные из консоли)
        · добавление карточки в конец списка (или в начало)
        · включение карточки после текущей
        · поиск карточки (по указателю, по ключу, по имени..)
        · удаление карточки из списка (последней, первой или по ключу)
        · изменение карточки и отдельных её полей
        · печать карточки (в консоль)
        · печать всего списка
        · загрузка списка из файла
        · сохранение списка в файл
        При этом карточка обязательно должна содержать данные с типом char. */

#include <Windows.h> //это набор функций (API – Application Programming Interface), работающих под управлением ОС Windows.
#include <iostream> //заголовочный файл с классами, функциями и переменными для организации ввода-вывода
#include <fstream> //заголовочный файл с классами, функциями и переменными для организации файлового ввода-вывода
#include <stdlib.h> //содержит в себе функции, занимающиеся выделением памяти, контролем процесса выполнения программы, преобразованием типов
#include <stddef.h>//  заголовочный файл стандартной библиотеки языка программирования С, определяющий макросы NULL и offsetof, а также типы ptrdiff_t, wchar t и size_t.
#include <string> // строки
#include <cstring> //несколько функций для обработки Cи-строк и массивов.

using namespace std;

// класс Карточка
// содержит данные о книге: заголовок, автор, год издания

class Card
{
private:
    char *m_title;  // Заголовок книги
    char *m_author; // Автор книги
    int   m_year;   // год издания

public:
	Card(void) //конструктор
	{
	    nextCard = NULL;
        prevCard = NULL;

        m_title = NULL;
        m_author = NULL;
        m_year = 0;
	}

	~Card(void){  //деструктор
        if (m_title)
        {
            delete[] m_title;
            m_title = NULL;
        }
        if (m_author)
        {
            delete[] m_author;
            m_author = NULL;
        }
	}

    Card *prevCard; // указатель на предыдущий элемент списка
    Card *nextCard; // указатель на следующий элемент списка

    void SetTitle(const char *);		// изменить заголовок
    void SetAuthor(const char *);	// изменить автора
    void SetYear(const int);			// изменить год издания

    void GetTitle(char **);	// получить заголовок
    void GetAuthor(char **);	// получить автора
    void GetYear(int &);		// получить год издания

	void Show(); // печать карточки в консоль

};

/*Изменение заголовка*/
void Card::SetTitle(const char *title)
{
    if (title)
    {
        if (m_title)
		{
			delete[] m_title;
			m_title = NULL;
		}

		m_title = new char [strlen(title) + 1];
        strcpy(m_title, title);
    }
}

/*Изменение автора*/
void Card::SetAuthor(const char *author)
{
    if (author)
    {
        if (m_author)
		{
			delete[] m_author;
			m_author = NULL;
		}

		m_author = new char [strlen(author) + 1];
        strcpy(m_author, author);
    }
}

/*Изменение года*/
void Card::SetYear(const int year)
{
    m_year = year;
}

/*Получение заголовка*/
void Card::GetTitle(char **title)
{
    *title = new char [strlen(m_title) + 1];
    strcpy(*title, m_title);
}

/*Получение автора*/
void Card::GetAuthor(char **author)
{
    *author = new char [strlen(m_author) + 1];
    strcpy(*author, m_author);
}

/*Получение Года*/
void Card::GetYear(int &year)
{
    year = m_year;
}

/*Показ карточки*/
void Card::Show()
{
    cout << "Заголовок книги: " << m_title << endl;
    cout << "Автор книги: " << m_author << endl;
    cout << "Год выхода: " << m_year << endl;
}

// Двунаправленный список Карточек

class CardsList
{
public:
    CardsList(); //Конструктор
    ~CardsList(); //Деструктор

	void Insert(const Card *);	// вставить карточку после текущей
    void Prepend(const Card *);	// вставить карточку в начало списка
    void Append(const Card *);	// вставить карточку в конец списка

	void RemoveFirst();			// удалить первый элемент списка
	void RemoveLast();			// удалить последний элемент списка
	void RemoveAt(const int );	// удаление карточки по номеру

    void Show();	// печать всего списка в консоль

	bool SearchByIndex(const int , Card &);// ищет карточку по номеру index и заносит найденный результат в
                                                          // findedCard. если карточка найдена, возвращает true, иначе false

	int SearchByAuthor(const char *, CardsList &);// ищет карточкb по автору author и формирует из найденных результатов
                                                                   // список findedCards. возвращает число найденных карточек

	void SaveToFile(const string );		// сохранить список в файл
	void LoadFromFile(const string );	// загрузить список из файла

private:
    Card *m_first;		// указатель на первый элемент списка
    Card *m_last;		// указатель на последний элемент списка
    Card *m_current;	// указатель на текущий элемент списка

    void copyCard(Card *, Card *); // поля из карточки srcCard в dstCard
	void clearList(); // очистить список
};

/*Конструктор*/
CardsList::CardsList()
{
    m_first = NULL;
    m_last = NULL;
    m_current = NULL;
}

/*Деструктор*/
CardsList::~CardsList()
{
    clearList();
}

/*Вставка после текущего*/
void CardsList::Insert(const Card *card)
{
	Card *newCard = new Card;			// создаём новый элемент списка
    copyCard((Card *)card, newCard);	// заполняем поля нового элемента

	// если текущий элемент уже существует,
	if (m_current != NULL)
	{
		// копируем из него ссылку на следующий
		newCard->nextCard = m_current->nextCard;
		// и привязываем перед новым элементом
		m_current->nextCard = newCard;
		newCard->prevCard = m_current;
	}

	if (m_first == NULL)	// если первый элемент ещё не сохранён сохраняем новый элемент в качестве первого
		m_first = newCard;

	// если последний элемент ещё не сохранён
	// или последний элемент является текущим
	// сохраняем новый элемент в качестве последнего
	if (m_last == NULL || m_last == m_current)
		m_last = newCard;


	m_current = newCard;// сохраняем новый элемент в качестве текущего
}

/*Вставка в начало*/
void CardsList::Prepend(const Card *card)
{
	Card *newCard = new Card;			// создаём новый элемент списка
    copyCard((Card *)card, newCard);	// заполняем поля нового элемента

	// если первый элемент уже сохранён
	if (m_first != NULL)
	{
		// связываем его с новым элементом
		m_first->prevCard = newCard;
		newCard->nextCard = m_first;
	}

	// запоминаем новый элемент в качестве первого и текущего
    m_first = newCard;
	m_current = newCard;
}

/*Вставка в конец*/
void CardsList::Append(const Card *card)
{
	Card *newCard = new Card;			// создаём новый элемент списка
    copyCard((Card *)card, newCard);	// заполняем поля нового элемента

	// если последний элемент уже сохранён
	if (m_last != NULL)
	{
		// связываем его с новым элементом
		m_last->nextCard = newCard;
        newCard->prevCard = m_last;
	}

	// запоминаем новый элемент в качестве последнего и текущего
    m_last = newCard;
	m_current = newCard;
}

/*Удаление первого*/
void CardsList::RemoveFirst()
{
	if (m_first)
	{
		// отвязываем первый элемент от следующего за ним
		Card *temp = m_first->nextCard;
		if (temp != NULL)
			temp->prevCard = NULL;

		// если первый элемент был текущим, делаем текущим следующий
		if (m_current == m_first)
			m_current = temp;

		delete m_first; // освобождаем память
		m_first = temp; // запоминаем следующий элемент как первый
	}
}

/*Удаляем последний*/
void CardsList::RemoveLast()
{
	if (m_last)
	{
		// отвязываем последний элемент от следующего за ним
		Card *temp = m_last->prevCard;
		if (temp != NULL)
			temp->nextCard = NULL;

		// если последний элемент был текущим, делаем текущим предыдущий
		if (m_current == m_last)
			m_current = temp;

		delete m_last; // освобождаем память
		m_last = temp; // запоминаем предыдущий элемент как последний
	}
}

/*Удаление по номеру*/
void CardsList::RemoveAt(const int index)
{
	Card *temp = m_first;	// временно указываем на адрес первого элемента
    int counter = 0;		// счётчик элементов списка

    while (temp != NULL)
    {
		// если значение счётчика меньше заданного индекса
		if (counter < index)
		{
			// переходим к следующему элементу, увеличиваем
			// значение счётчика и пропускаем шаг
			temp = temp->nextCard;
			counter ++;
			continue;
		}

		// дошли до нужного элемента
		// запоминаем элементы до и после него
		Card *tempPrev = temp->prevCard;
		Card *tempNext = temp->nextCard;

		if (tempPrev != NULL)				// если предыдущий существует
			tempPrev->nextCard = tempNext;	// связываем его со следующим
		else								// иначе
			m_first = tempNext;				// запоминаем следующий как первый

		if (tempNext != NULL)				// если следующий существует
			tempNext->prevCard = tempPrev;	// связываем его с предыдущим
		else								// иначе
			m_last = tempPrev;				// запоминаем предыдущий как последний

		if (m_current == temp)		// если удаляемый элемент является текущим
			m_current = m_first;	// делаем текущим первый

		delete temp; // освобождаем память
		temp = NULL;
    }
}

/*Печать списка*/
void CardsList::Show()
{
    //ВЫВОДИМ СПИСОК С НАЧАЛА
    Card *temp = m_first;	// Временно указываем на адрес первого элемента
    int counter = 0;
    cout << "Содержимое списка:" << endl;
	while (temp != NULL) // Пока не встретим пустое значение
    {
        cout << "Карточка №" << counter ++ << endl;	// выводим порядковый номер карточки
		temp->Show();								// и значения её полей
        cout << "~~~" << endl; // разделитель
        temp = temp->nextCard;       // Смена адреса на адрес следующего элемента
    }
	cout << "Итого записей: " << counter << endl; // выводим общее количество сохранённых карточек
}


/*Поиск по индексу*/
bool CardsList::SearchByIndex(const int index, Card &findedCard)
{
	Card *temp = m_first; // Временно указываем на адрес первого элемента
    int counter = 0;
    bool isFinded = false;
	// ищем пока не нашли или не дошли до конца
    while (temp != NULL && !isFinded)
    {
		if (counter < index)	// пока не дошли до заданного номера
		{						// переходим к следующей записи и увеличиваем счётчик
			temp = temp->nextCard;
			counter ++;
			continue;
		}
		// дошли до нужной записи
		copyCard(temp, &findedCard);	// сохраняем в результат значения полей
		isFinded = true;				// включаем флаг для завершения поиска
    }
	return isFinded;
}

/*Поиск по автору*/
int CardsList::SearchByAuthor(const char *s_author, CardsList &findedCards)
{
	Card *temp = m_first; // Временно указываем на адрес первого элемента
    int findedCount = 0;
	bool isFinded = false;
    char *author = NULL;
    int year = 0;
    // ищем пока не нашли или не дошли до конца
    while (temp != NULL && !isFinded)
    {
		// считываем значение поля Автор
		author = NULL;
        temp->GetAuthor(&author);
		// если поле Автор содержит искомую фамилию
		if (strstr(author, s_author) != NULL)
		{
			findedCards.Insert(temp);	// добавляем карточку к списку результатов
			findedCount ++;				// увеличиваем счётчик найденных элементов
		}

		// переходим к следующему элементу
		temp = temp->nextCard;
        delete[] author;
    }
	// возвращаем количество найденных элементов
	return findedCount;
}

/*Сохранение в файл*/
void CardsList::SaveToFile(const string fileName)
{
	// отктываем файл для записи
	FILE *outFile = NULL;
	outFile = fopen(fileName.c_str(), "w");
	if (outFile == NULL)
	{
		printf("Ошибка открытия файла %s", fileName.c_str());
		return;
	}

	Card *temp = m_first;        // Временно указываем на адрес первого элемента
	int counter = 0;
	char *title = NULL;
	char *author = NULL;
	int year = 0;
	while (temp != NULL)         // Пока не встретим пустое значение
	{
		title = NULL;
		author = NULL;
		// считываем значения полей
		temp->GetTitle(&title);
		temp->GetAuthor(&author);
		temp->GetYear(year);
		// записываем их в файл
		fprintf(outFile, "%s\n", title);
		fprintf(outFile, "%s\n", author);
		fprintf(outFile, "%d\n", year);
		delete[] title;
		delete[] author;
		temp = temp->nextCard;       // Смена адреса на адрес следующего элемента
	}
	// закрываем файл
	fflush(outFile);
	fclose(outFile);
}


/*Загрузка из файла*/
void CardsList::LoadFromFile(const string fileName)
{
	// поток для чтения из файла
	ifstream infile(fileName.c_str());
	string title;
    string author;
    string year;
	// очищаем список
	clearList();
	// пока не достигли конца файла
	while (!infile.eof())
	{
		// построчно считывам значения полей
		getline(infile, title);
		getline(infile, author);
		getline(infile, year);
		if (title.length() == 0 ||
			author.length() == 0)
			continue;
		// заносим значения полей в карточку
		Card *card = new Card;
		card->SetTitle((char *)title.c_str());
		card->SetAuthor((char *)author.c_str());
		card->SetYear(atoi(year.c_str()));
		// добавляем карточку в список
		Insert(card);
		delete card;
	}
	return;
}

/*Копия*/
void CardsList::copyCard(Card *srcCard, Card *dstCard)
{
    char *title = NULL;
    char *author = NULL;
    int year = 0;
	// получаем значения полей из srcCard
    srcCard->GetTitle(&title);
    srcCard->GetAuthor(&author);
    srcCard->GetYear(year);
	// устанавливаем значения полей в dstCard
    dstCard->SetTitle(title);
    dstCard->SetAuthor(author);
    dstCard->SetYear(year);
    delete[] title;
    delete[] author;
}

/*Очистка*/
void CardsList::clearList()
{
	while (m_first) //Пока по адресу на начало списка что-то есть
    {
        m_last = m_first->nextCard;  // Резервная копия адреса следующего звена списка
        delete m_first;              // Очистка памяти от первого звена
        m_first = m_last;            // Смена адреса начала на адрес следующего элемента
    }
	m_first = NULL;
	m_last = NULL;
	m_current = NULL;
}


//_______________________________________________________________________________________________________________________________

char *title; //Заголовок книги


void FillCard(Card *card);
//void ShowCard(Card *card);

int main()
{
    //Настройка консоли на кириллицу
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	// создание пустого списка
    CardsList *cardList = new CardsList;
	Card *card = NULL;
    int count = 0;
    cout << "Задайте количество карточек (0 для перехода к загрузке из файла) : ";
    cin >> count; // Получаем количество элементов списка
	if (count > 0)
	{
		for (int c = 0; c < count; c ++)
		{
			cout << endl << "Заполните " << c << "-ю карточку: " << endl;
			// создание элемента списка
			card = new Card;
			FillCard(card);
			cardList->Insert(card);
			delete card;
		}
	}
	else
	{
		cout << "Введите имя файла для загрузки списка:" << endl;
		cin.get();
		string inFileName;
		getline(cin, inFileName);
		cardList->LoadFromFile(inFileName);
	}
    cout << endl << endl;
	cardList->Show(); //Отображаем список на экране
    cout << endl;

    int action;
    Card iCard;
    int index = 0;
    string author;
    CardsList findedList;
    int r;
    int rn = 0;
    do {
    cout << endl;
    cout << "Выбери функцию:" << endl;
    cout << "1. Добавление карточки в конец списка" << endl;
    cout << "2. Добавление карточки в начало списка" << endl;
    cout << "3. Добавление карточки после текущей" << endl;
    cout << "4. Поиск карточки по индексу (номерация от 0) -> " << endl;
    cout << "5. Поиск карточки по автору" << endl;
    cout << "6. Удаление первого элемента списка:" << endl;
    cout << "7. Удаление последнего элемента списка:" << endl;
    cout << "8. Удаление элемента списка по номеру:" << endl;
    cout << "9. Сохранение в файл:" << endl;
    cout << "10. Выход" << endl;
    cout << "Выбрать функцию: ";
    cin >> action;
    cout << endl;

    switch (action)
    {
    case 1:
        cout << "Добавление карточки в конец списка:" << endl;
        card = new Card;
        FillCard(card);
        cardList->Append(card);
        delete card;

        cardList->Show(); //Отображаем список на экране
        cout << endl;
        break;

    case 2:
        cout << "Добавление карточки в начало списка:" << endl;
        card = new Card;
        FillCard(card);
        cardList->Prepend(card);
        delete card;

        cardList->Show(); //Отображаем список на экране
        cout << endl;
        break;

    case 3:
        cout << "Добавление карточки после текущей:" << endl;
        card = new Card;
        FillCard(card);
        cardList->Insert(card);
        delete card;

        cardList->Show(); //Отображаем список на экране
        cout << endl;
        break;

    case 4:
        //int index = 0;
        cout << "Задайте индекс для поиска карточки (номерация от 0) -> ";
        cin >> index; // Получаем количество элементов списка

        //Card iCard;
        if (cardList->SearchByIndex(index, iCard))
        {
            cout << "Найдена карта:" << endl;
            iCard.Show();
        }
        else
            cout << "Карта не найдена" << endl;
        cout << endl;
        break;

    case 5:
        cout << "Введите автора для поиска карточек:" << endl;
        cin.get(); //считывание символа
        getline(cin, author);
        r = cardList->SearchByAuthor(author.c_str(), findedList);
        if (r > 0)
        {
            cout << "Найдено " << r << " совпадений:" << endl;
            findedList.Show();
        }
        break;

    case 6:
        cout << "Удаление первого элемента списка:" << endl;
        cardList->RemoveFirst();
        cardList->Show(); //Отображаем список на экране
        cout << endl;
        break;

    case 7:
        cout << "Удаление последнего элемента списка:" << endl;
        cardList->RemoveLast();
        cardList->Show(); //Отображаем список на экране
        cout << endl;
        break;

    case 8:
        //int rn = 0;
        cout << "Задайте номер элемента для удаления из списка (номерация от 0) -> ";
        cin >> rn; // Получаем количество элементов списка
        cardList->RemoveAt(rn);
        cardList->Show(); //Отображаем список на экране
        cout << endl;
        break;

    case 9:
        cout << "Введите имя файла для сохранения списка:" << endl;
        cin.get();

        string outFileName;
        getline(cin, outFileName);
        cardList->SaveToFile(outFileName);
        break;
    }
    }
    while (action!=10);
	delete cardList;

	system("PAUSE");
    return 0;
}

void FillCard(Card *card)
{
	cin.get();

	string title;
    string author;
    int year;

	cout << "Автор книги: ";
    getline(cin, author);

    cout << "Заголовок книги: ";
    getline(cin, title);

    cout << "Год выхода книги: ";
    cin >> year;

    card->SetTitle((char *)title.c_str());
    card->SetAuthor((char *)author.c_str());
    card->SetYear(year);
}

void ShowCard(Card *card)
{
	char *title = NULL;
    char *author = NULL;
    int year = 0;

	card->GetTitle(&title);
    card->GetAuthor(&author);
    card->GetYear(year);

    cout << "Заголовок книги: " << title << endl;
    cout << "Автор книги: " << author << endl;
    cout << "Год выхода: " << year << endl;
	cin.get();
}
