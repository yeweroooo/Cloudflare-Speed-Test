#include "SpeedTest.hpp"
#include <iostream>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <fstream>

SpeedTest::SpeedTest() {}

SpeedTest::~SpeedTest() {}

std::string SpeedTest::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

double SpeedTest::bytesToMB(double bytes) {
    return bytes / (1024.0 * 1024.0);
}

LatencyResult SpeedTest::testLatency(int iterations) {
    std::vector<double> latencies;
    
    for (int i = 0; i < iterations; ++i) {
        try {
            std::string cmd = "curl -o /dev/null -s -w \"%{time_connect}\" \"https://speed.cloudflare.com/__down?bytes=0\"";
            std::string output = exec(cmd.c_str());
            double latSeconds = std::stod(output);
            latencies.push_back(latSeconds * 1000.0); // Convert to ms
        } catch (...) {
            continue;
        }
    }

    if (latencies.empty()) return {0.0, 0.0};

    double sum = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    double mean = sum / latencies.size();

    double sq_sum = std::inner_product(latencies.begin(), latencies.end(), latencies.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / latencies.size() - mean * mean);

    return {mean, stdev};
}

double SpeedTest::testDownload(long bytes) {
    std::string cmd = "curl -o /dev/null -s -w \"%{speed_download}\" \"https://speed.cloudflare.com/__down?bytes=" + std::to_string(bytes) + "\"";
    
    try {
        std::string output = exec(cmd.c_str());
        double speedBytesSec = std::stod(output);
        return bytesToMB(speedBytesSec);
    } catch (...) {
        return 0.0;
    }
}

double SpeedTest::testUpload(long bytes) {
    std::string tempFile = "temp_upload_data.bin";
    
    // Generate temp file
    {
        std::ofstream ofs(tempFile, std::ios::binary);
        if (!ofs) return 0.0;
        std::vector<char> buffer(1024 * 1024, 'A'); 
        long written = 0;
        while (written < bytes) {
             long toWrite = std::min((long)buffer.size(), bytes - written);
             ofs.write(buffer.data(), toWrite);
             written += toWrite;
        }
    }

    std::string cmd = "curl -o /dev/null -s -w \"%{speed_upload}\" --data-binary @" + tempFile + " \"https://speed.cloudflare.com/__up\"";
    
    try {
        std::string output = exec(cmd.c_str());
        std::filesystem::remove(tempFile);
        double speedBytesSec = std::stod(output);
        return bytesToMB(speedBytesSec);
    } catch (...) {
        std::filesystem::remove(tempFile);
        return 0.0;
    }
}
