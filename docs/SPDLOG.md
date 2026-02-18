# spdlog

### Default Behavior

The default log level for **spdlog** is **`info`**.

This means messages at the `info` level and higher (more severe) are displayed, while `debug` and `trace` messages are hidden.

---

### Log Level Hierarchy

Spdlog filters messages based on this priority ladder:

| Level          | Priority | Description                                   |
| -------------- | -------- | --------------------------------------------- |
| **`trace`**    | 0        | Very noisy, low-level execution details.      |
| **`debug`**    | 1        | Information useful for development/debugging. |
| **`info`**     | 2        | **(Default)** General operational progress.   |
| **`warn`**     | 3        | Warnings about non-critical issues.           |
| **`err`**      | 4        | Error messages for failed operations.         |
| **`critical`** | 5        | Catastrophic failures.                        |
| **`off`**      | 6        | Disables all logging entirely.                |

---

### Changing the Level

Change the level globally at runtime (perfect for `--verbose` flag):

```cpp
// Show everything from debug upwards
spdlog::set_level(spdlog::level::debug);

// To check the current level
auto current_level = spdlog::get_level();

```

> **Note:** To use `SPDLOG_DEBUG()` or `SPDLOG_TRACE()` macros, ensure `#define SPDLOG_ACTIVE_LEVEL` is set to the desired level **before** including spdlog headers, or compiler might strip them out for performance.
