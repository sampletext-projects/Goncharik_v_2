#include<iostream>

using namespace std;

template <typename T>
class LinkedList
{
protected:
	struct Node
	{
		T field; // поле данных
		Node* next; // указатель на следующий элемент
	};

	int size;
	Node* head;

	Node* create_node(T elem)
	{
		Node* node = new Node();
		node->field = elem;
		return node;
	}

	Node* get_indexed(int index)
	{
		if (index < 0 || index >= size)
		{
			return nullptr;
		}
		Node* elem = head;
		int i = 0;
		while (i < index)
		{
			elem = elem->next;
			i++;
		}
		return elem;
	}

public:
	LinkedList()
	{
		size = 0;
	}

	void insert(int index, T elem)
	{
		if (index < 0 || index > size)
		{
			return;
		}
		if (index == 0)
		{
			if (!head)
			{
				Node* append = create_node(elem);
				head = append;
			}
			else
			{
				Node* append = create_node(elem);
				append->next = head;
				head = append;
			}
		}
		else
		{
			Node* node = get_indexed(index - 1);
			insert_after(node, elem);
		}
		size++;
	}

	void push_back(T elem)
	{
		insert(size, elem);
	}

	void push_head(T elem)
	{
		insert(0, elem);
	}

	void insert_after(Node* node, T elem)
	{
		Node* append = create_node(elem);

		Node* next = node->next;
		node->next = append;
		append->next = next;
	}

	Node* get_node(int index)
	{
		Node* node = get_indexed(index);
		return node;
	}

	T get_value(int index)
	{
		Node* node = get_node(index);
		if (node == nullptr)
		{
			return nullptr;
		}
		else
		{
			return node->field;
		}
	}

	T min()
	{
		T min = INT32_MAX;
		Node* elem = head;
		while (elem != nullptr)
		{
			if (elem->field < min)
			{
				min = elem->field;
			}
			elem = elem->next;
		}
		return min;
	}

	void write()
	{
		Node* elem = head;
		int i = 0;
		while (i < size)
		{
			cout << elem->field << " ";
			elem = elem->next;
			i++;
		}
		cout << "\n";
	}
};

class Aeroflot
{
	int id_;
	int t_departure_;
	int days_;

public:
	Aeroflot()
	{
	}

	Aeroflot(int id, int t_departure, int days)
	{
		id_ = id;
		t_departure_ = t_departure;
		days_ = days;
	}

	int get_id()
	{
		return id_;
	}

	int get_t_departure()
	{
		return t_departure_;
	}

	int get_days()
	{
		return days_;
	}

	void write()
	{
		cout << "Aeroflot: " << id_ << ", t: " << t_departure_ / 3600 << ":" << t_departure_ % 3600 / 60 << ", days: ";
		int t = days_;
		while (t != 0)
		{
			cout << t % 2;
			t /= 2;
		}
		cout << "\n";
	}
};

template <class T=Aeroflot>
class ArrayList
{
protected:
	int size_;
	int capacity_;
	T* array_;

	T* get_indexed(int index)
	{
		if (index < 0 || index >= size_)
		{
			return nullptr;
		}
		return array_[index];
	}

	void relocate_capacity()
	{
		T* memory = new T[capacity_];
		for (int i = 0; i < size_; i++)
		{
			memory[i] = array_[i];
		}
		delete[] array_;
		array_ = memory;
	}

public:
	ArrayList()
	{
		size_ = 0;
		capacity_ = 2;
		relocate_capacity();
	}

	void insert(int index, T* elem)
	{
		if (index < 0 || index > size_) return;

		if (size_ + 1 > capacity_)
		{
			capacity_ *= 2;
			relocate_capacity();
		}

		for (int i = size_ - 1; i > index; i++)
		{
			array_[i] = array_[i - 1];
		}
		array_[index] = *elem;
		for (int i = index - 1; i > 0; i++)
		{
			array_[i] = array_[i - 1];
		}
		size_++;
	}

	void push_back(T* elem)
	{
		insert(size_, elem);
	}

	void push_head(T* elem)
	{
		insert(0, elem);
	}

	void write()
	{
		for (int i = 0; i < size_; ++i)
		{
			array_[i].write();
		}
	}
};

int main()
{
	LinkedList<float> list;
	list.push_back(1.1);
	list.write();
	list.push_back(2.2);
	list.write();
	list.push_back(3.3);
	list.write();
	list.insert(1, 4.4);
	list.write();
	cout << list.min() << "\n\n";

	ArrayList<> aeroflot_list;
	aeroflot_list.push_back(new Aeroflot(1, 14 * 3600 + 33 * 60, 1 + 4 + 16 + 64)); // (пн, ср, пт, вс) в 14:33
	aeroflot_list.push_back(new Aeroflot(2, 21 * 3600 + 17 * 60, 1 + 2 + 4 + 8 + 16 + 32 + 64));
	// (каждый день) в 21:13
	aeroflot_list.write();
	return 0;
}
