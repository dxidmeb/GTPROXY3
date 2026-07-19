#pragma once
#include <string>
#include <fmt/format.h>

#include "../command.hpp"
#include "../command_registry.hpp"
#include "../../packet/packet_helper.hpp"
#include "../../packet/message/chat.hpp"
#include "../../packet/packet_variant.hpp"

namespace command {
class FindCommand final : public ICommand {
public:
    [[nodiscard]] std::string_view name() const override { return "find"; }
    [[nodiscard]] std::string description() const override { return "Find and visually spoof an item"; }

    Result execute(const Context& ctx) override
    {
        // We will send a dialog request to the client
        packet::PacketVariant dialog_req{};
        dialog_req.add("OnDialogRequest");
        
        std::string dialog = 
            "set_default_color|`o\n"
            "add_label_with_icon|big|`wFind Item``|left|6016|\n"
            "add_text_input|item_query|Item Name:|50|\n"
            "end_dialog|find_item_dialog|Cancel|Search!|\n";
            
        dialog_req.add(dialog);
        
        packet::VariantPayload payload{ dialog_req };
        auto raw_data = packet::PacketHelper::serialize(payload);
        raw_data.push_back(static_cast<std::byte>(0x00));
        
        ctx.client.write(raw_data, 0);

        return Result::Success;
    }
};
}
