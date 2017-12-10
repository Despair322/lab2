#include <iostream>
#include <tuple>
#include <future>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "semafor.h"

int main()
{
    int limit = 20;
    int threads = 4000;

    std::vector<std::string> logs(2 * threads);
    std::vector<std::future<void>> handles(threads);

    auto func = [limit, &logs]() {
        static Semafor semafor(limit);
        int clock, count;

        std::tie(clock, count) = semafor.Enter();
        std::stringstream buffer;
        buffer << (limit - count) << '/' << limit << " — Вход в семафор\n";
        logs[clock] = buffer.str();

        std::tie(clock, count) = semafor.Leave();
        buffer.str("");
        buffer << (limit - count) << '/' << limit << " — Выход из семафора\n";
        logs[clock] = buffer.str();
    };

    for (int i = 0; i < threads; ++i)
        handles[i] = std::async(std::launch::async, func);

    for (int i = 0; i < threads; ++i)
        handles[i].wait();

    for (int i = 0; i < 2 * threads; ++i)
        std::clog << logs[i];
}
