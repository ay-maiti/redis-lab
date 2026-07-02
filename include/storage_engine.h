#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

#include <optional>
#include <shared_mutex>
#include <string>
#include <unordered_map>

class StorageEngine
{
public:
    StorageEngine() = default;
    ~StorageEngine() = default;

    // Disable copying
    StorageEngine(const StorageEngine&) = delete;
    StorageEngine& operator=(const StorageEngine&) = delete;

    // Allow moving
    StorageEngine(StorageEngine&&) = default;
    StorageEngine& operator=(StorageEngine&&) = default;

    // Basic Redis commands
    bool Set(const std::string& key, const std::string& value);

    std::optional<std::string> Get(const std::string& key) const;

    bool Delete(const std::string& key);

    bool Exists(const std::string& key) const;

    std::size_t Size() const;

    void Clear();

private:
    mutable std::shared_mutex mutex_;

    std::unordered_map<std::string, std::string> store_;
};

#endif