#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "httplib.h"

std::vector<char> file;

void init() {
    std::ifstream fileStream("static/index.html", std::ios::binary);
    if (!fileStream) {
        std::cerr << "Could not open the file!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    file.assign((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
}

int main() {
    init();

    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content(file.data(), file.size(), "text/html");
    });

    std::cout << "Server started on http://localhost:8080" << std::endl;
    svr.listen("localhost", 8080);

    return 0;
}
