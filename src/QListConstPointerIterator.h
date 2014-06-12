#pragma once
#include "main.h"

template<typename T>
class QListConstPointerIterator
{
public:
	QListConstPointerIterator() : begin(), end(), iterator()
	{
	}

	QListConstPointerIterator(typename QList<T*>::const_iterator begin, typename QList<T*>::const_iterator end) : begin(begin), end(end), iterator(begin)
	{
	}

	bool operator++(int)
	{
		if(this->iterator != this->end)
			this->iterator++;
		return this->iterator != this->end;
	}

	bool operator++()
	{
		return (*this)++;
	}

	bool operator--(int)
	{
		if(this->iterator == this->begin)
			return false;
		this->iterator--;
		return true;
	}

	bool operator--()
	{
		return (*this)--;
	}

	bool isEnd() const
	{
		return this->iterator == this->end;
	}

	void toLastElement()
	{
		while(this->iterator != this->end)
			this->iterator++;
		if(this->iterator != this->begin)
			this->iterator--;
	}

	const T *operator*() const
	{
		if(this->iterator == this->end)
			return nullptr;
		return *(this->iterator);
	}

private:
	typename QList<T*>::const_iterator begin;
	typename QList<T*>::const_iterator end;
	typename QList<T*>::const_iterator iterator;
};
