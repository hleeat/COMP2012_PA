#include "polynomial.h"
#include <iostream>
using namespace std;
//note: you are not allowed to include any additional library, see also FAQ for what you can/cannot do
//write your code below and submit this file only
int power(int k, int v)
{
	int temp = 1;
	if (k == 0) return 1;
	for (int i = 0; i < k; i++)
	{
		temp = temp * v;
	}
	return temp;
}
Polynomial::Polynomial()
{
	head = nullptr;
}
Polynomial::Polynomial(const Polynomial& another)
{
	if (another.head == nullptr)
	{
		this->head = nullptr;
	}
	else
	{
		this->head = new Term;
		this->head->coefficient = another.head->coefficient;
		this->head->exponent = another.head->exponent;
		Term* newnode = nullptr;
		Term* previous = nullptr;
		this->head->next = newnode;
		previous = this->head;
		Term* ano_cur = another.head->next;
		while (ano_cur != nullptr)
		{
			newnode = new Term;
			previous->next = newnode;
			previous = previous->next;
			newnode->coefficient = ano_cur->coefficient;
			newnode->exponent = ano_cur->exponent;
			ano_cur = ano_cur->next;
		}
		previous->next = nullptr;
	}
}
Polynomial::Polynomial(int array[], int arraySize)
{
	int count = 0;
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i] == 0) count++;
	}
	if (count == arraySize)
	{
		head = nullptr;
	}
	else
	{
		head = new Term;
		int index = 0;
		for (index = 0; index < arraySize; index++)
		{
			if (array[index] != 0) break;
		}
		head->coefficient = array[index];
		head->exponent = arraySize - 1 - index;
		Term* cur = head;
		Term* newterm = nullptr;
		cur->next = newterm;
		while (index != arraySize)
		{
			if (array[index] != 0)
			{
				newterm = new Term;
				cur->next = newterm;
				cur = cur->next;
				newterm->coefficient = array[index];
				newterm->exponent = arraySize - index - 1;
			}
			index++;
		}
		cur->next = nullptr;
	}
}
Polynomial::~Polynomial()
{
	Term* current = head;
	Term* nextnode = nullptr;
	while (current != nullptr)
	{
		nextnode = current->next;
		delete current;
		current = nextnode;
	}
}
void Polynomial::print() const
{

	if (this->head == nullptr) cout << 0;
	else {
		int size = this->head->exponent + 1;
		int* arr = new int[size];
		Term* current = this->head;
		for (int i = 0; i < size; i++)
			arr[i] = 0;
		while (current != nullptr)
		{
			arr[current->exponent] = current->coefficient;
			current = current->next;
		}
		int zero = 0;
		for (int i = size - 1; i >= 0; i--)
		{
			if (arr[i] == 0)
			{
				zero++;
				continue;
			}
			if (size == 1) { cout << arr[i]; break; }
			if (zero == (size - 1 - i))
			{
				if (i == 0) cout << arr[i];
				else if (i == 1)
				{
					if (arr[i] == -1) cout << "-x";
					else if (arr[i] == 1) cout << "x";
					else cout << arr[i] << "*x";
				}
				else
				{
					if (arr[i] == -1) cout << "-x^";
					else if (arr[i] == 1) cout << "x^";
					else cout << arr[i] << "*x^";
					cout << i;
				}
			}
			if (zero != (size - 1 - i))
			{
				if (i == 0)
				{
					if (arr[i] < 0) cout << " - " << (-1) * arr[i];
					else cout << " + " << arr[i];
				}
				else if (i == 1)
				{
					if (arr[i] == -1) cout << " - x";
					else if (arr[i] == 1) cout << " + x";
					else if (arr[i] < -1) cout << " - " << (-1) * arr[i] << "*x";
					else cout << " + " << arr[i] << "*x";
				}
				else
				{
					if (arr[i] == -1) cout << " - x^";
					else if (arr[i] == 1) cout << " + x^";
					else if (arr[i] < -1) cout << " - " << (-1) * arr[i] << "*x^";
					else cout << " + " << arr[i] << "*x^";
					cout << i;
				}
			}
		}
		delete[] arr;
		arr = nullptr;
	}
}
void adding(int result[], int a1[], int a2[], int t1, int t2, int max)
{
	for (int i = 0; i < max; i++)
	{
		result[i] = 0;
	}
	for (int i = 0; i < t1; i++)
	{
		result[i] = result[i] + a1[i];
	}
	for (int i = 0; i < t2; i++)
	{
		result[i] = result[i] + a2[i];
	}
	int temp;
	for (int i = 0; i < max / 2; i++)
	{
		temp = result[i];
		result[i] = result[max - i - 1];
		result[max - i - 1] = temp;
	}
}
void sub(int result[], int a1[], int a2[], int t1, int t2, int max)
{
	for (int i = 0; i < max; i++)
	{
		result[i] = 0;
	}
	for (int i = 0; i < t1; i++)
	{
		result[i] = result[i] + a1[i];
	}
	for (int i = 0; i < t2; i++)
	{
		result[i] = result[i] - a2[i];
	}
	int temp;
	for (int i = 0; i < max / 2; i++)
	{
		temp = result[i];
		result[i] = result[max - i - 1];
		result[max - i - 1] = temp;
	}
}
void mul(int result[], int a1[], int a2[], int t1, int t2, int max)
{
	for (int i = 0; i < max; i++)
	{
		result[i] = 0;
	}
	for (int i = 0; i < t1; i++)
	{
		for (int j = 0; j < t2; j++)
		{
			result[i + j] = a1[i] * a2[j] + result[i + j];
		}
	}
	int temp;
	for (int i = 0; i < max / 2; i++)
	{
		temp = result[i];
		result[i] = result[max - i - 1];
		result[max - i - 1] = temp;
	}
}
Polynomial Polynomial::add(const Polynomial& another)const
{
	int tmax_co = (this->head == nullptr) ? 0 : this->head->exponent;
	int amax_co = (another.head == nullptr) ? 0 : another.head->exponent;
	int* a1 = new int[tmax_co + 1];
	int* a2 = new int[amax_co + 1];
	for (int i = 0; i < tmax_co + 1; i++)
		a1[i] = 0;
	for (int i = 0; i < amax_co + 1; i++)
		a2[i] = 0;
	Term* t_cur = this->head;
	Term* a_cur = another.head;
	while (t_cur != nullptr)
	{
		a1[t_cur->exponent] = t_cur->coefficient;
		t_cur = t_cur->next;
	}
	while (a_cur != nullptr)
	{
		a2[a_cur->exponent] = a_cur->coefficient;
		a_cur = a_cur->next;
	}
	int max = (tmax_co + 1 > amax_co + 1) ? tmax_co + 1 : amax_co + 1;
	int* result = new int[max];
	adding(result, a1, a2, tmax_co + 1, amax_co + 1, max);
	delete[]a1; delete[] a2;
	Polynomial p1 = Polynomial(result, max);
	delete[] result;
	return p1;
}
Polynomial Polynomial::subtract(const Polynomial& another)const
{
	int tmax_co = (this->head == nullptr) ? 0 : this->head->exponent;
	int amax_co = (another.head == nullptr) ? 0 : another.head->exponent;
	int* a1 = new int[tmax_co + 1];
	int* a2 = new int[amax_co + 1];
	for (int i = 0; i < tmax_co + 1; i++)
		a1[i] = 0;
	for (int i = 0; i < amax_co + 1; i++)
		a2[i] = 0;
	Term* t_cur = this->head;
	Term* a_cur = another.head;
	while (t_cur != nullptr)
	{
		a1[t_cur->exponent] = t_cur->coefficient;
		t_cur = t_cur->next;
	}
	while (a_cur != nullptr)
	{
		a2[a_cur->exponent] = a_cur->coefficient;
		a_cur = a_cur->next;
	}
	int max = (tmax_co + 1 > amax_co + 1) ? tmax_co + 1 : amax_co + 1;
	int* result = new int[max];
	sub(result, a1, a2, tmax_co + 1, amax_co + 1, max);
	delete[] a1; delete[] a2;
	a1 = nullptr; a2 = nullptr;
	Polynomial p1 = Polynomial(result, max);
	delete[] result;
	result = nullptr;
	return p1;

}
Polynomial Polynomial::multiply(const Polynomial& another)const
{
	int tmax_co = (this->head == nullptr) ? 0 : this->head->exponent;
	int amax_co = (another.head == nullptr) ? 0 : another.head->exponent;
	int* a1 = new int[tmax_co + 1];
	int* a2 = new int[amax_co + 1];
	for (int i = 0; i < tmax_co + 1; i++)
		a1[i] = 0;
	for (int i = 0; i < amax_co + 1; i++)
		a2[i] = 0;
	Term* t_cur = this->head;
	Term* a_cur = another.head;
	while (t_cur != nullptr)
	{
		a1[t_cur->exponent] = t_cur->coefficient;
		t_cur = t_cur->next;
	}
	while (a_cur != nullptr)
	{
		a2[a_cur->exponent] = a_cur->coefficient;
		a_cur = a_cur->next;
	}
	int max = tmax_co + amax_co + 1;
	int* result = new int[max];
	mul(result, a1, a2, tmax_co + 1, amax_co + 1, max);
	delete[] a1; delete[] a2;
	a1 = nullptr; a2 = nullptr;
	Polynomial p1 = Polynomial(result, max);
	delete[] result;
	result = nullptr;
	return p1;
}
int Polynomial::evaluate(int valueOfX) const
{
	int result = 0;
	int count = 0;
	Term* current = this->head;
	while (current != nullptr)
	{
		count++;
		current = current->next;
	}
	int size = count * 2;
	int* arr = new int[size];
	current = this->head;
	int i = 0;
	while (current != nullptr)
	{
		arr[i++] = current->coefficient;
		arr[i++] = current->exponent;
		current = current->next;
	}
	for (int j = 0; j < count; j++)
	{
		result = result + arr[j * 2] * power(arr[2 * j + 1], valueOfX);
	}
	delete[] arr;
	arr = nullptr;
	return result;
}
int Polynomial::compare(const Polynomial& another) const
{
	Term* this_cur = this->head;
	Term* ano_cur = another.head;
	while (this_cur != nullptr || ano_cur != nullptr)
	{
		if (this_cur == nullptr) return -1;
		if (ano_cur == nullptr) return 1;
		if (this_cur->exponent > ano_cur->exponent) return 1;
		else if (this_cur->exponent < ano_cur->exponent) return -1;
		else
		{
			if (this_cur->coefficient > ano_cur->coefficient) return 1;
			else if (this_cur->coefficient < ano_cur->coefficient) return -1;
			else
			{
				this_cur = this_cur->next;
				ano_cur = ano_cur->next;
			}
		}
	}
	if (this_cur == nullptr && ano_cur == nullptr) return 0;
	else if (this_cur != nullptr && ano_cur == nullptr) return 1;
	else return -1;
}