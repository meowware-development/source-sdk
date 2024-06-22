#pragma once

template <class T, class I = int> class CUtlMemory {
public:
	T& operator[](int i) {
		return m_pMemory[i];
	};

	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template <class T, class A = CUtlMemory<T>> class CUtlVector {
public:
	typedef A CAllocator;

	T& operator[](int i) {
		return m_Memory[i];
	};

	CAllocator m_Memory;
	int m_Size;
	T* m_pElements;
};