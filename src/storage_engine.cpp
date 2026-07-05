#include "storage_engine.h"

bool StorageEngine::Set(const std::string& key,
                        const std::string& value)
{
    store_[key] = value;
    return true;
}

std::optional<std::string>
StorageEngine::Get(const std::string& key) const
{
    auto it = store_.find(key);

    if (it == store_.end())
    {
        return std::nullopt;
    }

    return it->second;
}

bool StorageEngine::Delete(const std::string& key)
{
    return store_.erase(key) > 0;
}

bool StorageEngine::Exists(const std::string& key) const
{
    return store_.find(key) != store_.end();
}

std::size_t StorageEngine::Size() const
{
    return store_.size();
}

void StorageEngine::Clear()
{
    store_.clear();
}