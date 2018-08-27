#pragma once
namespace OpenGames::Oxel::Math
{
	template<typename T> class Array {
	private:
		T * array;
		size_t capacity;
		size_t count;
		void increaseCapacity(size_t value)
		{
			size_t newCapacity = count + value;
			T* newArray = new T[newCapacity];

			for(size_t i = 0; i < capacity; ++i)
			{
				newArray[i] = array[i];
			}
			capacity = newCapacity;

			delete[] array;
			array = newArray;
		}
	public:
		Array(size_t capacity = 1) : capacity(capacity), count(0)
		{
			array = new T[capacity];
		}
		~Array()
		{
			delete[] array;
		}
		inline size_t size() { return count; }
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
		T& operator[](size_t index)
		{
			return array[index];
		}
	};
}