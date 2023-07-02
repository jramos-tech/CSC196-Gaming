#include "Memory.h"
#include <iostream>

using namespace std;
M::MemoryTracker M::g_memoryTracker;


void* operator new(size_t size) {
	void* p = malloc(size);
	M::g_memoryTracker.Add(p, size);
	return p;
}

void operator delete(void* address, size_t size) {
	M::g_memoryTracker.Remove(address, size);
	free(address);
}
namespace M {
	void MemoryTracker::Add(void* address, size_t size){
		m_bytesAllocated += size;
		m_numAllocations++;
	}
	void MemoryTracker::Remove(void* address, size_t size){
		m_bytesAllocated -= size;
		m_numAllocations--;
	}
	void MemoryTracker::DisplayInfo(){
		cout << "current bytes allocated: " << m_bytesAllocated << endl;
		cout << "current number allocations: " << m_numAllocations << endl;
	}
}