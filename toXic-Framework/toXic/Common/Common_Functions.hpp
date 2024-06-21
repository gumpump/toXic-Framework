#ifndef COMMON_FUNCTIONS_IS_DEFINED
#define COMMON_FUNCTIONS_IS_DEFINED

template <class type>
type *ReverseArray(type *array, int lenght)
{
	int zaehler = lenght-1;
	for (int h=0; h<(lenght/2); h++)
	{
		int tmp = array[h];
		array[h] = array[zaehler];
		array[zaehler] = tmp;
		zaehler--;
	}

	return array;
}

// Copied code
template <typename T>
class Singleton
{
public:
	static T& Instance();

protected:
	virtual ~Singleton();
	inline explicit Singleton();

private:
	static T* _instance;
	static T* CreateInstance();
};

template<typename T>
T* Singleton<T>::_instance = 0;

template <typename T>
Singleton<T>::Singleton()
{
	Singleton::_instance = 0;
	Singleton::_instance = static_cast<T*>(this);
}

template<typename T>
T& Singleton<T>::Instance()
{
	if (Singleton::_instance == 0)
	{
		Singleton::_instance = CreateInstance();
	}
	return *(Singleton::_instance);
}

template<typename T>
inline T* Singleton<T>::CreateInstance()
{
	return new T();
}

template<typename T>
Singleton<T>::~Singleton()
{
	if (Singleton::_instance != 0)
	{
		delete Singleton::_instance;
	}
	Singleton::_instance = 0;
}
#endif