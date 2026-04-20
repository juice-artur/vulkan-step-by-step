#ifndef VULKAN_STEP_BY_STEP_DELETION_QUEUE_H
#define VULKAN_STEP_BY_STEP_DELETION_QUEUE_H

#include <functional>
#include <deque>

struct deletion_queue
{
    std::deque<std::function<void()>> deletors;

    void push_function(std::function<void()>&& function) {
        deletors.push_back(function);
    }

    void flush() {
        for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
            (*it)();
        }

        deletors.clear();
    }
};

#endif //VULKAN_STEP_BY_STEP_DELETION_QUEUE_H
