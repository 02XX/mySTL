#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include<cstddef>
#include<iostream>
#include<new>

namespace mtd{
    template<class T>
    inline T* _allocate(ptrdiff_t size, T*)
    {
        try
        {
            T* tmp = (T*)(::operator new((size_t)(size* sizeof(T))));//size × sizeof(T)
            return tmp;
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(...)
        {
            std::cerr << "Unknown Error\n";
        }
        return nullptr;
    }

    template<class T>
    inline void _deallocate(T* buffer)
    {
        ::operator delete(buffer);
    }

    template<class T1,class T2>
    inline void _construct(T1* p, const T2& value)
    {
        new(p)T1(value);
    }

    template<class T>
    inline void _destroy(T* ptr)
    {
        ptr->~T();
    }




    template<class T>
    class allocator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t different_type;
        template<class T1>
        struct rebind{
            typedef allocator<T1> other;
        };

        allocator() {}
        allocator(const allocator&){}
        template<class U>allocator(const allocator<U>&){}
        ~allocator(){}

        pointer allocate(size_type n, const void* = 0)
        {
            return _allocate((different_type)n, (pointer)0);
        }
        void deallocate(pointer p, size_type n)
        { 
            _deallocate(p);
        }

        void construct(pointer p, const T& value)
        {
            _construct(p,value);
        }
        void destroy(pointer p)
        {
            _destroy(p);
        }
    };

}




#endif//_ALLOCATOR_H_