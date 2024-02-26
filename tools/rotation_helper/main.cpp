#include <string>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>


#include <cxxopts.hpp>
#include <fmt/core.h>

#define CXXOPTS_VECTOR_DELIMITER ','

#include <le3.h>
using namespace le3;

void deg_to_rad(std::vector<double>& v) {
    for (auto& x : v) x = x / 180 * M_PI;
}

void rpy_to_quat(std::vector<double> v) {
    LE3Transform trans; trans.setRotationRPY(v[0], v[1], v[2]);
    glm::quat q = trans.getRotation();
    fmt::print("{}, {}, {}, {}\n", q.w, q.x, q.y, q.z);
}


int main(int argc, char** argv) {
    cxxopts::Options options("LE3 Rotation Helper", "Used to convert different types of rotations");
    options.add_options()
        ("i,typein", "Type of input [quat, rpy]", cxxopts::value<std::string>()->default_value("rpy"))
        ("o,typeout", "Type of output [quat, rpy]", cxxopts::value<std::string>()->default_value("quat"))
        ("vector", "Input values, comma separated (e.g., : --vector=1.57,0.,-1.57)", cxxopts::value<std::vector<double>>())
        ("d,degrees", "Use this flag to use degrees instead of radians.")
        ("h,help", "Show executable help")
    ;
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        fmt::print("{}\n", options.help()); 
        return 0;
    }

    std::string typein = result["typein"].as<std::string>();
    std::string typeout = result["typeout"].as<std::string>();
    std::vector<double> v = result["vector"].as<std::vector<double>>();

    std::string cvt = fmt::format("{}->{}", typein, typeout);

    bool use_deg = result.count("degrees");
    if (use_deg) deg_to_rad(v);

    if (cvt == "rpy->quat") rpy_to_quat(v);
    else if (typein == typeout) fmt::print("Don't be silly\n");
    else fmt::print("Unsupported convertion {}\n", cvt);

    return 0;
}
