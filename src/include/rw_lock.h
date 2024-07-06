//
// Created by 20473 on 2024/7/6.
//

#ifndef RW_LOCK_H
#define RW_LOCK_H
#include <shared_mutex>

namespace FileSystem {
/**
 *
 */
class ReaderWriterLock {
   public:
    void WLock() { lock_.lock(); }

    void WUnlock() { lock_.unlock(); }

    void RLock() { lock_.lock_shared(); }

    void RUnlock() { lock_.unlock_shared(); }

   private:
    std::shared_mutex lock_;
};
}  // namespace FileSystem
#endif  // RW_LOCK_H
