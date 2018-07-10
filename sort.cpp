#include <iostream>
#include<ctime>
#include<cstdlib>
#include<limits>
#include<cmath>
#include<cstddef>
#include<fstream>
#include<cctype>

enum Error_code
{
	success, fail, range_out,underflow,overflow, not_present,fatal, duplicate_error, emtry_inserted, entry_found, internal_error
};

int const max_list = 20;
template <class List_entry>
class List
{
public:
	List();
	int size() const;
	bool full() const;
	bool empty() const;
	void clear();
	void traverse(void (*vist)(List_entry &));
	Error_code retrieve(int position, List_entry &x) const;
	Error_code remove(int position, const List_entry &x);
	Error_code replace(int position, const List_entry &x);
	Error_code insert(int position, const List_entry &x);
protected:
	int count;
	List_entry entry[max_list];
};

template <class List_entry>
List<List_entry>::List()
{
	count = 0;
}

template <class List_entry>
int List<List_entry>::size() const
{
	return count;
}

template <class List_entry>
bool List<List_entry>::full() const
{
	return count >= max_list;
}

template <class List_entry>
bool List<List_entry>::empty() const
{
	return count <= 0;
}

template <class List_entry>
void List<List_entry>::clear()
{
	count = 0;
}


template <class List_entry>
void List<List_entry>::traverse(void(*visit)(List_entry &))
{
	for(int i = 0; i < count; i++)
		(*visit)(entry[i]);
}


template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x)const
{
	if(position < 0 || position >= count)
		return range_out;
	else
		x = entry[position];
	return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
{
	if(position < 0 || position >= count)
		return range_out;
	else
		entry[position] = x;
	return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int position, const List_entry &x)
{
	if(position == 0)
		return underflow;
	if(position < 0 || position >= count)
		return range_out;
	x = entry[position];
	count--;
	while(position < count)
	{
		entry[position] = entry[position + 1];
		position++;
	}
	return success;
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
{
	if(full())
		return overflow;
	if(position < 0 || position > count)
		return range_out;
	for(int i = count - 1; i >= position; i--)
		entry[i + 1] = entry[i];
	entry[position] = x;
	count++;
	return success;
}

class Key
{
private:
	int key;
public:
	Key(int x=0)
	{
		key = x;
	}
	int the_key()const
	{
		return key;
	}
	static int comparisons;

};

typedef Key Record;

bool operator==(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() == y.the_key();
}
bool operator>(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() > y.the_key();
}
bool operator<(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() < y.the_key();
}
bool operator>=(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() >= y.the_key();
}
bool operator<=(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() <= y.the_key();
}
bool operator!=(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() != y.the_key();
}

template <class Node_entry>
struct Node
{
	Node_entry entry;
	Node<Node_entry> *next;
	Node();
	Node(Node_entry, Node<Node_entry> *link = NULL);
};


template <class Record>
class Sortable_list:public List<Record>
{
public:
	void insertion_sort();
	void merge_sort();
	void recursive_merge_sort(Node<Record>*&sub_list);
	Node<Record> *divide_from(Node<Record>*sub_list);
	Node<Record> *merge(Node<Record>*first, Node<Record>*second);
	void quick_sort();
	void recusive_quick_sort(int low, int high);
	int partition(int low, int high);
	void heap_sort();
	void insert_heap(const Record &current, int low, int high);
	void build_heap();


};

//≤Â»Î≈≈–Ú
template <class Record>
void Sortable_list<Record>::insertion_sort()
{
	int first_unsoted;
	int position;
	Record current;
	for(first_unsorted = 1; first_unsorted < count; first_unsorted++)
	{
		if(entry[first_unsorted] < entry[first_unsorted-1])
		{
			position = first_unsorted;
			current = entry[first_unsoted];
			do
			{
				entry[position] = entry[position-1];
				position--;
			}while(postion > 0 && entry[position-1] > currrent);
			entry[position] = current;
		}
	}
}

//πÈ≤¢≈≈–Ú
template <class Record>
void Sortable_list<Record>::merge_sort()
{
	recursive_merge_sort(head);
}


template <class Record>
void Sortable_list<Record>::recursive_merge_sort(Node<Record>*&sub_list)
{
	if(sub_list != NULL && sub_list->next != NULL)
	{
		Node<Record> *second_half = divide_from(sub_list);
		recursive_merge_sort(head);
		recursive_merge_sort(second_half);
		sub_list = marge(sub_list, second_half);
	}
}

template <class Record>
Node<Record> *Sortable_list<Record>::divide_from(Node<Record>*sub_list)
{
	Node<Record> *positon,
				 *midpoint,
				 *second_half;
	if({midpiont = sub_list} = NULL)
		return NULL;
	position = midpoint->next;
	while(positon != NULL)
	{
		positoin = positon->next;
		if(position != NULL)
		{
			midpoint = midpoint->next;
			position = position->next;
		}
	}
	second_half = midpoint->next;
	midpoint->next = NULL;
	return second_half;
}

template <class Record>
Node<Record> *Sortable_list<Record>::merge(Node<Record>*first, Node<Record>*second)
{
	Node<Record> *last_sorted;
	Node<Record> combined;
	last_sorted = &combined;
	while(first != NULL && second != NULL)
	{
		if(first->entry <= second->entry)
		{

			last_sorted->next = first;
			last_sorted = first;
			first = first->next;
		}
		else
		{
			last_sorted->next = second;
			last_sorted = scond;
			second = second->next;
		}
	}
	if(first != NULL)
		last_sorted->next = second;
	else
		last_sorted->next = first;
	return combined.next;
}

//øÏÀŸ≈≈–Ú
template <class Record>
void Sortable_list<Record>::quick_sort()
{
	recusive_quick_sort(0, count-1);
}

template <class Record>
void Sortable_list<Record>::recusive_quick_sort(int low, int high)
{
	int pivot_position;
	if(low < high)
	{
		pivot_position = partition(low, high);
		recusive_quick_sort(low, pivot_position-1);
		recusive_quick_sort( pivot_position+1, high);
	}
}

template <class Record>
int Sortable_list<Record>::partition(int low, int high)
{
	Record pivot;
	int i , last_small;
	swap(low, (low + high)/2);
	pivot = entry[low];
	last_small = low;

	for(i = low + 1;i <= high; i++)
	{
		if(entry[i] < pivot)
		{
			last_small = last_small + 1;
			swap(last_small, i)
		}
	}
	swap(low, last_small);
	return last_small;
}

template <class Record>
void Sortable_list<Record>::heap_sort()
{
	Record current;
	int last_unsorted;
	build_heap();
	for (last_unsorted = count - 1£ª last_unsrted > 0, last_unsorted--)
	{
		current = entry[last_unsorted];
		entry[last_unsorted] = entry[0];
		insert_heap(current, 0, last_unsorted);
	}
}

template <class Record>
void Sortable_list<Record>::insert_heap(const Record &current, int low, int high)
{
	int large;
	large = 2 * low + 1;
	while (large <= high)
	{
		if (large < high && entry[large] < entry[large + 1])
			large++;
		if (current >= entry[laarge])
			break;
		else
		{
			entry[low] = entry[large];
			low = large;
			large = 2 * low + 1;
		}
	}
	entry[low] = current;
}

template <class Record>
void Sortable_list<Record>::build_heap()
{
	int low;
	for (low = count / 2 - 1; low >= 0; low--)
	{
		Record = entry[low];
		insert_heap(current, low, count - 1);
	}
}