#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <glaze/glaze.hpp>
#include <spdlog/spdlog.h>
#include "../utils/singleton.hpp"

namespace world {
class ItemDatabase : public utils::Singleton<ItemDatabase> {
public:
    void load(const std::string& filepath = "items.json") {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            spdlog::warn("Failed to open {}. Item search will be limited.", filepath);
            return;
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        auto err = glz::read_json(items_, content);
        if (err) {
            spdlog::error("Failed to parse items.json");
            return;
        }
        
        spdlog::info("Loaded {} items from item database.", items_.size());
    }

    std::vector<std::pair<std::string, uint32_t>> search(std::string query, size_t limit = 10) const {
        std::ranges::transform(query, query.begin(), ::tolower);
        std::vector<std::pair<std::string, uint32_t>> results;

        for (const auto& [name, id] : items_) {
            std::string lower_name = name;
            std::ranges::transform(lower_name, lower_name.begin(), ::tolower);
            
            if (lower_name.find(query) != std::string::npos) {
                results.emplace_back(name, id);
                if (results.size() >= limit) break;
            }
        }
        return results;
    }

private:
    std::unordered_map<std::string, uint32_t> items_;
};
}
