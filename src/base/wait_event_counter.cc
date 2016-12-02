#include "wait_event_counter.h"

namespace chef {

  wait_event_counter::wait_event_counter(int need_count)
    : need_count_(need_count)
    , count_(0)
  {
  }

  wait_event_counter::~wait_event_counter() {}

  void wait_event_counter::notify() {
    std::unique_lock<std::mutex> lock(mutex_);
    count_++;
    cond_.notify_one();
  }

  void wait_event_counter::wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (count_.load() < need_count_) {
      cond_.wait(lock);
    }
  }

} // namespace chef