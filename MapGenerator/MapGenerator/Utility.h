#pragma once


namespace Utility
{
	template<typename T>
	static void deletePointer(T* p)
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
	}
}