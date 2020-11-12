#include <iostream>
#include <list>
#include <ctime>
#include <Windows.h>

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




class Storage {
private:
	int length;
	//Food** objects = new Food*[length];
	//list<Food>* food = new list<Food>[length];
	list<Food*> food;
public:
	Storage() {
		length = 10 + rand() % 15;
	}
	Storage(int length) {
		this->length = length;
	}
	~Storage() {

	}

	void add_object(int index, list<Food*> food) {
		for (auto i = food.begin(); i != food.end(); ++i) {
			this->food.push_back(*i);		
		}
	}

	void delete_objects(int index) {		
		//delete objects[index];
		//objects[index] = NULL;
	} 

	void get_object() {
		for (auto i = food.begin(); i != food.end(); ++i) {
			cout << (*i)->clone();
			printf("\r");
		}
	}
	 
	int get_count() {
		//return length;
	}

};

list<Food*> cook_food(int index, Storage storage);
void add_to_storage(int index, Storage storage, list<Food*> food);
void delete_from_storage(int index, Storage storage);

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

void add_to_storage(int index, Storage storage, list<Food*> food)
{
	storage.add_object(index, food); 
}

void delete_from_storage(int index, Storage storage)
{
	storage.delete_objects(index);
}

int main()
{
	setlocale(LC_ALL, "");
	srand((unsigned)time(NULL));

	Storage storage;
	int index = 10 + rand() % 20;	
	storage.add_object(index, cook_food(index, storage));
	storage.get_object();
	
}

