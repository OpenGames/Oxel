#pragma once
namespace OpenGames::Oxel::Math
{
	template<typename T> class Array {
	private:
		T * array;
		int capacity;
		int count;
		void increaseCapacity(int value)
		{
			int newCapacity = count + value;
			T* newArray = new T[newCapacity];

			for(int i = 0; i < capacity; ++i)
			{
				newArray[i] = array[i];
			}
			capacity = newCapacity;

			delete[] array;
			array = newArray;
		}
	public:
		Array(int capacity = 1) : capacity(capacity), count(0)
		{
			array = new T[capacity];
		}
		~Array()
		{
			delete[] array;
		}
		inline int size() { return count; }
		void pushBack(T value)
		{
			if(count >= capacity) increaseCapacity(1);
			array[count] = value;
			++count;
		}
		void popFront()
		{
			increaseCapacity(-1);
			--count;
		}
		T& operator[](int index)
		{
			return array[index];
		}
	};
}