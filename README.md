# C++ Cloudflare Speed Test Module

A high-performance, lightweight C++ module for testing network speed (Latency, Jitter, Download, Upload) using Cloudflare's speed test endpoints. This project serves as both a standalone CLI tool and a reusable C++ library.

## Features

- **Accurate**: Measures Latency, Jitter, Download Speed (MBps), and Upload Speed (MBps).
- **Lightweight**: Built with C++17 and `curl`. No heavy dependencies.
- **Modern CLI**: Beautiful, animated command-line interface with ANSI color support.
- **Reusable**: Easily integrate the `SpeedTest` class into your own C++ applications.

## Credits

- **Made by**: [Gemini AI](https://deepmind.google/technologies/gemini/)
- **Inspiration/Fork**: [XIU2/CloudflareSpeedTest](https://github.com/XIU2/CloudflareSpeedTest)

---

## 🚀 Quick Start (CLI)

### Prerequisites

- Linux/macOS (or Windows with WSL/MinGW)
- `g++` (supporting C++17)
- `curl` installed and available in PATH

### Build and Run

```bash
make
./speedtest
```

### Sample Output

```text
   Cloudflare Speed Test C++ Module
   ──────────────────────────────

✓ Testing Latency... Done!
   → Latency : 18.11 ms
   → Jitter  : 9.45 ms

✓ Testing Download... Done!
   ↓ Download: 0.45 MBps

✓ Testing Upload...   Done!
   ↑ Upload  : 0.52 MBps

   ──────────────────────────────
   Test Completed.
```

---

## 🛠 Integration Guide (C++ Module)

You can use the `SpeedTest` class directly in your own projects.

### 1. Copy Files

Copy the following files to your project directory:

- `SpeedTest.hpp`
- `SpeedTest.cpp`

### 2. Include and Use

Here is a minimal example of how to use the library:

```cpp
#include "SpeedTest.hpp"
#include <iostream>

int main() {
    SpeedTest st;

    // 1. Measure Latency
    LatencyResult lr = st.testLatency(); // returns {avg, jitter}
    std::cout << "Latency: " << lr.avgLatencyMs << " ms" << std::endl;

    // 2. Measure Download Speed (default ~50MB test)
    double download = st.testDownload();
    std::cout << "Download: " << download << " MBps" << std::endl;

    // 3. Measure Upload Speed (default ~20MB test)
    double upload = st.testUpload();
    std::cout << "Upload: " << upload << " MBps" << std::endl;

    return 0;
}
```

### 3. Compile

Ensure you link `SpeedTest.cpp` when compiling your application.

**Manual Compilation:**

```bash
g++ -std=c++17 -o my_app main.cpp SpeedTest.cpp
```

**CMake Example:**

```cmake
cmake_minimum_required(VERSION 3.10)
project(MySpeedTestApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_app main.cpp SpeedTest.cpp)
```

---

## ⚙️ Configuration

The methods accept optional parameters to tune the test:

- **`testLatency(int iterations)`**:
  - `iterations` (default: 10): Number of pings to perform.
- **`testDownload(long bytes)`**:

  - `bytes` (default: 50,000,000): Size of the file to download (in bytes).

- **`testUpload(long bytes)`**:
  - `bytes` (default: 20,000,000): Size of the data to upload (in bytes).

## License

MIT License
