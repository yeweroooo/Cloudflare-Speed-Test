#include "SpeedTest.hpp"
#include <iostream>
#include <iomanip>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <string>

// ANSI Colors
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string CYAN = "\033[36m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string MAGENTA = "\033[35m";
const std::string RED = "\033[31m";

void show_spinner(std::atomic<bool>& done, const std::string& label) {
    const std::vector<std::string> spinner = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
    int i = 0;
    while (!done) {
        std::cout << "\r" << CYAN << spinner[i % spinner.size()] << RESET << " " << label << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        i++;
    }
    std::cout << "\r" << GREEN << "✓" << RESET << " " << label << " " << GREEN << "Done!" << RESET << "       " << std::endl;
}

int main() {
    // Clear screen for fresh start
    std::cout << "\033[2J\033[1;1H";

    std::cout << "" << std::endl;
    std::cout << CYAN << BOLD << "   Cloudflare Speed Test" << RESET << " " << "C++ Module" << std::endl;
    std::cout << "   ──────────────────────────────" << std::endl;
    std::cout << "" << std::endl;

    SpeedTest st;
    std::cout << std::fixed << std::setprecision(2);

    // Latency Test
    {
        std::atomic<bool> done{false};
        std::thread t(show_spinner, std::ref(done), "Testing Latency...");
        LatencyResult latency = st.testLatency();
        done = true;
        t.join();

        std::cout << "   " << MAGENTA << "→ Latency :" << RESET << " " << BOLD << latency.avgLatencyMs << " ms" << RESET << std::endl;
        std::cout << "   " << MAGENTA << "→ Jitter  :" << RESET << " " << BOLD << latency.jitterMs << " ms" << RESET << std::endl;
        std::cout << "" << std::endl;
    }

    // Download Test
    {
        std::atomic<bool> done{false};
        std::thread t(show_spinner, std::ref(done), "Testing Download...");
        double downloadSpeed = st.testDownload();
        done = true;
        t.join();

        std::cout << "   " << GREEN << "↓ Download:" << RESET << " " << BOLD << downloadSpeed << " MBps" << RESET << std::endl;
        std::cout << "" << std::endl;
    }

    // Upload Test
    {
        std::atomic<bool> done{false};
        std::thread t(show_spinner, std::ref(done), "Testing Upload...  ");
        double uploadSpeed = st.testUpload();
        done = true;
        t.join();

        std::cout << "   " << YELLOW << "↑ Upload  :" << RESET << " " << BOLD << uploadSpeed << " MBps" << RESET << std::endl;
        std::cout << "" << std::endl;
    }

    std::cout << "   " << std::string(30, ' ') << std::endl;
    std::cout << "   " << CYAN << "Made by Gemini AI" << RESET << std::endl;
    std::cout << "   " << "Inspired by XIU2/CloudflareSpeedTest" << std::endl;
    std::cout << "   ──────────────────────────────" << std::endl;
    std::cout << "   " << BOLD << "Test Completed." << RESET << std::endl;
    std::cout << "" << std::endl;

    return 0;
}
