//
// Created by chenh on 6/16/2020.
//

#include "smart_array_temp.h"
#include <exception>
using namespace std;

template<typename T>
SmartArray<T> SmartArray<T>::copy() const {
    if (ref_count == nullptr)
        throw std::exception();
    SmartArray<T> ret;
    ret.elem = elem;
    ret.ref_count = ref_count;
    if (ref_count != nullptr) {
        *ref_count += 1;
    }
    return ret;
}

template<typename T>
SmartArray<T> SmartArray<T>::make_array(size_t size) {
    SmartArray<T> ret;
    ret.elem = new T[size];
    ret.ref_count = new unsigned int;
    *ret.ref_count = 1;
    return ret;
}

template<typename T>
const T &SmartArray<T>::operator[](int index) const {
    return elem[index];
}

template<typename T>
T &SmartArray<T>::operator[](int index) {
    return elem[index];
}

template<typename T>
SmartArray<T>::~SmartArray() {
    release();
}

template<typename T>
SmartArray<T> &SmartArray<T>::operator=(const SmartArray<T> &other) {
    if (this == &other)
        return *this;

    release();
    elem = other.elem;
    ref_count = other.ref_count;
    if (ref_count != nullptr)
        *ref_count += 1;
}

template<typename T>
SmartArray<T> &SmartArray<T>::operator=(SmartArray<T> &&other) noexcept{
    T *temp_elem = elem;
    unsigned int *temp_count = ref_count;

    elem = other.elem;
    ref_count = other.ref_count;

    other.elem = temp_elem;
    other.ref_count = temp_count;

    return *this;
}

template<typename T>
void SmartArray<T>::release() {
    bool release_elem = true;

    if (ref_count != nullptr) {
        if (*ref_count > 1) {
            *ref_count -= 1;
            release_elem = false;
            ref_count = nullptr;
        } else {
            delete ref_count;
            ref_count = nullptr;
        }
    }

    if (elem != nullptr) {
        if (release_elem)
            delete elem;
        elem = nullptr;
    }
}
