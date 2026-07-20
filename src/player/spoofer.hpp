#pragma once
#include <string>
#include <unordered_map>
#include "../utils/singleton.hpp"

namespace player {
class Spoofer : public utils::Singleton<Spoofer> {
public:
    void set_spoofed_item(uint32_t item_id) {
        // We only support spoofing one item at a time for this basic implementation.
        // We can extend this to track hat, shirt, pants, etc. based on item type if we had item types.
        last_spoofed_item_ = item_id;
    }

    [[nodiscard]] uint32_t get_last_spoofed_item() const {
        return last_spoofed_item_;
    }

    void clear() {
        last_spoofed_item_ = 0;
    }

private:
    uint32_t last_spoofed_item_{ 0 };
};
}
