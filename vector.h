#pragma once
#include<iostream>
#include<assert.h>
#include<string>

namespace IceCola
{
    template<class T>
    class vector
    {
    public:
        // Vector的迭代器是一个原生指针
        typedef T* iterator;
        typedef const T* const_iterator;
        iterator begin()
        {
            return _start;
        }
        iterator end()
        {
            return _finish;
        }
        const_iterator cbegin() 
        {
            return _start;
        }
        const_iterator cend() const
        {
            return _finish;
        }

        // constructor and destructor
        vector() : _start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
        {}

        vector(int n, const T& value = T())
        {
            assert(n > 0);
            reserve(n);
            if (!_start)
            {
                exit(-1);
            }
            for (int i = 0; i < n; i++)
            {
                _start[i] = value;
            }
            _finish = _start + n;
            _endOfStorage = _start + n;
        }

        template<class InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            assert(first && last);
            int sz = last - first;
            reserve(sz);
            if (!_start)
            {
                exit(-1);
            }
            _finish = _start;
            _endOfStorage = sz + _start;
            while (first != last)
            {
                *_finish = *first;
                first++;
                _finish++;
            }
        }

        vector(const vector<T>& v):_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
        {
            vector tmp(v._start, v._finish);
            swap(tmp);
        }

        vector<T>& operator= (vector<T> v)
        {
            _start = _finish = _endOfStorage = nullptr;
            swap(v);
            return *this;
        }
        
        ~vector()
        {
            delete[] _start;
            _start = _finish = _endOfStorage = nullptr;
        }

        // capacity
        size_t size() const
        {
            return _finish - _start;
        }

        size_t capacity() const
        {
            return _endOfStorage - _start;
        }

        void reserve(size_t n)
        {
            assert(n > 0);
            if (n > this->size())
            {
                int sz = _finish - _start;
                iterator tmp = new T[n];
                for (int i = 0; i < sz; i++)
                {
                    tmp[i] = _start[i];
                }
                delete[] _start;
                _start = tmp;
                _finish = _start + sz;
                _endOfStorage = _start + n;
            }
        }

        void resize(size_t n, const T& value = T())
        {
            assert(n >= 0);
            if (n <= this->size())
            {
                _finish = _start + n;
            }
            else
            {
                if (n > capacity())
                {
                    reserve(n);
                }
                while (_finish != _start + n)
                {
                    *_finish = value;
                    _finish++;
                }
            }
        }

        //access
        T& operator[](size_t pos)
        {
            return _start + pos;
        }

        const T& operator[](size_t pos)const
        {
            return _start + pos;
        }

        //modify
        void push_back(const T& x)
        {
            if (_endOfStorage == _finish)
            {
                int sz = _endOfStorage - _start;
                reserve(sz == 0? 4: sz * 2);
            }
            *_finish = x;
            _finish++;
        }
        
        void pop_back()
        {
            assert(_start != _finish);
            _finish--;
        }

        void swap(vector<T>& v)
        {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_endOfStorage, v._endOfStorage);
        }

        iterator insert(iterator pos, const T& x)
        {
            assert(pos <= _finish);
            if (_finish == _endOfStorage)
            {
                int sz = _endOfStorage - _start;
                reserve(sz == 0 ? 4 : sz * 2);
            }
            iterator end = _finish + 1;
            while (end != pos)
            {
                *end = *(end - 1);
                end--;
            }
            *pos = x;
            _finish++;
            return pos;
        }

        iterator erase(iterator pos)
        {
            assert(pos < _finish);
            iterator cur = pos + 1;
            while (cur != _finish)
            {
                *(cur - 1) = *cur;
                cur++;
            }
            _finish--;
            return pos;
        }
    private:

        iterator _start; // 指向数据块的开始
        iterator _finish; // 指向有效数据的尾
        iterator _endOfStorage; // 指向存储容量的尾
    };

}
