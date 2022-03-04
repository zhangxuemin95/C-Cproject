#pragma once
#include<iostream>
#include<cstring>
#define DEFAULT_SIZE 1000
#define ERROR -1
using namespace std;
template <class T>
class SqList {
protected:
	int length;
	int listsize;
	T* data;
public:
	SqList(int size = DEFAULT_SIZE)
	{
		listsize = size;
		length = 0;
		data = new T[size];
	}                                  // ��������v������
	virtual ~SqList() {
		delete[] data;
		data = NULL;
	}                                                             // ��������
	int GetLength() const;
	bool IsEmpty() const;		                                  // �ж�˳����Ƿ�Ϊ��
	void Clear();				                                  // ��˳������
	void Traverse(void (*Visit)(const T&)) const;	      // ����˳���
	int Locate(T e);	                  // Ԫ�ض�λ����ָ��Ԫ����˳����е�λ��
	int GetElem(int i, T& e) const;	                      // ȡ˳����е�i��Ԫ�ص�ֵ	
	int SetElem(int i, T e);	                      // �޸�˳����е�i��Ԫ�ص�ֵ
	int Delete(int i, T &e);                           // ɾ��˳����е�i��Ԫ��		
	int Insert(int i, T e);                     // ��˳����i��λ�ò���Ԫ��
	int Insert(T e);                            // ��˳����β����Ԫ��
	void sort();
	SqList(const SqList<T>& sa);                           // ���ƹ��캯��
	SqList<T>& operator =(const SqList<T>& sa) {
		this->length = sa.length;
		this->listsize = sa.length;
		int i = 0;
		while (i < sa.length)
		{
			this->data[i] = sa.data[i];
			i++;
		}
		return *this;
	}                                                               // ��ֵ�������
};
template <class T>
bool SqList<T>::IsEmpty() const
{
	if (length == 0) {
		return true;
	}
	else
	{
		return false;
	}
}
template <class T>
void SqList<T>::Clear() {
	delete[] data;
	data = NULL;
	data = new T[DEFAULT_SIZE];
	length = 0;
}
template <class T>
int SqList<T>::GetLength() const
{
	return length;
}
template <class T>
void SqList<T>::Traverse(void (*Visit)(const T&)) const
{
	for (int i = 0; i < length; i++) {
		visit(&data[i]);
	}
}
template <class T>
int SqList<T>::GetElem(int i, T& e) const
{
	if (i < 1 || i > length) {
		return ERROR;
	}
	else
	{
		e = data[i - 1];
		return 1;
	}
}
template <class T>
int SqList<T>::Locate(T e) 
{
	int i;
	for (i = 0; i < length; i++) {
		if (data[i] == e) {
			break;
		}
	}
	if (i == length) {
		return ERROR;
	}
	else
	{
		return i + 1;
	}
}
template <class T>
int SqList<T>::SetElem(int i, T e)
{
	if (i < 0 || i > length) {
		return ERROR;
	}
	else
	{
		data[i - 1] = e;
		return 1;
	}
}
template <class T>
int SqList<T>::Insert(int i, T e)
{
	if (i < 0 || i > length + 1) {
		return ERROR;
	}
	else
	{
		if (length == listsize)
		{
			return ERROR;
		}
		else
		{
			int j = length;
			while (j > i - 1) {
				data[j] = data[j - 1];
				j--;
			}
			data[i - 1] = e;
			length++;
			return 1;
		}
	}
}
template <class T>
int SqList<T>::Delete(int i, T& e)
{
	if (i < 0 || i > length) {
		return ERROR;
	}
	else
	{
		if (length == 0) {
			return ERROR;
		}
		else
		{
			int j = i - 1;
			while (j < length - 1) {
				data[j] = data[j + 1];
				j++;
			}
			length--;
			return 1;
		}
	}
}
template <class T>
int SqList<T>::Insert(T e)
{
	if (length == listsize) {
		return ERROR;
	}
	else
	{
		data[length] = e;
		length++;
		return 1;
	}
}
template<class T>
inline void SqList<T>::sort()
{
	int i, j, record;
	T m;
	for (i = 0; i < length; i++)
	{
		m = data[i]; record = i;
		for (j = i; j < length; j++) {
			if (data[j] < m) { m = data[j]; record = j; }
		}
		data[record] = data[i];
		data[i] = m;
	}
}
template <class T>
SqList<T>::SqList(const SqList<T>& sa)
{
	return sa;
}