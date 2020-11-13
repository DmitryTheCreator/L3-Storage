#include <iostream>
#include <list>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

//  Создание родительского класса Food,
//  который содержит два виртуальных метода
class Food {
public:
	virtual Food* clone() = NULL;
	virtual void expiration() = NULL;
};

//  Класс наследник класса Food, имеет перекрытые методы clone()
//  и expiration()
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
	virtual void expiration() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "\r        \r";
		cout << "	Срок годности ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "мяса ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		cout << "4 месяца\n";
	}
};

//  Класс наследник класса Food, имеет перекрытые методы clone()
//  и expiration()
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
	virtual void expiration() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "\r        \r";
		cout << "	Срок годности ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 13));
		cout << "овощей ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		cout << "3 месяца\n";
	}
};

//  Класс наследник класса Food, имеет перекрытые методы clone()
//  и expiration()
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
	virtual void expiration() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "\r        \r";
		cout << "	Срок годности ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << "фруктов ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		cout << "2 месяца\n";
	}
};

class Storage;
void choose(list<Food*> food, int &key, Storage storage, bool is_exp);
void random_actions(Storage storage, int count);

/*  Хранилище Storage, которое является списком указателя на объекты list.
    Имеет 10 методов:
    1) Метод bring_food(list<Food*> food) добавляет в список
	объекты наследников класса Food, с которой будет работать пользователь в дальнейшем
	2) void bring_one(Food* food) добавляет объект наследника класса Food
	в случайное место списка
	3) void bring_one_certain(Food* food, int num) добавляет объект наследника 
	класса Food в указанное место списка
	4) void throw_food() уничтожает объект наследника класса Food из случайного места списка
	5) void throw_food_certain(int num) уничтожает объект 
	наследника класса Food из указанного места списка
	6) void choose_one(int &num, Storage storage, bool is_exp) 
	осуществляет переход между объектами
	7) void get_expiration() вызывает метод expiration()
	у объектов наследников класса Food
	8) void get_food() выводит на экран список объектов наследников класса Food
	9) void start_actions(Storage storage, int count) запускает
	цикл 100/1000/10000 случайных действий из методов хранилища
	10) int get_amount() возвращает размер списка
*/
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

	void bring_one_certain(Food* food, int num) {
		auto it = this->food.begin();
		advance(it, num);
		this->food.insert(it, food);
	}

	void throw_food() {		
		auto it = food.begin();
		advance(it, rand() % food.size());
		food.erase(it);
	} 

	void throw_food_certain(int num) {
		auto it = food.begin();
		advance(it, num);
		food.erase(it);
	}

	void choose_one(int &num, Storage storage, bool is_exp) {
		choose(food, num, storage, is_exp);
	}

	void get_expiration() {
		auto it = food.begin();
		advance(it, rand() % food.size());
		for (auto i = food.begin(); i != food.end(); ++i) {
			if (i == it) {
				cout << (*i)->clone() << "\r";
				(*it)->expiration();
			}
			else cout << (*i)->clone() << "\r";
		}
		cout << "\r        \r";
		
	}

	void get_food() {
		for (auto i = food.begin(); i != food.end(); ++i) {
			cout << (*i)->clone();
			printf("\r");
		}
		printf("\r        \r");
	}
	 
	void start_actions(Storage storage, int count) {
		random_actions(storage, count);
	}

	int get_amount() {
		return food.size();
	}
};

//  Создает объекты наследников класса Food
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

//  Возвращает объект наследника класса Food
Food* buy_one()
{
	int count = 1 + rand() % 3;
	if (count == 1) return new Meat();
	if (count == 2) return new Vegetable();
	if (count == 3) return new Fruit();
}

//  Осуществляет переход по объектам
void choose(list<Food*> food, int &num, Storage storage, bool is_exp)
{
	system("cls");
	int input = 0;
	auto it = food.begin();
	int shift = 0;	

	while (input != 13) {
		advance(it, shift);
		int count = 0;
		for (auto i = food.begin(); i != food.end(); ++i) {
			if (i == it) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
				cout << "--> ";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
				cout << (*i)->clone() << "\r";
				num = count;
					
				if (is_exp == true) (*i)->expiration();
			}
			else cout << (*i)->clone() << "\r";
			count++;
		}

		cout << "\r        \r";
		printf("На складе %d продуктов\n", storage.get_amount());
		printf("\nНажмите на W или S, чтобы перемещаться между едой\n");
		printf("Нажмите на Enter, чтобы выбрать еду\n");
		input = _getch();
		if (input == 230 || input == 119) shift = -1;
		if (input == 235 || input == 115) shift = 1;
		if (input == 230 && it == food.begin()) shift = 0;
		if (input == 235 && it == food.end()) shift = 0;
			
		system("cls");
	}
}

//  Запускает цикл из 100/1000/10000 случайных дествий
void random_actions(Storage storage, int count)
{
	int num;
	float start_time = clock();
	for (int i = 0; i < count; ++i) {;
		int action = 1 + rand() % 4;
		switch (action) {
		case 1:
			cout << "Цикл из " << count << " случайных действий\n";
			storage.bring_one(buy_one());
			storage.get_food();
			break;
		case 2:
			cout << "Цикл из " << count << " случайных действий\n";
			storage.throw_food();
			storage.get_food();
			break;
		case 3:
			cout << "Цикл из " << count << " случайных действий\n";
			num = rand() % storage.get_amount();
			storage.throw_food_certain(num);
			storage.bring_one_certain(buy_one(), num);
			storage.get_food();
			break;
		case 4:
			cout << "Цикл из " << count << " случайных действий\n";
			storage.get_expiration();
			break;
		}
		printf("На складе %d продуктов\n\n", storage.get_amount());
		if (i != count - 1) system("cls");
	}
	float end_time = clock();
	float search_time = (end_time - start_time) / 1000;
	cout << "Время работы программы: " << search_time << " sec\n";
}

// Выводи меню на консоль
void print_menu()
{
	cout << "[1] --> Принести еду\n";
	cout << "[2] --> Выкинуть еду\n";
	cout << "[3] --> Заменить еду на другую\n";
	cout << "[4] --> Узнать срок годности\n";
	cout << "[5] --> Оставить склад без присмотра\n";
}

int main()
{
	setlocale(LC_ALL, "");
	srand((unsigned)time(NULL));

	Storage storage;
	int index = 10 + rand() % 10;
	int key = 49;
	int num = 0;
	storage.bring_food(cook_food(index, storage));
repeat:
	storage.get_food();
	printf("На складе %d продуктов\n\n", storage.get_amount());
	print_menu();
	key = _getch();
	switch (key) {
	case 49:
		system("cls");
		storage.choose_one(num, storage, false);
		storage.bring_one_certain(buy_one(), num);
		goto repeat;
		break;
	case 50:
		system("cls");
		storage.choose_one(num, storage, false);
		storage.throw_food_certain(num);
		goto repeat;
		break;
	case 51:
		system("cls");
		storage.choose_one(num, storage, false);
		storage.throw_food_certain(num);
		storage.bring_one_certain(buy_one(), num);
		goto repeat;
		break;
	case 52:
		system("cls");
		storage.choose_one(num, storage, true);
		goto repeat;
		break;
	case 53:
		system("cls");
		
		storage.start_actions(storage, 100);
		cout << "Нажмите любую клавишу, чтобы запустить цикл на 1000 случайных действий\n";
		_getch();		
		storage.start_actions(storage, 1000);
		cout << "Нажмите любую клавишу, чтобы запустить цикл на 10000 случайных действий\n";
		_getch();
		storage.start_actions(storage, 10000);
		cout << "Нажмите любую клавишу, чтобы перейти к главному меню\n";
		_getch(); 
		goto repeat;
		break;
	}
	
}

