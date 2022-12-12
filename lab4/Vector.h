#pragma once

#include <memory>
#include <stdexcept>

// todo reserve
//  clear
//  insert
//  erase

// why reserve, push_back is constexpr

template<class T, class Alloc = std::allocator<T>>
class Vector {
    T* arr = nullptr;
    size_t len = 0;
    size_t cap = 0;

    Alloc alloc;

    using AllocTraits = std::allocator_traits<Alloc>;


public:
    Vector() = default;

    constexpr explicit Vector(size_t length, const Alloc & allocator = std::allocator<T>()) : len(length), alloc(allocator) {
        if (length > cap) {
            arr = AllocTraits::allocate(alloc, length);
            cap = length;
        } else {
            arr = AllocTraits::allocate(alloc, cap);
        }
        int i = 0;
        try {
            for (; i < length; ++i) {
                AllocTraits::construct(alloc, arr + i, T());
            }
        } catch(...) {
            for (int j = 0; j < i; ++j) {
                AllocTraits::destroy(alloc, arr + i);
            }
            throw;
        }
    };

    constexpr Vector(std::initializer_list<T> && list, const Alloc & allocator = std::allocator<T>()) : alloc(allocator) {
        arr = AllocTraits::allocate(alloc, list.size());
        try {
            uninitializedCopy(list.begin(), list.end(), arr);
        } catch(...) {
            AllocTraits::deallocate(alloc, arr, list.size());
        }
        cap = list.size();
        len = list.size();
    };

//        constexpr ~Vector() {
    ~Vector() {
        for (int i = 0; i < len; ++i) {
            AllocTraits::destroy(alloc, arr + i);
        }
        AllocTraits::deallocate(alloc, arr, cap);
    }



    constexpr void popBack() {
        if (len == 0) return;
        AllocTraits::destroy(alloc, len);
        len--;
    }

    constexpr void pushBack(const T & el) {
        emplaceBack(el);
    }

    constexpr void pushBack(T && el) {
        emplaceBack(std::move(el));
    }


    template<class... Args>
    constexpr T & emplaceBack(Args && ... args) {
        if (len == cap) {
            reserve(newCapacity(cap));
        }
        AllocTraits::construct(alloc, arr + len, std::forward<Args>(args)...);
        ++len;
        return back();
    }

private:
    [[nodiscard]]
    constexpr size_t newCapacity(size_t oldCapacity) {
        return (oldCapacity == 0) ? 10 : oldCapacity * 3 / 2;
    }

public:
    constexpr void reserve(size_t length) {
        if (length <= cap) return;
        T* newArr = AllocTraits::allocate(alloc, length);

        size_t i = 0;
        try {
            uninitializedMove(arr, arr + len, newArr);
        } catch (...) {
            uninitializedMove(newArr, newArr + i, arr);
            AllocTraits::deallocate(alloc, newArr, length);
            throw;
        }
        AllocTraits::deallocate(alloc, arr, cap);
        arr = newArr;
        cap = length;
    }


    constexpr void shrinkToFit() {
        if (cap == len) return;

        T* newArr = AllocTraits::allocate(alloc, len);
        size_t i = 0;
        try {
            uninitializedMove(arr, arr + len, newArr);
        } catch (...) {
            uninitializedMove(newArr, newArr + i, arr);
            AllocTraits::deallocate(alloc, newArr, len);
            throw;
        }
        AllocTraits::deallocate(alloc, arr, cap);
        arr = newArr;
        cap = len;
    }

private:
    template<class ForwardIt, class DestinationIt>
    DestinationIt uninitializedMove(ForwardIt begin, ForwardIt end, DestinationIt destinationIt) {
        ForwardIt it = begin;
        DestinationIt current = destinationIt;
        try {
            for (; it != end; ++it) {
                AllocTraits::construct(alloc, current, std::move_if_noexcept(*it));
                ++current;
            }
        } catch (...) {
            for (ForwardIt jt = begin; jt != it; ++jt) {
                AllocTraits::construct(alloc, begin, std::move_if_noexcept(*jt));
                ++begin;
            }
            throw;
        }
        return current;
    }

    template<class ForwardIt, class DestinationIt>
    DestinationIt uninitializedCopy(ForwardIt begin, ForwardIt end, DestinationIt destinationIt) {
        ForwardIt it = begin;
        DestinationIt current = destinationIt;
        try {
            for (; it != end; ++it) {
                AllocTraits::construct(alloc, current, *it);
                ++current;
            }
        } catch (...) {
            for (ForwardIt jt = destinationIt; jt != current; ++jt) {
                AllocTraits::destroy(alloc, jt);
            }
            throw;
        }
        return current;
    }


public:
    Vector(const Vector<T, Alloc> & other) {
        len = other.len;
        cap = other.cap;
        alloc = AllocTraits::select_on_container_copy_construction(other.alloc);
        arr = AllocTraits::allocate(alloc, other.cap);
        size_t i = 0;
        try {
            uninitializedCopy(other.arr, other.arr + other.len, arr);
        } catch (...) {
            for (int j = 0; j < i; ++j) {
                AllocTraits::destroy(alloc, arr + i);
            }
            AllocTraits::deallocate(alloc, arr, other.cap);
            throw;
        }
    }

    Vector<T, Alloc>& operator=(const Vector<T, Alloc> & other) & {
        if (&other == this) return *this;

        for (int i = 0; i < len; ++i) {
            AllocTraits::destroy(alloc, arr + i);
        }
        AllocTraits::deallocate(alloc, arr, cap);

        len = other.len;
        cap = other.cap;
        if (AllocTraits::propagate_on_container_copy_assignment::value) {
            alloc = other.alloc;
        }
        arr = AllocTraits::allocate(alloc, other.cap);
        size_t i = 0;
        try {
            uninitializedCopy(other.arr, other.arr + other.len, arr);
        } catch (...) {
            for (int j = 0; j < i; ++j) {
                AllocTraits::destroy(alloc, arr + i);
            }
            AllocTraits::deallocate(alloc, arr, other.cap);
            throw;
        }

        return *this;
    }

    Vector(Vector<T, Alloc> && other) noexcept
        : len(other.len), cap(other.cap),
        arr(other.arr), alloc(std::move(other.alloc)) {
        other.len = 0;
        other.cap = 0;
        other.alloc = Alloc();
        other.arr = nullptr;
    }

    Vector<T, Alloc>& operator=(Vector<T, Alloc> && other) & noexcept {
        if (&other == this) return *this;

        for (int i = 0; i < len; ++i) {
            AllocTraits::destroy(alloc, arr + i);
        }
        AllocTraits::deallocate(alloc, arr, cap);

        len = other.len;
        cap = other.cap;
        alloc = std::move(alloc);
        arr = other.arr;

        other.len = 0;
        other.cap = 0;
        other.alloc = Alloc();
        other.arr = nullptr;

        return *this;
    }

    constexpr Alloc & get_allocator() const {
        return alloc;
    }

    [[nodiscard]]
    constexpr size_t capacity() const {
        return cap;
    }

    [[nodiscard]]
    constexpr size_t size() const {
        return len;
    }

    [[nodiscard]]
    constexpr bool empty() const {
        return len == 0;
    }

    [[nodiscard]]
    constexpr T & back() {
        return arr[len - 1];
    }

    [[nodiscard]]
    constexpr const T & back() const {
        return arr[len - 1];
    }

    [[nodiscard]]
    constexpr T & front() {
        return arr[0];
    }

    [[nodiscard]]
    constexpr const T & front() const {
        return arr[0];
    }

    [[nodiscard]]
    constexpr T & operator[](size_t index) {
        return arr[index];
    }

    [[nodiscard]]
    constexpr const T & operator[](size_t index) const {
        return arr[index];
    }
    
    T *begin(){
      return &arr[0];
    }
    
    T *end(){
      return &arr[len];
    }

    [[nodiscard]]
    constexpr T & at(size_t index) {
        return (index >= len) ? throw std::out_of_range("Vector index out of range") : arr[index];
    }

    [[nodiscard]]
    constexpr const T & at(size_t index) const {
        return (index >= len) ? throw std::out_of_range("Vector index out of range") : arr[index];
    }

};
