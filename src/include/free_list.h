//
// Created by 20473 on 2024/7/7.
//

#ifndef FREE_LIST_H
#define FREE_LIST_H
#include <list>
namespace FileSystem {
/**
 * 基于std::list实现空闲列表，非线程安全。
 * @tparam T 空闲列表类型
 */
template <class T>
class FreeList {
   public:
    auto Get() const -> T;
    auto Put(const T& object) -> bool;
    auto Pop(T& object) -> bool;
    [[nodiscard]] auto Empty() const -> bool;

   private:
    std::list<T> free_list_;
};

template <typename T>
auto FreeList<T>::Get() const -> T {
    return free_list_.front();
}

template <typename T>
auto FreeList<T>::Put(const T& object) -> bool {
    free_list_.push_back(object);
    return true;
}

template <typename T>
auto FreeList<T>::Pop(T& object) -> bool {
    object = free_list_.front();
    free_list_.pop_front();
    return true;
}

template <typename T>
auto FreeList<T>::Empty() const -> bool {
    return free_list_.empty();
}
}  // namespace FileSystem

#endif  // FREE_LIST_H
