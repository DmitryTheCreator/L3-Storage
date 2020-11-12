#include <iostream>
#include <list>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

const int AMOUNT = 100;

class Food {
public:
	virtual Food* clone() = NULL;
};

class Meat : public Food {
public:
	virtual Food* clone() {
		cout << "Здесь лежит ";
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "Мясо\n";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		return new Meat();
	}
};

class Vegetable : public Food {
public:
	virtual Food* clone() {
		cout << "Тут хранятся ";
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 13));
		cout << "Овощи\n";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		return new Vegetable();
	}
};

class Fruit : public Food {
public:
	virtual Food* clone() {
		cout << "В этом месте содержатся ";
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << "Фрукты\n";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		return new Fruit();
	}
};


void choose(list<Food*> food);

class Storage {
private:
	list<Food*> food;
public:
	void bring_food(list<Food*> food) {
		for (auto i = food.begin(); i != food.end(); ++i) {
			this->food.push_back(*i);		
		}
	}
	void bring_one(Food* food) {
		auto it = this->food.begin();
		advance(it, rand() % this->food.size());	
		this->food.insert(it, food);
	}

	void throw_food() {		
		auto it = food.begin();
		advance(it, rand() % food.size());
		food.erase(it);
	} 

	void choose_one() {
		choose(food);
	}

	void get_food() {
		for (auto i = food.begin(); i != food.end(); ++i) {
			cout << (*i)->clone();
			printf("\r");
		}
		printf("\r        \r");
	}
	 
	Food* take_one() {
		auto it = food.begin();
		advance(it, rand() % food.size());
		return *it;
	}

};

list<Food*> cook_food(int index, Storage storage)
{
	list<Food*> food;
	for (int i = 0; i < index; ++i) {
		int count = 1 + rand() % 3;
		if (count == 1) food.push_back(new Meat());
		if (count == 2) food.push_back(new Vegetable());
		if (count == 3) food.push_back(new Fruit());
	}
	return food;
}

Food* buy_one()
{
	int count = 1 + rand() % 3;
	if (count == 1) return new Meat();
	if (count == 2) return new Vegetable();
	if (count == 3) return new Fruit();
}

void choose(list<Food*> food) {
	system("cls");
	cout << "Нажмите на Enter\n";
	int input = _getch();
	auto it = food.begin();
	int shift = 0;

	if (input == 13) {
		while (input != 27) {
			advance(it, shift);

			for (auto i = food.begin(); i != food.end(); ++i) {
				if (i == it) {
					cout << "--> ";
					cout << (*i)->clone() << "\r";
				}
				else {
					cout << "    ";
					cout << (*i)->clone() << "\r";
				}
			}
			printf("Нажмите на W or S");
			input = _getch();
			if (input == 119) shift = -1;
			if (input == 115) shift = 1;
			if (input == 119 && it == food.begin()) shift = 0;
			if (input == 115 && it == food.end()) shift = 0;
			
			system("cls");
		}
	}
}


int main()
{
	setlocale(LC_ALL, "");
	srand((unsigned)time(NULL));

	Storage storage;
	int index = 3 + rand() % 10;	
	storage.bring_food(cook_food(index, storage));
	storage.get_food();
	_getch();
	cout << "\n";
	storage.throw_food();
	storage.get_food();
	cout << "\n\n";
	_getch();
	storage.bring_one(buy_one());
	storage.get_food();
	cout << "\n\n\n";
	storage.choose_one();

	Food* ds = storage.take_one();
	cout << ds->clone();
}

