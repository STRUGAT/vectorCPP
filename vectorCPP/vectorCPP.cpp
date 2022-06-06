#include <iostream>

using namespace std;

template <typename T>
class Vector {

private:
	T* array;
	int index;
	int size;

public:
	Vector() { // конструктор по умолчанию
		index = 0;
		size = 5;
		array = new T[5];
	}

	Vector(int aSize) { // конструктор c пользовательсксим размером
		index = 0;
		size = aSize;
		array = new T[size];
	}

	Vector(const Vector& object) { // конструктор копирования
		size = object.size;
		index = size;
		array = new T[size];
		for (int i = 0; i < size; i++)
			array[i] = object.array[i];
	}

	~Vector() { // деструктор
		delete[] array;
	}

	Vector& operator =(const Vector& object) { // оператор =
		delete[] array;
		array = new T[object.size];
		size = object.size;
		index = object.index;
		for (int i = 0; i < size; i++)
			array[i] = object.array[i];
		return *this;
	}

	void Add(T item) { // вставка элемента
		if (index < size) {
			array[index] = item;
			index++;
		}
		else {
			T* arrayMod = new T[size + 1];
			for (int i = 0; i < size; i++)
				arrayMod[i] = array[i];
			size++;
			delete[] array;
			array = arrayMod;
			array[index] = item;
			index++;
		}
	}

	T Print(int i) { // вывод
		if (i >= size)
			return -1;
		else
			return array[i];
	}

	int Lenght() { // вывод размера вектора
		return size;
	}

	void Clear() { // очистка вектора
		size = 0;
		index = 0;
		delete[] array;
		array = new T[];
	}

	class Iterator {
	private:
		T* iter;

	public:
		Iterator(T* arg) { // конструктор (iter как указатель на аргумент)
			iter = arg;
		}

		Iterator(T iter) { // конструтор (для присвоения итератору значение другого)

		}

		Iterator& operator ++() { // оператор ++
			++iter;
			return *this;
		}

		Iterator& operator --() { // оператор --
			--iter;
			return *this;
		}

		Iterator& operator =(const Iterator& arg) { // оператор =
			if (this != arg)
				iter = arg.iter;
			return *this;
		}

		T& operator *() { // оператор для извлечения данных
			return *iter;
		}

		bool operator !=(const Iterator& arg) { // оператор !=
			return !(*this == arg);
		}

		bool operator ==(const Iterator& arg) { // оператор ==
			return iter == arg.iter;
		}
	};

	Iterator Begin() { // граница для итератора (начало)
		Iterator border(array);
		return border;
	}

	Iterator End() { // граница для итератора (конец)
		Iterator border(array + size);
		return border;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	Vector<int> vector5;
	cout << "вектор с размером по умолчанию" << endl;
	for (int i = 0; i < 5; i++)
	{
		vector5.Add(i);
		cout << vector5.Print(i) << " ";
	}

	cout << endl << "добавление элемента в конец" << endl;
	vector5.Add(10);
	for (int i = 0; i < vector5.Lenght(); i++)
		cout << vector5.Print(i) << " ";

	cout << endl << "оператор =" << endl;
	Vector<int> vectorCopy = vector5;
	for (int i = 0; i < vectorCopy.Lenght(); i++)
		cout << vectorCopy.Print(i) << " ";

	cout << endl << "итератор" << endl;
	for (Vector<int>::Iterator border = vector5.Begin(); border != vector5.End(); ++border)
		cout << *border << " ";
};