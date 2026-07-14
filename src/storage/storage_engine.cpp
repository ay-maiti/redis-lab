#include "storage_engine.h"

Status StorageEngine::Set(const std::string& key,
                          const std::string& value)
{
    if (key.empty())
    {
        return Status::INVALID_KEY;
    }

    store_[key] = value;

    return Status::OK;
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

Status StorageEngine::Delete(const std::string& key)
{
    if (store_.erase(key) == 0)
    {
        return Status::KEY_NOT_FOUND;
    }

    return Status::OK;
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