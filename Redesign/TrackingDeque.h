#ifndef TRACKINGDEQUE_H
#define TRACKINGDEQUE_H
#include <iostream>
#include <deque>
using namespace std;

template <class T> class TrackingDeque : public deque<T>
{
	public:
		TrackingDeque();
		~TrackingDeque();
		void push_back (const T& val);
		void push_front (const T& val);
	private:
		int max_size_reached;

};

//Functions

template <class T> TrackingDeque<T>::TrackingDeque() : max_size_reached(0)
{
}

template <class T> TrackingDeque<T>::~TrackingDeque()
{
	cout << "Max Size Reached in TrackingDeque = " << max_size_reached << endl;
}

template <class T> void TrackingDeque<T>::push_back(const T& val)
{
	(*this).deque<T>::push_back(val);
	if((*this).deque<T>::size() > max_size_reached)
	{
		max_size_reached++;
	}
}

template <class T> void TrackingDeque<T>::push_front(const T& val)
{
	(*this).deque<T>::push_front(val);
	if((*this).deque<T>::size() > max_size_reached)
	{
		max_size_reached++;
	}
}

#endif
