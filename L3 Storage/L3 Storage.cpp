#include <iostream>
#include <ctime>

using namespace std;

const int AMOUNT = 100;


class Object {
public:
	Object() {

	}
	~Object() {

	}
};

class Box : public Object {
public:
	Box() {

	}
};

class File : public Object {
public:
};


class MyStorage {
private:
	int length;
	Object* objects = new Object[length];
public:
	MyStorage() {
		length = 1 + rand() % 15;
	}
	MyStorage(int length) {
		this->length = length;
	}
	~MyStorage() {

	}

	void add_objects(Object objects[]) {
		for (int i = 0; i < get_count(); ++i) {
			 this->objects[i] = objects[i];
		}
	}

	void delete_objects(Object objects[]) {
		
	}
	 

	int get_count() {
		return length;
	}

};

void create_objects(MyStorage storage);
void add_to_storage(MyStorage storage, Object objects[]);
void delete_from_storage(MyStorage storage, Object objects[]);

void create_objects(MyStorage storage)
{
	Object* objects = new Object[storage.get_count()];
	for (int i = 0; i < storage.get_count(); ++i) {
		int count = 1 + rand() % 2;
		if (count == 1) {
			objects[i] = Box();
			printf("box\n");
		}

		if (count == 2) {
			objects[i] = File();
			printf("file\n");
		}
	}
	add_to_storage(storage, objects);

}

void add_to_storage(MyStorage storage, Object objects[])
{
	storage.add_objects(objects); 
}

void delete_from_storage(MyStorage storage, Object objects[])
{

}

int main()
{
	srand(time(NULL));

	{
		MyStorage storage(10);
		create_objects(storage);
		printf("\n%d", storage.get_count());
		printf("\n\n");
	}

	{
		MyStorage storage1;
		create_objects(storage1);
		printf("\n%d", storage1.get_count());
		printf("\n\n");
	}

}

