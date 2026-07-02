#include "storage_engine.h"

bool StorageEngine::Set(const std::string& key,
                        const std::string& value)
{
    std::unique_lock lock(mutex_);

    store_[key] = value;
    return true;
}

std::optional<std::string>
StorageEngine::Get(const std::string& key) const
{
    std::shared_lock lock(mutex_);

    auto it = store_.find(key);

    if (it == store_.end())
    {
        return std::nullopt;
    }

    return it->second;
}

bool StorageEngine::Delete(const std::string& key)
{
    std::unique_lock lock(mutex_);

    return store_.erase(key) > 0;
}

bool StorageEngine::Exists(const std::string& key) const
{
    std::shared_lock lock(mutex_);

    return store_.find(key) != store_.end();
}

std::size_t StorageEngine::Size() const
{
    std::shared_lock lock(mutex_);

    return store_.size();
}

void StorageEngine::Clear()
{
    std::unique_lock lock(mutex_);

    store_.clear();
}