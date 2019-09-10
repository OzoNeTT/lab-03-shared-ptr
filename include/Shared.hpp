#pragma once
#include <atomic>
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <string>

using namespace std;

template <typename T>
class SharedPtr {
private:
    T* pointer;
    atomic_uint *totalUse;
public:
    SharedPtr() {
        pointer = nullptr;
        totalUse = nullptr;
    }
    explicit SharedPtr(T *ptr) {
        pointer = ptr;
        totalUse = new atomic_uint{1};
    }

    SharedPtr(const SharedPtr& r) {
        totalUse = nullptr;
        *this = r;
    }

    SharedPtr(SharedPtr&& r) {
        totalUse = nullptr;
        *this = std::forward<SharedPtr>(r);
    }
    auto operator=(const SharedPtr& r) -> SharedPtr& {
        if (this == &r)
            return *this;
        if (totalUse != nullptr) {
            --(*totalUse);
            if (*totalUse == 0) {
                delete pointer;
                delete totalUse;
            }
        }
        pointer = r.pointer; totalUse = r.totalUse;
        (*totalUse)++;
        return *this;

    }
    auto operator=(SharedPtr&& r) -> SharedPtr&{
        if (this == &r)
            return *this;
        if (totalUse != nullptr) {
            --(*totalUse);
            if (*totalUse == 0) {
                delete pointer;
                delete totalUse;
            }
        }
        pointer = r.pointer; totalUse = r.totalUse;
        r.pointer = nullptr; r.totalUse = nullptr;
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const {
        if (pointer != nullptr)
            return true;
        return false;
    }

    auto operator*() const -> T&{
        return *pointer;
    }

    auto operator->() const -> T* {
        return pointer;
    }

    auto get() -> T*{
        return pointer;
    }

    void reset() {
        if (totalUse != nullptr) {
            --(*totalUse);
            if (*totalUse == 0) {
                delete pointer;
                delete totalUse;
            }
            pointer = nullptr;
            totalUse = nullptr;
        }
    }

    void reset(T* ptr){
        if (totalUse != nullptr) {
            --(*totalUse);
            if (*totalUse == 0) {
                delete pointer;
                delete totalUse;
            }
        }
        pointer = ptr;
        totalUse = new SharedPtr{1};
        totalUse++;
    }

    void swap(SharedPtr& r) {
        std::swap(pointer, r.pointer);
        std::swap(totalUse, r.totalUse);
    }

    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t {
        return *totalUse;
    }
    ~SharedPtr() {
        if( totalUse == nullptr)
            return;
        --(*totalUse);
        if (*totalUse == 0) {
            delete pointer;
            delete totalUse;
        }
    }

};