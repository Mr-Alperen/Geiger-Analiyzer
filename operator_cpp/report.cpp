#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

struct Entry {
    std::string timestamp;
    double alpha_cpm;
    double gamma_cpm;
};

int main() {
    std::ifstream log("log/geiger_log.txt");
    std::string line;
    std::vector<Entry> entries;

    while (std::getline(log, line)) {
        auto pos = line.find("{");
        if (pos != std::string::npos) {
            std::string timeStr = line.substr(0, pos-2);
            std::string json = line.substr(pos);

            double alpha, gamma;
            sscanf(json.c_str(), "{\"alpha_cps\":%*f,\"alpha_cpm\":%lf,\"gamma_cps\":%*f,\"gamma_cpm\":%lf}", &alpha, &gamma);

            entries.push_back({timeStr, alpha, gamma});
        }
    }

    double alpha_sum = 0, gamma_sum = 0, alpha_max = 0, gamma_max = 0;
    for (auto &e : entries) {
        alpha_sum += e.alpha_cpm;
        gamma_sum += e.gamma_cpm;
        if (e.alpha_cpm > alpha_max) alpha_max = e.alpha_cpm;
        if (e.gamma_cpm > gamma_max) gamma_max = e.gamma_cpm;
    }

    std::cout << "Alpha ortalama CPM: " << alpha_sum / entries.size() << std::endl;
    std::cout << "Gamma ortalama CPM: " << gamma_sum / entries.size() << std::endl;
    std::cout << "Alpha max CPM: " << alpha_max << std::endl;
    std::cout << "Gamma max CPM: " << gamma_max << std::endl;

    return 0;
}
