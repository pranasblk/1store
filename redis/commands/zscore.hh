#pragma once
#include "redis/command_with_single_schema.hh"
#include "redis/request.hh"
#include "redis/prefetcher.hh"
namespace query {
class result;
}

class timeout_config;
namespace redis {

namespace commands {
class zscore : public command_with_single_schema {
protected:
    bytes _key;
    std::vector<bytes> _map_keys;
public:
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, const service::client_state& cs, request&& req);
    zscore(bytes&& name, const schema_ptr schema, bytes&& key, std::vector<bytes>&& map_keys) 
        : command_with_single_schema(std::move(name), schema)
        , _key(std::move(key))
        , _map_keys(std::move(map_keys))
    {
    }
    ~zscore() {}
    future<redis_message> execute(service::storage_proxy&, db::consistency_level, db::timeout_clock::time_point, const timeout_config& tc, service::client_state& cs) override;
};

}
}
