#pragma once
#include "redis/command_with_single_schema.hh"
#include "redis/request.hh"

namespace service {
class storage_proxy;
}
class timeout_config;
namespace redis {
namespace commands {
class lset : public command_with_single_schema {
protected:
    bytes _key;
    long _index;
    bytes _value;
public:
    lset(bytes&& name, const schema_ptr schema, bytes&& key, long index, bytes&& value) 
        : command_with_single_schema(std::move(name), schema)
        , _key(std::move(key))
        , _index(index)
        , _value(std::move(value))
    {
    }
    ~lset() {}
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, const service::client_state& cs, request&& req);
    virtual future<redis_message> execute(service::storage_proxy&,
        db::consistency_level,
        db::timeout_clock::time_point,
        const timeout_config& tc,
        service::client_state& cs
        ) override;
};

}
}
