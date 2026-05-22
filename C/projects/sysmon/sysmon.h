#pragma once

#include <stdint.h>

typedef struct {
    uint64_t uptime_seconds;     // Total uptime
    uint64_t idle_seconds;       // Total CPU idle time
} SysUptime;

typedef struct {
    uint64_t total_kb;          // Total RAM in kilobytes
    uint64_t free_kb;           // Free RAM in kilobytes
    uint64_t available_kb;      // Available RAM in kilobytes
    uint64_t buffers_kb;            // in kilobytes
    uint64_t cached_kb;             // in kilobytes
} SysMemory;

int read_uptime(SysUptime *uptime);      // Returns 0 on success, -1 on failure

int read_memory(SysMemory *memory);     // Returns 0 on success, -1 on failure

void format_uptime(const SysUptime *uptime, char *buffer, uint32_t buffer_len);

void format_memory_kb(uint64_t value_kb, char *buffer, uint32_t buffer_len);
