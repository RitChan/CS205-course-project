//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_SMART_ARRAY_DECL_H
#define COURSEPROJECT_SMART_ARRAY_DECL_H

#include <cstdlib>
#include <utility>

namespace mat {

    template<typename T>
    class SmartArray {
    public:
        static SmartArray<T> make_array(size_t size);

        SmartArray() = default;
        SmartArray(const SmartArray<T> &other) { *this = other; };
        SmartArray(SmartArray<T> &&other) noexcept { *this = std::forward<SmartArray<T>>(other); };
        SmartArray<T> &operator=(const SmartArray<T> &other); // TODO add test
        SmartArray<T> &operator=(SmartArray<T> &&other) noexcept; // TODO add test
        ~SmartArray();

        T &operator[](int index);
        const T &operator[](int index) const;

        SmartArray<T> shallow_copy() const;
        void release();
        unsigned int get_ref_count() const { return ref_count == nullptr ? 0 : (*ref_count); }

    private:
        T *elem{nullptr};
        unsigned int *ref_count{nullptr};
    };

}
#endif //COURSEPROJECT_SMART_ARRAY_DECL_H
