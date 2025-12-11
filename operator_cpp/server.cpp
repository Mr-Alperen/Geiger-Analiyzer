#include <httplib.h>
#include <iostream>
#include <fstream>
#include <ctime>

std::string now() {
    time_t t = time(NULL);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return buf;
}

int main() {
    httplib::Server svr;

    svr.Post("/geiger", [&](const httplib::Request& req, httplib::Response& res) {
        std::ofstream log("log/geiger_log.txt", std::ios::app);
        log << now() << " | " << req.body << "\n";

        std::cout << "Data received: " << req.body << std::endl;

        res.set_content("OK", "text/plain");
    });

    std::cout << "Server started on :8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
}
