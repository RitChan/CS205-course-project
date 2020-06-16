//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_SMART_ARRAY_TEMP_H
#define COURSEPROJECT_SMART_ARRAY_TEMP_H

#include <cstdlib>
#include <utility>

template<typename T>
class SmartArray {
public:
    friend class SmartArrayTest_makeArrayTest_Test;
    friend class SmartArrayTest_referToTest_Test;
    friend class SmartArrayTest_releaseTest_Test;

    static SmartArray<T> make_array(size_t size);

    SmartArray() = default;
    SmartArray(const SmartArray<T> &other) { *this = other; };
    SmartArray(SmartArray<T> &&other) noexcept { *this = std::forward<SmartArray<T>>(other); };
    SmartArray<T> &operator=(const SmartArray<T> &other);
    SmartArray<T> &operator=(SmartArray<T> &&other) noexcept;
    ~SmartArray();

    T &operator[](int index);
    const T&operator[](int index) const;

    SmartArray<T> copy() const;
    void release();

private:

    T *elem{nullptr};
    unsigned int *ref_count{nullptr};
};

#endif //COURSEPROJECT_SMART_ARRAY_TEMP_H
