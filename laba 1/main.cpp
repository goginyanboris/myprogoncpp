// CardsList.cpp: ���������� ����� ����� ��� ����������� ����������.
/*������� ����� �������� (������������, ������� � �.�.).
    - ������� ������ (���������������� ��� ���������������) �� �������� (������� ������ �/��� ��������� �������, ��������).
    - ����������� ��������� �������:
        � �������� ������� ������
        � �������� �������� ������ (������ �� �������)
        � ���������� �������� � ����� ������ (��� � ������)
        � ��������� �������� ����� �������
        � ����� �������� (�� ���������, �� �����, �� �����..)
        � �������� �������� �� ������ (���������, ������ ��� �� �����)
        � ��������� �������� � ��������� � �����
        � ������ �������� (� �������)
        � ������ ����� ������
        � �������� ������ �� �����
        � ���������� ������ � ����
        ��� ���� �������� ����������� ������ ��������� ������ � ����� char. */

#include <Windows.h> //��� ����� ������� (API � Application Programming Interface), ���������� ��� ����������� �� Windows.
#include <iostream> //������������ ���� � ��������, ��������� � ����������� ��� ����������� �����-������
#include <fstream> //������������ ���� � ��������, ��������� � ����������� ��� ����������� ��������� �����-������
#include <stdlib.h> //�������� � ���� �������, ������������ ���������� ������, ��������� �������� ���������� ���������, ��������������� �����
#include <stddef.h>//  ������������ ���� ����������� ���������� ����� ���������������� �, ������������ ������� NULL � offsetof, � ����� ���� ptrdiff_t, wchar t � size_t.
#include <string> // ������
#include <cstring> //��������� ������� ��� ��������� C�-����� � ��������.

using namespace std;

// ����� ��������
// �������� ������ � �����: ���������, �����, ��� �������

class Card
{
private:
    char *m_title;  // ��������� �����
    char *m_author; // ����� �����
    int   m_year;   // ��� �������

public:
	Card(void) //�����������
	{
	    nextCard = NULL;
        prevCard = NULL;

        m_title = NULL;
        m_author = NULL;
        m_year = 0;
	}

	~Card(void){  //����������
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

    Card *prevCard; // ��������� �� ���������� ������� ������
    Card *nextCard; // ��������� �� ��������� ������� ������

    void SetTitle(const char *);		// �������� ���������
    void SetAuthor(const char *);	// �������� ������
    void SetYear(const int);			// �������� ��� �������

    void GetTitle(char **);	// �������� ���������
    void GetAuthor(char **);	// �������� ������
    void GetYear(int &);		// �������� ��� �������

	void Show(); // ������ �������� � �������

};

/*��������� ���������*/
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

/*��������� ������*/
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

/*��������� ����*/
void Card::SetYear(const int year)
{
    m_year = year;
}

/*��������� ���������*/
void Card::GetTitle(char **title)
{
    *title = new char [strlen(m_title) + 1];
    strcpy(*title, m_title);
}

/*��������� ������*/
void Card::GetAuthor(char **author)
{
    *author = new char [strlen(m_author) + 1];
    strcpy(*author, m_author);
}

/*��������� ����*/
void Card::GetYear(int &year)
{
    year = m_year;
}

/*����� ��������*/
void Card::Show()
{
    cout << "��������� �����: " << m_title << endl;
    cout << "����� �����: " << m_author << endl;
    cout << "��� ������: " << m_year << endl;
}

// ��������������� ������ ��������

class CardsList
{
public:
    CardsList(); //�����������
    ~CardsList(); //����������

	void Insert(const Card *);	// �������� �������� ����� �������
    void Prepend(const Card *);	// �������� �������� � ������ ������
    void Append(const Card *);	// �������� �������� � ����� ������

	void RemoveFirst();			// ������� ������ ������� ������
	void RemoveLast();			// ������� ��������� ������� ������
	void RemoveAt(const int );	// �������� �������� �� ������

    void Show();	// ������ ����� ������ � �������

	bool SearchByIndex(const int , Card &);// ���� �������� �� ������ index � ������� ��������� ��������� �
                                                          // findedCard. ���� �������� �������, ���������� true, ����� false

	int SearchByAuthor(const char *, CardsList &);// ���� �������b �� ������ author � ��������� �� ��������� �����������
                                                                   // ������ findedCards. ���������� ����� ��������� ��������

	void SaveToFile(const string );		// ��������� ������ � ����
	void LoadFromFile(const string );	// ��������� ������ �� �����

private:
    Card *m_first;		// ��������� �� ������ ������� ������
    Card *m_last;		// ��������� �� ��������� ������� ������
    Card *m_current;	// ��������� �� ������� ������� ������

    void copyCard(Card *, Card *); // ���� �� �������� srcCard � dstCard
	void clearList(); // �������� ������
};

/*�����������*/
CardsList::CardsList()
{
    m_first = NULL;
    m_last = NULL;
    m_current = NULL;
}

/*����������*/
CardsList::~CardsList()
{
    clearList();
}

/*������� ����� ��������*/
void CardsList::Insert(const Card *card)
{
	Card *newCard = new Card;			// ������ ����� ������� ������
    copyCard((Card *)card, newCard);	// ��������� ���� ������ ��������

	// ���� ������� ������� ��� ����������,
	if (m_current != NULL)
	{
		// �������� �� ���� ������ �� ���������
		newCard->nextCard = m_current->nextCard;
		// � ����������� ����� ����� ���������
		m_current->nextCard = newCard;
		newCard->prevCard = m_current;
	}

	if (m_first == NULL)	// ���� ������ ������� ��� �� ������� ��������� ����� ������� � �������� �������
		m_first = newCard;

	// ���� ��������� ������� ��� �� �������
	// ��� ��������� ������� �������� �������
	// ��������� ����� ������� � �������� ����������
	if (m_last == NULL || m_last == m_current)
		m_last = newCard;


	m_current = newCard;// ��������� ����� ������� � �������� ��������
}

/*������� � ������*/
void CardsList::Prepend(const Card *card)
{
	Card *newCard = new Card;			// ������ ����� ������� ������
    copyCard((Card *)card, newCard);	// ��������� ���� ������ ��������

	// ���� ������ ������� ��� �������
	if (m_first != NULL)
	{
		// ��������� ��� � ����� ���������
		m_first->prevCard = newCard;
		newCard->nextCard = m_first;
	}

	// ���������� ����� ������� � �������� ������� � ��������
    m_first = newCard;
	m_current = newCard;
}

/*������� � �����*/
void CardsList::Append(const Card *card)
{
	Card *newCard = new Card;			// ������ ����� ������� ������
    copyCard((Card *)card, newCard);	// ��������� ���� ������ ��������

	// ���� ��������� ������� ��� �������
	if (m_last != NULL)
	{
		// ��������� ��� � ����� ���������
		m_last->nextCard = newCard;
        newCard->prevCard = m_last;
	}

	// ���������� ����� ������� � �������� ���������� � ��������
    m_last = newCard;
	m_current = newCard;
}

/*�������� �������*/
void CardsList::RemoveFirst()
{
	if (m_first)
	{
		// ���������� ������ ������� �� ���������� �� ���
		Card *temp = m_first->nextCard;
		if (temp != NULL)
			temp->prevCard = NULL;

		// ���� ������ ������� ��� �������, ������ ������� ���������
		if (m_current == m_first)
			m_current = temp;

		delete m_first; // ����������� ������
		m_first = temp; // ���������� ��������� ������� ��� ������
	}
}

/*������� ���������*/
void CardsList::RemoveLast()
{
	if (m_last)
	{
		// ���������� ��������� ������� �� ���������� �� ���
		Card *temp = m_last->prevCard;
		if (temp != NULL)
			temp->nextCard = NULL;

		// ���� ��������� ������� ��� �������, ������ ������� ����������
		if (m_current == m_last)
			m_current = temp;

		delete m_last; // ����������� ������
		m_last = temp; // ���������� ���������� ������� ��� ���������
	}
}

/*�������� �� ������*/
void CardsList::RemoveAt(const int index)
{
	Card *temp = m_first;	// �������� ��������� �� ����� ������� ��������
    int counter = 0;		// ������� ��������� ������

    while (temp != NULL)
    {
		// ���� �������� �������� ������ ��������� �������
		if (counter < index)
		{
			// ��������� � ���������� ��������, �����������
			// �������� �������� � ���������� ���
			temp = temp->nextCard;
			counter ++;
			continue;
		}

		// ����� �� ������� ��������
		// ���������� �������� �� � ����� ����
		Card *tempPrev = temp->prevCard;
		Card *tempNext = temp->nextCard;

		if (tempPrev != NULL)				// ���� ���������� ����������
			tempPrev->nextCard = tempNext;	// ��������� ��� �� ���������
		else								// �����
			m_first = tempNext;				// ���������� ��������� ��� ������

		if (tempNext != NULL)				// ���� ��������� ����������
			tempNext->prevCard = tempPrev;	// ��������� ��� � ����������
		else								// �����
			m_last = tempPrev;				// ���������� ���������� ��� ���������

		if (m_current == temp)		// ���� ��������� ������� �������� �������
			m_current = m_first;	// ������ ������� ������

		delete temp; // ����������� ������
		temp = NULL;
    }
}

/*������ ������*/
void CardsList::Show()
{
    //������� ������ � ������
    Card *temp = m_first;	// �������� ��������� �� ����� ������� ��������
    int counter = 0;
    cout << "���������� ������:" << endl;
	while (temp != NULL) // ���� �� �������� ������ ��������
    {
        cout << "�������� �" << counter ++ << endl;	// ������� ���������� ����� ��������
		temp->Show();								// � �������� � �����
        cout << "~~~" << endl; // �����������
        temp = temp->nextCard;       // ����� ������ �� ����� ���������� ��������
    }
	cout << "����� �������: " << counter << endl; // ������� ����� ���������� ���������� ��������
}


/*����� �� �������*/
bool CardsList::SearchByIndex(const int index, Card &findedCard)
{
	Card *temp = m_first; // �������� ��������� �� ����� ������� ��������
    int counter = 0;
    bool isFinded = false;
	// ���� ���� �� ����� ��� �� ����� �� �����
    while (temp != NULL && !isFinded)
    {
		if (counter < index)	// ���� �� ����� �� ��������� ������
		{						// ��������� � ��������� ������ � ����������� �������
			temp = temp->nextCard;
			counter ++;
			continue;
		}
		// ����� �� ������ ������
		copyCard(temp, &findedCard);	// ��������� � ��������� �������� �����
		isFinded = true;				// �������� ���� ��� ���������� ������
    }
	return isFinded;
}

/*����� �� ������*/
int CardsList::SearchByAuthor(const char *s_author, CardsList &findedCards)
{
	Card *temp = m_first; // �������� ��������� �� ����� ������� ��������
    int findedCount = 0;
	bool isFinded = false;
    char *author = NULL;
    int year = 0;
    // ���� ���� �� ����� ��� �� ����� �� �����
    while (temp != NULL && !isFinded)
    {
		// ��������� �������� ���� �����
		author = NULL;
        temp->GetAuthor(&author);
		// ���� ���� ����� �������� ������� �������
		if (strstr(author, s_author) != NULL)
		{
			findedCards.Insert(temp);	// ��������� �������� � ������ �����������
			findedCount ++;				// ����������� ������� ��������� ���������
		}

		// ��������� � ���������� ��������
		temp = temp->nextCard;
        delete[] author;
    }
	// ���������� ���������� ��������� ���������
	return findedCount;
}

/*���������� � ����*/
void CardsList::SaveToFile(const string fileName)
{
	// ��������� ���� ��� ������
	FILE *outFile = NULL;
	outFile = fopen(fileName.c_str(), "w");
	if (outFile == NULL)
	{
		printf("������ �������� ����� %s", fileName.c_str());
		return;
	}

	Card *temp = m_first;        // �������� ��������� �� ����� ������� ��������
	int counter = 0;
	char *title = NULL;
	char *author = NULL;
	int year = 0;
	while (temp != NULL)         // ���� �� �������� ������ ��������
	{
		title = NULL;
		author = NULL;
		// ��������� �������� �����
		temp->GetTitle(&title);
		temp->GetAuthor(&author);
		temp->GetYear(year);
		// ���������� �� � ����
		fprintf(outFile, "%s\n", title);
		fprintf(outFile, "%s\n", author);
		fprintf(outFile, "%d\n", year);
		delete[] title;
		delete[] author;
		temp = temp->nextCard;       // ����� ������ �� ����� ���������� ��������
	}
	// ��������� ����
	fflush(outFile);
	fclose(outFile);
}


/*�������� �� �����*/
void CardsList::LoadFromFile(const string fileName)
{
	// ����� ��� ������ �� �����
	ifstream infile(fileName.c_str());
	string title;
    string author;
    string year;
	// ������� ������
	clearList();
	// ���� �� �������� ����� �����
	while (!infile.eof())
	{
		// ��������� �������� �������� �����
		getline(infile, title);
		getline(infile, author);
		getline(infile, year);
		if (title.length() == 0 ||
			author.length() == 0)
			continue;
		// ������� �������� ����� � ��������
		Card *card = new Card;
		card->SetTitle((char *)title.c_str());
		card->SetAuthor((char *)author.c_str());
		card->SetYear(atoi(year.c_str()));
		// ��������� �������� � ������
		Insert(card);
		delete card;
	}
	return;
}

/*�����*/
void CardsList::copyCard(Card *srcCard, Card *dstCard)
{
    char *title = NULL;
    char *author = NULL;
    int year = 0;
	// �������� �������� ����� �� srcCard
    srcCard->GetTitle(&title);
    srcCard->GetAuthor(&author);
    srcCard->GetYear(year);
	// ������������� �������� ����� � dstCard
    dstCard->SetTitle(title);
    dstCard->SetAuthor(author);
    dstCard->SetYear(year);
    delete[] title;
    delete[] author;
}

/*�������*/
void CardsList::clearList()
{
	while (m_first) //���� �� ������ �� ������ ������ ���-�� ����
    {
        m_last = m_first->nextCard;  // ��������� ����� ������ ���������� ����� ������
        delete m_first;              // ������� ������ �� ������� �����
        m_first = m_last;            // ����� ������ ������ �� ����� ���������� ��������
    }
	m_first = NULL;
	m_last = NULL;
	m_current = NULL;
}


//_______________________________________________________________________________________________________________________________

char *title; //��������� �����


void FillCard(Card *card);
//void ShowCard(Card *card);

int main()
{
    //��������� ������� �� ���������
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	// �������� ������� ������
    CardsList *cardList = new CardsList;
	Card *card = NULL;
    int count = 0;
    cout << "������� ���������� �������� (0 ��� �������� � �������� �� �����) : ";
    cin >> count; // �������� ���������� ��������� ������
	if (count > 0)
	{
		for (int c = 0; c < count; c ++)
		{
			cout << endl << "��������� " << c << "-� ��������: " << endl;
			// �������� �������� ������
			card = new Card;
			FillCard(card);
			cardList->Insert(card);
			delete card;
		}
	}
	else
	{
		cout << "������� ��� ����� ��� �������� ������:" << endl;
		cin.get();
		string inFileName;
		getline(cin, inFileName);
		cardList->LoadFromFile(inFileName);
	}
    cout << endl << endl;
	cardList->Show(); //���������� ������ �� ������
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
    cout << "������ �������:" << endl;
    cout << "1. ���������� �������� � ����� ������" << endl;
    cout << "2. ���������� �������� � ������ ������" << endl;
    cout << "3. ���������� �������� ����� �������" << endl;
    cout << "4. ����� �������� �� ������� (��������� �� 0) -> " << endl;
    cout << "5. ����� �������� �� ������" << endl;
    cout << "6. �������� ������� �������� ������:" << endl;
    cout << "7. �������� ���������� �������� ������:" << endl;
    cout << "8. �������� �������� ������ �� ������:" << endl;
    cout << "9. ���������� � ����:" << endl;
    cout << "10. �����" << endl;
    cout << "������� �������: ";
    cin >> action;
    cout << endl;

    switch (action)
    {
    case 1:
        cout << "���������� �������� � ����� ������:" << endl;
        card = new Card;
        FillCard(card);
        cardList->Append(card);
        delete card;

        cardList->Show(); //���������� ������ �� ������
        cout << endl;
        break;

    case 2:
        cout << "���������� �������� � ������ ������:" << endl;
        card = new Card;
        FillCard(card);
        cardList->Prepend(card);
        delete card;

        cardList->Show(); //���������� ������ �� ������
        cout << endl;
        break;

    case 3:
        cout << "���������� �������� ����� �������:" << endl;
        card = new Card;
        FillCard(card);
        cardList->Insert(card);
        delete card;

        cardList->Show(); //���������� ������ �� ������
        cout << endl;
        break;

    case 4:
        //int index = 0;
        cout << "������� ������ ��� ������ �������� (��������� �� 0) -> ";
        cin >> index; // �������� ���������� ��������� ������

        //Card iCard;
        if (cardList->SearchByIndex(index, iCard))
        {
            cout << "������� �����:" << endl;
            iCard.Show();
        }
        else
            cout << "����� �� �������" << endl;
        cout << endl;
        break;

    case 5:
        cout << "������� ������ ��� ������ ��������:" << endl;
        cin.get(); //���������� �������
        getline(cin, author);
        r = cardList->SearchByAuthor(author.c_str(), findedList);
        if (r > 0)
        {
            cout << "������� " << r << " ����������:" << endl;
            findedList.Show();
        }
        break;

    case 6:
        cout << "�������� ������� �������� ������:" << endl;
        cardList->RemoveFirst();
        cardList->Show(); //���������� ������ �� ������
        cout << endl;
        break;

    case 7:
        cout << "�������� ���������� �������� ������:" << endl;
        cardList->RemoveLast();
        cardList->Show(); //���������� ������ �� ������
        cout << endl;
        break;

    case 8:
        //int rn = 0;
        cout << "������� ����� �������� ��� �������� �� ������ (��������� �� 0) -> ";
        cin >> rn; // �������� ���������� ��������� ������
        cardList->RemoveAt(rn);
        cardList->Show(); //���������� ������ �� ������
        cout << endl;
        break;

    case 9:
        cout << "������� ��� ����� ��� ���������� ������:" << endl;
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

	cout << "����� �����: ";
    getline(cin, author);

    cout << "��������� �����: ";
    getline(cin, title);

    cout << "��� ������ �����: ";
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

    cout << "��������� �����: " << title << endl;
    cout << "����� �����: " << author << endl;
    cout << "��� ������: " << year << endl;
	cin.get();
}
