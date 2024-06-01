#pragma once
#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
using namespace std;

namespace moyu
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector()
			: _finish(nullptr)
			, _start(nullptr)
			, _end_of_storage(nullptr)
		{ }

		vector(const vector<T>& tmp)
		{
			for (auto e : tmp)
			{
				cout << e << endl;
				push_back(e);
			}
		}

		template<class InPutIterator>
		vector(InPutIterator frist, InPutIterator last)
		{
			while (frist != last)
			{
				push_back(*frist);
				++frist;
			}
		}

		vector(size_t n, const T& x = T())
		{
			for (size_t i = 0; i < n; i++)
			{
				push_back(x);
			}
		}

		vector(int n, const T& x = T())
		{
			for (size_t i = 0; i < n; i++)
			{
				push_back(x);
			}
		}

		vector(const initializer_list<T>& tmp)
		{
			for (auto e : tmp)
			{
				push_back(e);
			}
		}

		void swap(vector<T>& tmp)
		{
			std::swap(_start, tmp._start);
			std::swap(_finish, tmp._finish);
			std::swap(_end_of_storage, tmp._end_of_storage);
		}


		vector<T> operator=(vector<T> tmp)
		{
			swap(tmp);
			return *this;
		}

		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t oldsize = size();
				T* newstart = new T[n];
				//memcpy(newstart , _start , size() * sizeof(T));
				for (size_t i = 0; i < size(); i++)
				{
					newstart[i] = _start[i];
				}
				delete[] _start;
				_start = newstart;
				_finish = _start + oldsize;
				_end_of_storage = _start + n;
			}
		}
		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t newcapacity = (capacity() == 0) ? 4 : 2 * capacity();
				reserve(newcapacity);
			}
			*_finish = x;
			++_finish;
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			if (_start == _finish)
			{
				size_t len = pos - _start;
				size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newcapacity);
				pos = _start + len;
			}

			iterator it = _finish;
			while (it != pos)
			{
				*(it) = *(it - 1);
				--it;
			}
			*pos = x;
			_finish++;
			return pos;
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
		iterator begin()
		{
			return _start;
		}		
		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}



		void pop_back()
		{
			assert(_start != _finish);
			_finish--;
		}

		iterator erase(iterator pos)
		{
			assert(pos < _finish);
			iterator it = pos;
			while (it != _finish - 1)
			{
				*(it) = *(it + 1);
				++it;
			}
			_finish--;
			return pos;
		}

		iterator erase(iterator left, iterator right)
		{
			assert(left >= _start && right <= _finish);
			assert(left < right);
			iterator it = left;
			size_t len = right - left;
			while (len != 0)
			{
				it = erase(it);
				len--;
			}
			_finish = _finish -  len;
			return left;
		}

		void resize(size_t n, const T x = T())
		{
			if (n > capacity())
			{
				reserve(n);
			}

			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				for (size_t i = 0; i < n - size(); i++)
				{
					*(_start + size()  + i) = x;
				}
				_finish = _start + n;
			}
		}



		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};


	void testvector1()
	{
		vector<int> str1;
		str1.push_back(1);
		str1.push_back(2);
		str1.push_back(3);
		str1.push_back(4);
		str1.push_back(5);
		for (size_t i = 0; i < str1.size(); ++i)
		{
			cout << str1[i] << ' ';
		}
		cout << endl;

		vector<int>::iterator it = str1.begin();
		it = find(str1.begin(), str1.end(), 4);
		it = str1.erase(it);
		it = str1.insert(it, 300);

		for (auto e : str1)
		{
			cout << e << ' ';
		}
		cout << endl;




		//str1.pop_back();
		//str1.pop_back();
		//str1.pop_back();
		//str1.pop_back();
		//str1.pop_back();
		//for (size_t i = 0; i < str1.size(); ++i)
		//{
		//	cout << str1[i] << ' ';
		//}
		cout << endl;



		vector<int> str2;
		str2.push_back(1);
		str2.push_back(2);
		str2.push_back(3);
		str2.push_back(4);
		str2.push_back(5);
		for (auto e : str2)
		{
			cout << e << ' ';
		}

		vector<int> str3(str2);
		cout << endl;
		for (auto e : str3)
		{
			cout << e << ' ';
		}
		cout << endl;
		for (auto e : str1)
		{
			cout << e << ' ';
		}
		cout << endl;
		str1.operator=(str2);
		for (auto e : str1)
		{
			cout << e << ' ';
		}
		cout << endl;
	}

	void testvector2()
	{
		vector<string> str;
		str.push_back("1");
		str.push_back("2");
		str.push_back("3");
		str.push_back("4");
		str.push_back("5");
		str.push_back("6");

		for (auto e : str)
		{
			cout << e << ' ';
		}
		cout << endl;

		str.resize(3);
		for (auto e : str)
		{
			cout << e << ' ';
		}		
		cout << endl;
		str.resize(10);
		for (auto e : str)
		{
			cout << e << ' ';
		}
		cout << endl;
	}

	void testvector3()
	{
		int arr[5] = { 1,2,3,4,5 };
		vector<int> tmp(arr, arr + 3);
		for (auto e : tmp)
		{
			cout << e << ' ';
		}
		cout << endl;

		vector<int> tmp1(10, 222);
		for (auto e : tmp1)
		{
			cout << e << ' ';
		}
		cout << endl;

		vector<int> tmp3{ 1,2,3,2333,4,5,100,6,7 };
		vector<int> tmp4{ 1,2,3,2333,4,5};
		for (auto e : tmp3)
		{
			cout << e << ' ';
		}
		cout << endl;
		for (auto e : tmp4)
		{
			cout << e << ' ';
		}
		cout << endl;
	}
}
