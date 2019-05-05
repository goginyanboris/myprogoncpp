/*Присутствует популяция травоядных, поглощающих с определённой скоростью (функция от размера популяции и количества пищи)
доступное пропитание. Популяция обладает возможностью приращивать количество особей естественным путём. При повышении возраста
особи увеличивается вероятность смерти. Кроме этого, существует аналогичная популяция хищников, скорость размножения которых
зависит от размера популяции травоядных. Необходимо построить математическую модель, отражающую изменение численности популяций
во времени.*/

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
unsigned int t; // допустим дни
int babeP=0, babeH=0;
bool Dead = false;

class world{
private:
    virtual void setquan(unsigned int quantity, int i, int N) = 0; // обьявление чисто виртуальных функций
    virtual void show(void) = 0;
	virtual void aging(int) = 0;
	virtual void sdvig(void) = 0; // (void) означает, что функция ничего не возвращает
	virtual vector< unsigned int > getPopul(void) const = 0;

public:
    virtual ~world(){}; // деструктор
};

class herbivorous; //прототип класса травоядных

class predators : public world {
private:
    vector<unsigned int> population;
public:
    predators(){ // конструктор
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
    herbivorous(){ // конструктор
        population = vector< unsigned int >(1, 0);
    }

    void setquan(unsigned int, int, int);
	void aging(int);// старение (умножение на коэффициент [i])
	void sdvig();
	void show();
	vector< unsigned int > getPopul(void) const;

	void birth(const int);// функция пополнения популяции травоядных
	void PrAttack(const predators &);// функция вымирания травоядных от нападений хищников(количество хищников)
};


void herbivorous::setquan(unsigned int quantity, int i, int N){ // функция задания начальных значений массива
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
            promort += population[i]/(population.size() - oldness); //вероятность смерти растет для каждого года
            population[i] -= promort;

        }
    }
}

void herbivorous::sdvig(){
    for(int i = 1; i < population.size(); i++){ // sum прибавить к populationH[0], а все остальные элементы сдвинуть
        population[population.size() - i] = population[population.size() - i - 1];
    }
    population[0] = 0;
}

void herbivorous::show(){
    cout << "Популяция травоядных:" << endl;
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
                    notnull = true;      // проверка на то, что  массив не нулевой

                }
            }

        if(notnull == true){  // если травоядные есть
            while(notnull == true){
                i = rand() % population.size();
                if(population[i] != 0) {
                    population[i] -= 1;
                    sum -= 2; //допустим, что двум хищникам хватает 1 особи(те 2 - то количество хищников, для прокормки которых хватает 1 особи )
                    notnull = false;
                }
            }
        }
        else{ //массив пуст
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
                notnull = true;      // проверка на то, что  массив не нулевой
            }
        }
         if(notnull == true){  // если травоядные есть
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
    cout << "Популяция хищников:" << endl;
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
            promort += population[i]/(population.size() - oldness); //вероятность смерти растет для каждого года
            population[i] -= promort;
       }
    }
}

void predators::birth(const herbivorous & herb){
    int sum = 0, meat = 0;
    for(int i = 1; i < population.size(); i++){ // общее количество хищников
        sum += population[i]/2;
    }
    for(int i = 1; i < herb.getPopul().size(); i++){
        meat += herb.getPopul()[i]*2; // 2 - то количество хищников, для прокормки которых хватает 1 особи
    }
    cout << "meat=" << meat << endl;
    if((sum > 0) && (meat != 0)){
        if(meat/sum >= 2){ // если количество пропитания выше какого то значения
            sum = 0;
            for(int j = 4; j < population.size() - 3; j++){ // j - возраст, при котором животное способно к имению потомства
                sum += population[j]*(rand() % babeP + 1); // 3 - количество детенышей, рождаемых за 1 такт
            }
        }
        population[0] += sum;
    }
}

void predators::sdvig(){
    for(int i = 1; i < population.size(); i++){  // sum прибавить к populationH[0], а все остальные элементы сдвинуть
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
    cout << "Введите максимальный возраст, до которого может дожить травоядное вашей популяции: ";
    cin >> quan;
    cout << "Нажмите 1, если хотите ввести количество особей каждого возраста самостоятельно\nи 2, если хотите завести некоторое количество особей определенного возраста\n";
    cin >> N;
    if(N == 1){
        for(int i = 0; i < quan; i++){
            cout << "ввод кол-ва особей с возрастом: " << i << endl;
            cin >> N;
            populH.setquan(quan, -1, N);
        }
    }
    else{
        cout << "Введите возраст особи: " << endl;
        cin >> i;
        cout << "Введите количество особей: ";
        cin >> N;
        populH.setquan(quan, i, N);
    }
    cout << "Введите максимальный возраст, до которого может дожить хищник вашей популяции: " << endl;
    cin >> quan;
    cout << "Нажмите 1, если хотите ввести количество особей каждого возраста самостоятельно\nи 2, если хотите завести некоторое количество особей определенного возраста\n";
    cin >> N;
    if(N == 1){
        for(int i = 0; i < quan; i++){
            cout << "ввод кол-ва особей с возрастом: " << i << endl;
            cin >> N;
            populP.setquan(quan, -1, N);
        }
    }
    else{
        cout << "Введите возраст особи: " << endl;
        cin >> i;
        cout << "Введите количество особей: " << endl;
        cin >> N;
        populP.setquan(quan, i, N);
    }
    int oldp, oldh;
    cout << "Введите возраст, начиная с которого травоядное начинает стареть " << endl;
    cin >> oldh;
    cout << "Введите возраст, начиная с которого хищник начинает стареть " << endl;
    cin >> oldp;
    cout << "Введите время(кол-во дней) наблюдения за популяцией:  " << endl;
    cin >> t;
    time(t, populH, populP, oldp, oldh);
    return 0;
 }

    void time(unsigned int t, herbivorous populH, predators populP, int oldp, int oldh)
    {
        int r = 0, Hb = 165, Pb = 230, f = 1;
        cout << "Введите максимальное количество потомков у травоядного: " ; cin >> babeH;
        cout << "Сколько раз в году наступает период спаривания у травоядных? " ; cin >> Hb;
        cout << "Введите максимальное количество потомков у хищника: " ; cin >> babeP;
        cout << "Сколько раз в году наступает период спаривания у хищников? " ; cin >> Pb;
        cout << "Сколько раз в день охотятся хищники? "; cin >> f;
        while(t - r != 0){
            cout << "День " << r << endl;
            populH.show();
            populP.show();
            cout << endl;
            if(f != 0){
                if(r % f == 0){
                    populH.PrAttack(populP); // хищники охотятся раз в пару дней
                    populP.dead();
                }
            }

            if((r % (365/Hb) == 0) && (r > (365/Hb - 1) )){
            cout << "birth __________________________________________________" << endl;
                populH.birth(food); // food можно задавать в маин
            }
            if((r % (365/Pb) == 0) && (r > (365/Pb - 1) )){
            cout << "birth __________________________________________________" << endl;
                populP.birth(populH); // потомство появится, если хищников в два раза меньше травоядных
            }

            if((r % 365 == 0)&&(r > 364)){
              cout << "YEAR____________________________________________________" << endl;
                populH.sdvig();
                populH.aging(oldh); // функции вымирания от старения и сдвиг элементов массива
                populP.sdvig();
                populP.aging(oldp); // старение раз в год
            }
            r++;
        }
    }

