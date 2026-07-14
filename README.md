# Redis Lab

Redis Lab is a C++ systems programming project that explores the design and implementation of a high-performance in-memory key-value database inspired by Redis.

The goal is not to recreate Redis feature-by-feature, but to study different server architectures, concurrency models, storage engines, and performance trade-offs.

---

## Goals

- Build an in-memory key-value database from first principles.
- Compare blocking, thread-pooled, and event-driven server architectures.
- Study synchronization techniques and concurrent data structures.
- Measure scalability through systematic benchmarking.
- Apply modern C++17/20, Linux systems programming, and networking concepts in a production-style codebase.

---

## Architecture Roadmap

### Version 1
- [x] Storage Engine
- [x] Single-threaded Blocking TCP Server

### Version 2
- [ ] epoll Event Loop
- [ ] Thread Pool
- [ ] Shared Storage Engine

### Version 3
- [ ] Sharded Storage Engine
- [ ] Concurrent Request Processing
- [ ] Benchmarking

---
## Why Multiple Versions?

Instead of implementing a single server, this project incrementally explores different concurrency architectures:

1. Blocking Server
2. Thread Pool + epoll
3. Sharded Storage Engine

Each version will be benchmarked to compare throughput, latency, CPU utilization, and scalability.
---

## Current Features

### Storage Engine

Supported commands:

- SET
- GET
- DEL
- EXISTS

### Networking

- Blocking TCP server
- Persistent client connections
- Simple request/response protocol

---

## Project Structure

```
include/
    server/
    storage/
    threadpool/

src/
    server/
    storage/
    main.cpp
```

---

## Build

```bash
cmake -S . -B build
cmake --build build
```

Run:

```bash
./build/redis_lab
```

---

## Future Work

- Custom HashMap
- RESP protocol
- Command parser
- LRU Cache
- Snapshot persistence
- Append-only log (AOF)
- Lock-free queue
- Benchmark suite