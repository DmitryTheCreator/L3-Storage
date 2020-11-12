#include <iostream>
#include <ctime>

using namespace std;

const int AMOUNT = 100;


class Object {
protected:
	
public:
	string classname;
	Object()
	{

	}
	~Object() {

	}
};

class Box : public Object {
public:
	string classname = "box";
	Box() {

	}
};

class File : public Object {
public:
	string classname = "file";
	File() {

	}
};


class MyStorage {
private:
	int length;
	Object** objects = new Object*[length];
public:
	MyStorage() {
		length = 10 + rand() % 15;
	}
	MyStorage(int length) {
		this->length = length;
	}
	~MyStorage() {

	}

	void add_object(int index, Object *object) {
		 objects[index] = object;
	}

	void delete_objects(int index) {		
		delete objects[index];
		objects[index] = NULL;
	}

	void get_object(int index) {
		
		if (objects[index]->classname == "box") printf("box\n");
		if (objects[index]->classname == "file") printf("file\n");
		//return *objects[index];
	}
	 
	int get_count() {
		return length;
	}

};

void create_objects(int index, MyStorage storage);
void add_to_storage(int index, MyStorage storage, Object *object);
void delete_from_storage(int index, MyStorage storage);

void create_objects(int index, MyStorage storage)
{
	int count = 1 + rand() % 2;
	if (count == 1) add_to_storage(index, storage, new Box());
	if (count == 2) add_to_storage(index, storage, new File());
}

void add_to_storage(int index, MyStorage storage, Object *object)
{
	storage.add_object(index, object); 
}

void delete_from_storage(int index, MyStorage storage)
{
	storage.delete_objects(index);
}

int main()
{
	srand(time(NULL));

	MyStorage storage2;
	create_objects(rand()%storage2.get_count(), storage2);
	//storage2.get_object(0);
	printf("\n%d\n", storage2.get_count());
	//delete_from_storage(rand() % storage2.get_count(), storage2);
	storage2.get_object(1);
	printf("\n%d\n\n", storage2.get_count());
	
}

