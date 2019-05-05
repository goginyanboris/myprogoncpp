/*������������ ��������� ����������, ����������� � ����������� ��������� (������� �� ������� ��������� � ���������� ����)
��������� ����������. ��������� �������� ������������ ����������� ���������� ������ ������������ ����. ��� ��������� ��������
����� ������������� ����������� ������. ����� �����, ���������� ����������� ��������� ��������, �������� ����������� �������
������� �� ������� ��������� ����������. ���������� ��������� �������������� ������, ���������� ��������� ����������� ���������
�� �������.*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <clocale>

using namespace std;
const unsigned int food = 4294967294;
unsigned int t; // �������� ���
int babeP=0, babeH=0;
bool Dead = false;

class world{
private:
    virtual void setquan(unsigned int quantity, int i, int N) = 0; // ���������� ����� ����������� �������
    virtual void show(void) = 0;
	virtual void aging(int) = 0;
	virtual void sdvig(void) = 0; // (void) ��������, ��� ������� ������ �� ����������
	virtual vector< unsigned int > getPopul(void) const = 0;

public:
    virtual ~world(){}; // ����������
};

class herbivorous; //�������� ������ ����������

class predators : public world {
private:
    vector<unsigned int> population;
public:
    predators(){ // �����������
        population = vector< unsigned int >(1, 0);
    }

    void setquan(unsigned int, int, int);
	void aging(int);
	void sdvig();
	void show();

	vector< unsigned int > getPopul(void) const;

	void birth(const herbivorous &);
	void dead();
};

class herbivorous{
private:
    vector<unsigned int> population;
public:
    herbivorous(){ // �����������
        population = vector< unsigned int >(1, 0);
    }

    void setquan(unsigned int, int, int);
	void aging(int);// �������� (��������� �� ����������� [i])
	void sdvig();
	void show();
	vector< unsigned int > getPopul(void) const;

	void birth(const int);// ������� ���������� ��������� ����������
	void PrAttack(const predators &);// ������� ��������� ���������� �� ��������� ��������(���������� ��������)
};


void herbivorous::setquan(unsigned int quantity, int i, int N){ // ������� ������� ��������� �������� �������
        if(i == -1){
            population.insert(population.end(), N);
        }
        else{
            for(int j = 0; j < quantity; j++){
                population.insert(population.end(), 0);
            }
            population[i-1] = N;
        }
}

void herbivorous::aging(int oldness){
    int k = 0;
    int promort = 0;
    for(int i = oldness; i < population.size(); i++){
         if(population[i]!= 0){
            promort += population[i]/(population.size() - oldness); //����������� ������ ������ ��� ������� ����
            population[i] -= promort;

        }
    }
}

void herbivorous::sdvig(){
    for(int i = 1; i < population.size(); i++){ // sum ��������� � populationH[0], � ��� ��������� �������� ��������
        population[population.size() - i] = population[population.size() - i - 1];
    }
    population[0] = 0;
}

void herbivorous::show(){
    cout << "��������� ����������:" << endl;
    for(int i = 0; i < population.size(); i++){
        cout << population[i] << " ";
    }
    cout << endl;
}

vector< unsigned int > herbivorous::getPopul(void) const
{
	return population;
}

void herbivorous::birth(const int food){
    int sum = 0;
    for(int i = 1; i < population.size(); i++){
        sum += population[i]/2;
    }
    if(sum > 0){
        if(food/sum >= 2){
            for(int j = 3; j < population.size() - 2; j++){
                sum += population[j]*(rand() % babeH + 1);
            }
        }
    }
    population[0] += sum;
}

void herbivorous::PrAttack(const predators &p){
    int sum = 0, i;
    bool notnull = false;
    for(int j = 1; j < p.getPopul().size(); j++){
        sum += p.getPopul()[j];
    }
    while(sum > 0){
         for(int l = 0; l < population.size(); l++){
                if(population[l] != 0){
                    notnull = true;      // �������� �� ��, ���  ������ �� �������

                }
            }

        if(notnull == true){  // ���� ���������� ����
            while(notnull == true){
                i = rand() % population.size();
                if(population[i] != 0) {
                    population[i] -= 1;
                    sum -= 2; //��������, ��� ���� �������� ������� 1 �����(�� 2 - �� ���������� ��������, ��� ��������� ������� ������� 1 ����� )
                    notnull = false;
                }
            }
        }
        else{ //������ ����
            Dead = true;
            break;
        }
    }
}

void predators::dead(){
    bool notnull;
    if(Dead == true){
        for(int l = 0; l < population.size(); l++){
            if(population[l] != 0){
                notnull = true;      // �������� �� ��, ���  ������ �� �������
            }
        }
         if(notnull == true){  // ���� ���������� ����
            for(int j =0; j <= population.size(); j++){
                int i = rand() % population.size();
                if(population[i] != 0) {
                    population[i] -= 1;
                    Dead = false;
                }
            }
        }
    }

}

void predators::setquan(unsigned int quantity, int i, int N){
	if(i == -1){
		population.insert(population.end(), N);
	}
	else{
		for(int j = 0; j < quantity; j++){
			population.insert(population.end(), 0);
		}
		population[i-1] = N;
	}
}

void predators::show(){
    cout << "��������� ��������:" << endl;
    for(int i = 0; i < population.size(); i++){
        cout << population[i] << " ";
    }
    cout << endl;
}

void predators::aging(int oldness){
    int k = 0;
    int promort = 0;

    for(int i = oldness; i < population.size(); i++){
       if(population[i]!= 0){
            promort += population[i]/(population.size() - oldness); //����������� ������ ������ ��� ������� ����
            population[i] -= promort;
       }
    }
}

void predators::birth(const herbivorous & herb){
    int sum = 0, meat = 0;
    for(int i = 1; i < population.size(); i++){ // ����� ���������� ��������
        sum += population[i]/2;
    }
    for(int i = 1; i < herb.getPopul().size(); i++){
        meat += herb.getPopul()[i]*2; // 2 - �� ���������� ��������, ��� ��������� ������� ������� 1 �����
    }
    cout << "meat=" << meat << endl;
    if((sum > 0) && (meat != 0)){
        if(meat/sum >= 2){ // ���� ���������� ���������� ���� ������ �� ��������
            sum = 0;
            for(int j = 4; j < population.size() - 3; j++){ // j - �������, ��� ������� �������� �������� � ������ ���������
                sum += population[j]*(rand() % babeP + 1); // 3 - ���������� ���������, ��������� �� 1 ����
            }
        }
        population[0] += sum;
    }
}

void predators::sdvig(){
    for(int i = 1; i < population.size(); i++){  // sum ��������� � populationH[0], � ��� ��������� �������� ��������
        population[population.size() - i] = population[population.size() - i - 1];
    }
    population[0] = 0;
}

vector< unsigned int > predators::getPopul(void) const
{
	return population;
}



void time(unsigned int , herbivorous , predators, int, int);

int main()
{
    herbivorous populH;
    predators populP;
    unsigned int quan;
    int N, i;
    setlocale(LC_CTYPE, "rus");
    cout << "������� ������������ �������, �� �������� ����� ������ ���������� ����� ���������: ";
    cin >> quan;
    cout << "������� 1, ���� ������ ������ ���������� ������ ������� �������� ��������������\n� 2, ���� ������ ������� ��������� ���������� ������ ������������� ��������\n";
    cin >> N;
    if(N == 1){
        for(int i = 0; i < quan; i++){
            cout << "���� ���-�� ������ � ���������: " << i << endl;
            cin >> N;
            populH.setquan(quan, -1, N);
        }
    }
    else{
        cout << "������� ������� �����: " << endl;
        cin >> i;
        cout << "������� ���������� ������: ";
        cin >> N;
        populH.setquan(quan, i, N);
    }
    cout << "������� ������������ �������, �� �������� ����� ������ ������ ����� ���������: " << endl;
    cin >> quan;
    cout << "������� 1, ���� ������ ������ ���������� ������ ������� �������� ��������������\n� 2, ���� ������ ������� ��������� ���������� ������ ������������� ��������\n";
    cin >> N;
    if(N == 1){
        for(int i = 0; i < quan; i++){
            cout << "���� ���-�� ������ � ���������: " << i << endl;
            cin >> N;
            populP.setquan(quan, -1, N);
        }
    }
    else{
        cout << "������� ������� �����: " << endl;
        cin >> i;
        cout << "������� ���������� ������: " << endl;
        cin >> N;
        populP.setquan(quan, i, N);
    }
    int oldp, oldh;
    cout << "������� �������, ������� � �������� ���������� �������� ������� " << endl;
    cin >> oldh;
    cout << "������� �������, ������� � �������� ������ �������� ������� " << endl;
    cin >> oldp;
    cout << "������� �����(���-�� ����) ���������� �� ����������:  " << endl;
    cin >> t;
    time(t, populH, populP, oldp, oldh);
    return 0;
 }

    void time(unsigned int t, herbivorous populH, predators populP, int oldp, int oldh)
    {
        int r = 0, Hb = 165, Pb = 230, f = 1;
        cout << "������� ������������ ���������� �������� � �����������: " ; cin >> babeH;
        cout << "������� ��� � ���� ��������� ������ ���������� � ����������? " ; cin >> Hb;
        cout << "������� ������������ ���������� �������� � �������: " ; cin >> babeP;
        cout << "������� ��� � ���� ��������� ������ ���������� � ��������? " ; cin >> Pb;
        cout << "������� ��� � ���� �������� �������? "; cin >> f;
        while(t - r != 0){
            cout << "���� " << r << endl;
            populH.show();
            populP.show();
            cout << endl;
            if(f != 0){
                if(r % f == 0){
                    populH.PrAttack(populP); // ������� �������� ��� � ���� ����
                    populP.dead();
                }
            }

            if((r % (365/Hb) == 0) && (r > (365/Hb - 1) )){
            cout << "birth __________________________________________________" << endl;
                populH.birth(food); // food ����� �������� � ����
            }
            if((r % (365/Pb) == 0) && (r > (365/Pb - 1) )){
            cout << "birth __________________________________________________" << endl;
                populP.birth(populH); // ��������� ��������, ���� �������� � ��� ���� ������ ����������
            }

            if((r % 365 == 0)&&(r > 364)){
              cout << "YEAR____________________________________________________" << endl;
                populH.sdvig();
                populH.aging(oldh); // ������� ��������� �� �������� � ����� ��������� �������
                populP.sdvig();
                populP.aging(oldp); // �������� ��� � ���
            }
            r++;
        }
    }

