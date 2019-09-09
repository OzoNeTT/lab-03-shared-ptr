#pragma once
#include <atomic>
#include <iostream>
#include <cstddef>

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
    SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    auto opeartor=(const SharedPtr& r) -> SharedPtr&;
    auto opeartor=(SharedPtr&& r) -> SharedPtr&;

    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;

    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t;
};