#ifndef LOGGING_ALLOCATOR_H_INCLUDED
#define LOGGING_ALLOCATOR_H_INCLUDED

#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>

#define USE_PRETTY 1

template <typename T>
struct logging_allocator {
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

	template <typename U>
	struct rebind {
		using other = logging_allocator<U>;
	};

	logging_allocator() = default;
	~logging_allocator() = default;

	template <typename U>
	logging_allocator(const logging_allocator<U> &) {
	}

	T *allocate(std::size_t n) {
#ifndef USE_PRETTY
		std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        static void* pool = std::malloc(poolSize);

        if (pool != nullptr && n <= (poolSize - allocatedSize))
        {
            auto ptr = reinterpret_cast<T*>(pool) + allocatedSize;
            allocatedSize += n;
            return ptr;
        }
        throw std::bad_alloc{};

	}

	void deallocate(T *p, std::size_t n) {
#ifndef USE_PRETTY
		std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
		//std::free(p);
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
#ifndef USE_PRETTY
		std::cout << "construct" << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
#ifndef USE_PRETTY
		std::cout << "destroy" << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		p->~U();
	}

private:
    static constexpr std::size_t poolSize = sizeof(T) * 100;
    static int allocatedSize;
};

template <typename T>
int logging_allocator<T>::allocatedSize = 0;

#endif // LOGGING_ALLOCATOR_H_INCLUDED
