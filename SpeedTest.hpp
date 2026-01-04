#ifndef SPEEDTEST_HPP
#define SPEEDTEST_HPP

#include <string>

struct LatencyResult {
    double avgLatencyMs;
    double jitterMs;
};

class SpeedTest {
public:
    SpeedTest();
    ~SpeedTest();

    LatencyResult testLatency(int iterations = 10);
    double testDownload(long bytes = 10000000);
    double testUpload(long bytes = 5000000);

private:
    std::string exec(const char* cmd);
    double bytesToMB(double bytes);
};

#endif // SPEEDTEST_HPP
