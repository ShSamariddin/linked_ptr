//
// Created by samariddin on 25.02.19.
//

#ifndef UNTITLED2_LINKED_PTR_H
#define UNTITLED2_LINKED_PTR_H
#include <iostream>


namespace {
    struct smart_ptr {
        smart_ptr() {};

        smart_ptr(smart_ptr *left, smart_ptr *right) {
            this->left = left;
            this->right = right;
        }

        ~smart_ptr() = default;

        void remove() {
            if (right) {
                right->left = left;
            }
            if (left) {
                left->right = right;
            }
            left = nullptr;
            right = nullptr;
        }

        void insert_b(smart_ptr *other) {
            left = other->left;
            right = other;

            if(other->left) {
                other->left->right = this;
            }
            other->left = this;
        }

        void swap(smart_ptr *other) {

            smart_ptr *first;
            if (other->left)
                first = other->left;
            else
                first = other->right;

            smart_ptr *second;
            if (left)
                second = left;
            else
                second = right;


            remove();
            other->remove();

            if (first)
                first->insert_b(this);
            if (second)
                second->insert_b(other);
        }
        void clear(){
            left = nullptr;
            right = nullptr;
        }

        smart_ptr *left = nullptr;
        smart_ptr *right = nullptr;
    };

    template<typename T>
    struct linked_ptr {
        template<typename U>
        friend struct linked_ptr;

    public:

        linked_ptr() : ptr(nullptr), data(nullptr, nullptr) {}

        explicit linked_ptr(T *p) : ptr(p), data(nullptr, nullptr) {}

        linked_ptr(std::nullptr_t): ptr(nullptr), data(nullptr, nullptr) {}


        template<typename Y>
        linked_ptr(linked_ptr<Y> &other) {
            ptr = other.ptr;
            data.insert_b(&other.data);
        }

        linked_ptr(linked_ptr &other) {
            ptr = other.ptr;
            data.insert_b(&other.data);
        }

        linked_ptr(linked_ptr const &other) : linked_ptr(const_cast<linked_ptr&>(other)){

        };

        template<typename U>
        linked_ptr(linked_ptr<U> const &other) : linked_ptr(const_cast<linked_ptr<U>&>(other)){

        };

        template<typename Y>
        linked_ptr &operator=(linked_ptr<Y> &other) {
            linked_ptr temp(other);
            swap(temp);
            return *this;
        }

        linked_ptr &operator=(linked_ptr &other) {
            linked_ptr temp(other);
            swap(temp);
            return *this;
        }

        template<typename Y>
        linked_ptr(linked_ptr<Y> &other, T *p) {
            this = other;
            ptr = p;
        }

        linked_ptr(linked_ptr &&other) {
            ptr = other.ptr;
            data = other.data;
            other.ptr = nullptr;
            other.data.left = nullptr;
            other.data.right = nullptr;
        }

        linked_ptr &operator=(linked_ptr &&other) {
            ptr = other.ptr;
            data = other.data;
            other.ptr = nullptr;
            other.data.left = nullptr;
            other.data.right = nullptr;
            return *this;
        }

        template<typename Y>
        void reset(Y *p) {
            linked_ptr temp(p);
            swap(temp);
        }

        void reset() {
            linked_ptr temp;
            swap(temp);
        }

        T *get() const {
            return ptr;
        }

        T *operator->() const {
            return get();
        }

        T &operator*() const {
            return *get();
        }

        bool unique() const {
            return (!data.left && !data.right) && ptr;
        }

        operator bool() const {
            return get() != nullptr;
        }

        ~linked_ptr() {
            //destroy();
            if(unique() && ptr) {

                delete ptr;

            } else if (ptr){
                data.remove();
            }
            ptr = nullptr;
        }

        void swap(linked_ptr &other) {
            std::swap(ptr, other.ptr);
            data.swap(&other.data);
        }

        //

        bool operator==(T *t) const {
            return ptr == t;
        }

        bool operator!=(T *t) const {
            return ptr != t;
        }

        bool operator>(T *t) const {
            return ptr > t;
        }

        bool operator>=(T *t) const {
            return ptr >= t;
        }

        bool operator<(T *t) const {
            return ptr < t;
        }

        bool operator<=(T *t) const {
            return ptr <= t;
        }

        template<typename U>
        bool operator==(linked_ptr<U> const &other) const {
            return other.ptr == ptr;
        }

        template<typename U>
        bool operator!=(linked_ptr<U> const &other) const {
            return other.ptr != ptr;
        }

        template<typename U>
        bool operator<(linked_ptr<U> const &other) const {
            return other.ptr < ptr;
        }

        template<typename U>
        bool operator<=(linked_ptr<U> const &other) const {
            return other.ptr <= ptr;
        }

        template<typename U>
        bool operator>(linked_ptr<U> const &other) const {
            return other.ptr > ptr;
        }

        template<typename U>
        bool operator>=(linked_ptr<U> const &other) const {
            return other.ptr >= ptr;
        }


    private:
        T *ptr;
        smart_ptr data;
    };

    template <typename T, typename U>
    bool operator!=(linked_ptr<T> const& a, linked_ptr<U> const& b) noexcept
    {
        return !(a == b);
    }


}
#endif //UNTITLED2_LINKED_PTR_H
