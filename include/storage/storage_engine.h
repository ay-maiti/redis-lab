#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

#include <optional>
#include <string>
#include <unordered_map>

enum class Status
{
    OK,
    KEY_NOT_FOUND,
    INVALID_KEY
};

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
    Status Set(const std::string& key, const std::string& value);

    std::optional<std::string> Get(const std::string& key) const;

    Status Delete(const std::string& key);

    bool Exists(const std::string& key) const;

    std::size_t Size() const;

    void Clear();

private:
    std::unordered_map<std::string, std::string> store_;
};

#endif