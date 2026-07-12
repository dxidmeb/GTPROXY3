# Graph Report - c:/Users/fuzzy/Downloads/GTProxy-3.0/GTProxy-3.0  (2026-07-12)

## Corpus Check
- Corpus is ~17,513 words - fits in a single context window. You may not need a graph.

## Summary
- 878 nodes · 1523 edges · 55 communities (52 shown, 3 thin omitted)
- Extraction: 96% EXTRACTED · 4% INFERRED · 0% AMBIGUOUS · INFERRED: 59 edges (avg confidence: 0.81)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- [[_COMMUNITY_Scheduler Core Module|Scheduler Core Module]]
- [[_COMMUNITY_Command Packet Module|Command Packet Module]]
- [[_COMMUNITY_Randutils Seed Module|Randutils Seed Module]]
- [[_COMMUNITY_Byte Stream Module|Byte Stream Module]]
- [[_COMMUNITY_Network Dns Module|Network Dns Module]]
- [[_COMMUNITY_Network Server Module|Network Server Module]]
- [[_COMMUNITY_Parse Text Module|Parse Text Module]]
- [[_COMMUNITY_Packet Registry Module|Packet Registry Module]]
- [[_COMMUNITY_Player World Module|Player World Module]]
- [[_COMMUNITY_Server Core Module|Server Core Module]]
- [[_COMMUNITY_Client Network Module|Client Network Module]]
- [[_COMMUNITY_Packet Game Module|Packet Game Module]]
- [[_COMMUNITY_Command Registry Module|Command Registry Module]]
- [[_COMMUNITY_Handler Core Module|Handler Core Module]]
- [[_COMMUNITY_Event Typedpacketevent Module|Event Typedpacketevent Module]]
- [[_COMMUNITY_Packet Message Module|Packet Message Module]]
- [[_COMMUNITY_Command Handler Module|Command Handler Module]]
- [[_COMMUNITY_Packet Game Module|Packet Game Module]]
- [[_COMMUNITY_Event Rawpacketevent Module|Event Rawpacketevent Module]]
- [[_COMMUNITY_Packet Game Module|Packet Game Module]]
- [[_COMMUNITY_Packet Types Module|Packet Types Module]]
- [[_COMMUNITY_Core Handler Module|Core Handler Module]]
- [[_COMMUNITY_Packet Variant Module|Packet Variant Module]]
- [[_COMMUNITY_Packet Event Module|Packet Event Module]]
- [[_COMMUNITY_Logger Core Module|Logger Core Module]]
- [[_COMMUNITY_Packet Helper Module|Packet Helper Module]]
- [[_COMMUNITY_Event Priorityeventdispatcher Module|Event Priorityeventdispatcher Module]]
- [[_COMMUNITY_Core Network Module|Core Network Module]]
- [[_COMMUNITY_Packet Helper Module|Packet Helper Module]]
- [[_COMMUNITY_Packet Helper Module|Packet Helper Module]]
- [[_COMMUNITY_Packet Game Module|Packet Game Module]]
- [[_COMMUNITY_Cmake Github Module|Cmake Github Module]]
- [[_COMMUNITY_Input Message Module|Input Message Module]]
- [[_COMMUNITY_Command Icommand Module|Command Icommand Module]]
- [[_COMMUNITY_Command Commands Module|Command Commands Module]]
- [[_COMMUNITY_Command Commands Module|Command Commands Module]]
- [[_COMMUNITY_Command Commands Module|Command Commands Module]]
- [[_COMMUNITY_Command Commands Module|Command Commands Module]]
- [[_COMMUNITY_Command Commands Module|Command Commands Module]]
- [[_COMMUNITY_Command Commands Module|Command Commands Module]]
- [[_COMMUNITY_Event Packet Module|Event Packet Module]]
- [[_COMMUNITY_Hash Fnv1a Module|Hash Fnv1a Module]]
- [[_COMMUNITY_Types Immobile Module|Types Immobile Module]]
- [[_COMMUNITY_Cmakelists Gtproxy Module|Cmakelists Gtproxy Module]]
- [[_COMMUNITY_Event Priority Module|Event Priority Module]]
- [[_COMMUNITY_Packet Message Module|Packet Message Module]]
- [[_COMMUNITY_Packet Variant Module|Packet Variant Module]]
- [[_COMMUNITY_Packet Payload Module|Packet Payload Module]]
- [[_COMMUNITY_Conanfile Gtproxyrecipe Module|Conanfile Gtproxyrecipe Module]]
- [[_COMMUNITY_Message Server Module|Message Server Module]]
- [[_COMMUNITY_Packet Helper Module|Packet Helper Module]]
- [[_COMMUNITY_Agents Httplib Module|Agents Httplib Module]]
- [[_COMMUNITY_Conanfile Module|Conanfile Module]]

## God Nodes (most connected - your core abstractions)
1. `Scheduler` - 53 edges
2. `Client` - 29 edges
3. `Server` - 27 edges
4. `OnSpawn` - 24 edges
5. `Core` - 22 edges
6. `IPacket` - 22 edges
7. `ByteStream` - 22 edges
8. `Player` - 20 edges
9. `seed_seq_fe` - 20 edges
10. `WebServer` - 19 edges

## Surprising Connections (you probably didn't know these)
- `CMake` --semantically_similar_to--> `CMake`  [INFERRED] [semantically similar]
  AGENTS.md → .github/workflows/cmake_build.yml
- `Conan` --semantically_similar_to--> `Conan`  [INFERRED] [semantically similar]
  AGENTS.md → .github/workflows/cmake_build.yml
- `Growtopia Proxy` --semantically_similar_to--> `GTProxy`  [INFERRED] [semantically similar]
  README.md → AGENTS.md
- `GTest` --semantically_similar_to--> `Google Test`  [INFERRED] [semantically similar]
  tests/CMakeLists.txt → AGENTS.md
- `TEST()` --references--> `ByteStream`  [INFERRED]
  tests/utils/test_byte_stream.cpp → src/utils/byte_stream.hpp

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **GTProxy Technology Stack** — agents_gtproxy, agents_cmake, agents_conan, agents_enet, agents_gtest, agents_cpp_httplib [EXTRACTED 1.00]

## Communities (55 total, 3 thin omitted)

### Community 0 - "Scheduler Core Module"
Cohesion: 0.05
Nodes (61): atomic, condition_variable, function, greater, priority_queue, queue, run, milliseconds (+53 more)

### Community 1 - "Command Packet Module"
Cohesion: 0.07
Nodes (28): PayloadType, CommandRegistry, Context, args, raw_input, Dispatcher, Func, Result (+20 more)

### Community 2 - "Randutils Seed Module"
Cohesion: 0.05
Nodes (49): array, count, default_seeds, engine_type, initializer_list, InputIter, IntRep, Iter (+41 more)

### Community 3 - "Byte Stream Module"
Cohesion: 0.09
Nodes (27): ByteStreamTest, LogConfig, optional, ReadVectorWithExplicitLength, SpanConstructor, byte, shared_ptr, span (+19 more)

### Community 4 - "Network Dns Module"
Cohesion: 0.07
Nodes (32): DnsStatus, HostType, CloudflareDnsProvider, string, string_view, unique_ptr, vector, create_dns_provider() (+24 more)

### Community 5 - "Network Server Module"
Cohesion: 0.07
Nodes (33): IConnection, is_connected, write, ENetHost, ENetWrapper, host_, on_connect, on_disconnect (+25 more)

### Community 6 - "Parse Text Module"
Cohesion: 0.09
Nodes (32): AddSetRemove, else, GetKeyValues, GetRaw, GetTypedValues, HeterogeneousAddSet, IdiotGrowtopiaParse, is_floating_point_v (+24 more)

### Community 7 - "Packet Registry Module"
Cohesion: 0.08
Nodes (27): PacketFactory, regex, Singleton<PacketRegistry>, derive_packet_id(), PacketId, Payload, string, string_view (+19 more)

### Community 8 - "Player World Module"
Cohesion: 0.08
Nodes (19): Singleton<World>, i32vec2, i32vec4, string, Player, collision_, country_code_, invisible_ (+11 more)

### Community 9 - "Server Core Module"
Cohesion: 0.11
Nodes (21): Dispatcher, Dispatcher, string, thread, WebServer, dns_resolver_, https_server_, listen_internal (+13 more)

### Community 10 - "Client Network Module"
Cohesion: 0.14
Nodes (22): Client, connect, create_host, decoder_, disconnect, disconnect_now, flush, is_connected (+14 more)

### Community 11 - "Packet Game Module"
Cohesion: 0.10
Nodes (19): i32vec2, i32vec4, string, OnSpawn, collision, country_code, game_packet, invisible (+11 more)

### Community 12 - "Command Registry Module"
Cohesion: 0.23
Nodes (13): CommandRegistry, commands_, execute, get, get_all_commands, is_command, parse, Dispatcher (+5 more)

### Community 13 - "Handler Core Module"
Cohesion: 0.24
Nodes (16): Dispatcher, Dispatcher, string, SessionHandler, pending_address_, pending_port_, SessionHandler::SessionHandler(), setup_connection_handlers (+8 more)

### Community 14 - "Event Typedpacketevent Module"
Cohesion: 0.15
Nodes (10): get(), Direction, shared_ptr, T, PacketEvent, packet, packet_id, TypedPacketEvent (+2 more)

### Community 15 - "Packet Message Module"
Cohesion: 0.15
Nodes (9): Payload, string, JoinRequest, invited_world, world_name, Quit, QuitToExit, ValidateWorld (+1 more)

### Community 16 - "Command Handler Module"
Cohesion: 0.14
Nodes (14): CommandRegistry, CommandHandler, CommandHandler::CommandHandler(), listener_handle_, on_text_packet, register_default_commands, registry_, Dispatcher (+6 more)

### Community 17 - "Packet Game Module"
Cohesion: 0.13
Nodes (13): PACKET_DISCONNECT, Disconnect, Payload, string, OnSendToServer, address, door_id, login_mode (+5 more)

### Community 18 - "Event Rawpacketevent Module"
Cohesion: 0.18
Nodes (9): ConnectionEvent, Event, canceled, type, EventPolicies, byte, RawPacketEvent, data (+1 more)

### Community 19 - "Packet Game Module"
Cohesion: 0.14
Nodes (10): Payload, string, OnChangeSkin, game_packet, net_id, skin_code, OnNameChanged, game_packet (+2 more)

### Community 20 - "Packet Types Module"
Cohesion: 0.13
Nodes (14): GameUpdatePacket, data_size, decompressed_data_size, flags, net_id, pad, pad_2, pad_3 (+6 more)

### Community 21 - "Core Handler Module"
Cohesion: 0.14
Nodes (13): Core, client_, command_handler_, config_, dispatcher_, running_, scheduler_, server_ (+5 more)

### Community 22 - "Packet Variant Module"
Cohesion: 0.23
Nodes (8): byte, vector, PacketVariant, variants_, variant, format(), FormatContext, VariantType

### Community 23 - "Packet Event Module"
Cohesion: 0.19
Nodes (9): PacketEventBuilder, Direction, PacketId, shared_ptr, unordered_map, make_event_builder(), PacketEventRegistry, builders_ (+1 more)

### Community 24 - "Logger Core Module"
Cohesion: 0.23
Nodes (5): rotating_file_sink_mt, shared_ptr, Logger, main(), stdout_color_sink_mt

### Community 25 - "Packet Helper Module"
Cohesion: 0.21
Nodes (13): GamePacket, CHANNEL, ID, MESSAGE_TYPE, PACKET_TYPE, NetMessageType, PacketId, PacketType (+5 more)

### Community 26 - "Event Priorityeventdispatcher Module"
Cohesion: 0.23
Nodes (9): BaseDispatcher, Callback, map, PriorityEntry, Handle, vector, PriorityEventDispatcher, dispatcher_ (+1 more)

### Community 27 - "Core Network Module"
Cohesion: 0.41
Nodes (3): span, Packet, write()

### Community 28 - "Packet Helper Module"
Cohesion: 0.24
Nodes (6): enable_shared_from_this<IPacket>, shared_ptr, IPacket, id, read, write

### Community 29 - "Packet Helper Module"
Cohesion: 0.24
Nodes (7): Sender, byte, Packet, Payload, vector, PacketHelper, write()

### Community 30 - "Packet Game Module"
Cohesion: 0.22
Nodes (5): Payload, OnRemove, game_packet, net_id, player_id

### Community 31 - "Cmake Github Module"
Cohesion: 0.25
Nodes (9): Build Workflow, CMake, Conan, CI Workflow, CMake, Conan, ENet, GTProxy (+1 more)

### Community 32 - "Input Message Module"
Cohesion: 0.33
Nodes (5): NET_MESSAGE_GENERIC_TEXT, Payload, string, Input, text

### Community 33 - "Command Icommand Module"
Cohesion: 0.29
Nodes (6): ICommand, description, execute, name, add, unique_ptr

### Community 34 - "Command Commands Module"
Cohesion: 0.29
Nodes (4): ExitCommand, Result, string, string_view

### Community 35 - "Command Commands Module"
Cohesion: 0.33
Nodes (4): HelpCommand, Result, string, string_view

### Community 36 - "Command Commands Module"
Cohesion: 0.29
Nodes (4): Result, string, string_view, NickCommand

### Community 37 - "Command Commands Module"
Cohesion: 0.29
Nodes (4): Result, string, string_view, ProxyCommand

### Community 38 - "Command Commands Module"
Cohesion: 0.29
Nodes (4): Result, string, string_view, SkinCommand

### Community 39 - "Command Commands Module"
Cohesion: 0.29
Nodes (4): Result, string, string_view, WarpCommand

### Community 40 - "Event Packet Module"
Cohesion: 0.48
Nodes (5): PacketId, is_packet_event(), packet_event_offset(), packet_event_type(), packet_id_from_type()

### Community 41 - "Hash Fnv1a Module"
Cohesion: 0.43
Nodes (6): fnv1a_32(), size_t, string_view, operator "" _fnv1a_32(), operator "" _proton(), proton()

### Community 42 - "Types Immobile Module"
Cohesion: 0.29
Nodes (3): Immobile, NoCopy, NoMove

### Community 43 - "Cmakelists Gtproxy Module"
Cohesion: 0.33
Nodes (6): Google Test, GTProxy, GTProxy-Library, Proxy, GTest, GTProxy_tests

### Community 44 - "Event Priority Module"
Cohesion: 0.33
Nodes (6): Priority, FairlyHigh, FairlyLow, Highest, Lowest, Normal

### Community 45 - "Packet Message Module"
Cohesion: 0.40
Nodes (4): Payload, string, Log, msg

### Community 46 - "Packet Variant Module"
Cohesion: 0.47
Nodes (4): add(), get(), size_t, T

### Community 47 - "Packet Payload Module"
Cohesion: 0.47
Nodes (5): GamePayload, extra, packet, byte, vector

### Community 49 - "Message Server Module"
Cohesion: 0.50
Nodes (3): NET_MESSAGE_SERVER_HELLO, Payload, ServerHello

### Community 50 - "Packet Helper Module"
Cohesion: 0.50
Nodes (4): TextPacket, CHANNEL, ID, MESSAGE_TYPE

## Knowledge Gaps
- **170 isolated node(s):** `args`, `raw_input`, `name`, `description`, `execute` (+165 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **3 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Scheduler` connect `Scheduler Core Module` to `Command Handler Module`, `Command Packet Module`, `Command Registry Module`, `Core Handler Module`?**
  _High betweenness centrality (0.115) - this node is a cross-community bridge._
- **Why does `Context` connect `Command Packet Module` to `Scheduler Core Module`, `Command Commands Module`, `Command Commands Module`, `Command Commands Module`, `Network Server Module`, `Command Commands Module`, `Command Commands Module`, `Command Commands Module`, `Client Network Module`?**
  _High betweenness centrality (0.079) - this node is a cross-community bridge._
- **Why does `Client` connect `Client Network Module` to `Command Packet Module`, `Byte Stream Module`, `Network Dns Module`, `Network Server Module`, `Server Core Module`, `Command Registry Module`, `Handler Core Module`, `Command Handler Module`, `Core Handler Module`, `Core Network Module`?**
  _High betweenness centrality (0.071) - this node is a cross-community bridge._
- **What connects `args`, `raw_input`, `name` to the rest of the system?**
  _170 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Scheduler Core Module` be split into smaller, more focused modules?**
  _Cohesion score 0.05454545454545454 - nodes in this community are weakly interconnected._
- **Should `Command Packet Module` be split into smaller, more focused modules?**
  _Cohesion score 0.07132867132867132 - nodes in this community are weakly interconnected._
- **Should `Randutils Seed Module` be split into smaller, more focused modules?**
  _Cohesion score 0.052600818234950324 - nodes in this community are weakly interconnected._