#include <iostream>
#include "include/Point_2.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <utility>
#include <iomanip>
#include <vector>
#include <list>
#include <functional>

#include <filesystem>  
// requires flag -std=c++17 for g++ 9.4.
//
// alternatively, if this C++17 feature is not 
// yet available, we can use Boost.Filesystem
// #include <boost/filesystem.hpp>   
// includes what we need. We then have to 
// replace std::filesystem by 
// boost::filesystem . C'est ca.

#include "include/Boost_based_timer.h"
#include "NRA.hpp"


typedef AE::Point_2<double>   Point_2;
typedef AE::Less_2<double>    Less_2;
typedef AE::Timer             Timer;

int n;
std::string str;

template <class Less>
void
report_and_reset(Timer& uhr, Less& less, std::string algo, int iterations)
{
    double factor = 131072.0 / iterations;
    std::cout << algo << ";";
    std::cout << str << ";";
    std::cout << n << ";";
    std::cout << std::fixed << std::setprecision(2) << uhr.time() * factor << ";";
    std::cout << std::endl;
    uhr.reset();
}


int
main(int argc, char** argv)
{


    // std::cout << "input data files directory is: " <<argv[1]<< "\n";

    std::string dir_path = argv[1];
    if (!std::filesystem::exists(dir_path)) {
        std::cout << "Directory not found!";
        return EXIT_FAILURE;
    }
    std::filesystem::directory_iterator end_itr;
    for (std::filesystem::directory_iterator itr(dir_path); itr != end_itr; ++itr)
    {
        if (is_regular_file(itr->status()))
        {

            Timer  uhr;

            std::vector<Point_2>  P;
            std::vector<Point_2>  S;

            int N;
            std::ifstream F(itr->path().string());
            str = itr->path().filename().string();

            F >> n;
            double x, y;
            for (int i = 1; i <= n; ++i)
            {
                F >> x; F >> y;
                P.push_back(Point_2(x, y));
            }
            F.close();
            std::copy(P.begin(), P.end(), std::back_inserter(S));

            Less_2  xy_less;
            int correction = std::log2(n);
            N = (2 * 16777216 >> correction);

            via_std_sort(P.begin(), P.end(), S.begin(), xy_less);

            uhr.start();
            for (int i = 0; i < N; ++i)
                NRA::sort(P.begin(), P.end(), S.begin(), xy_less);
            uhr.stop();
            report_and_reset(uhr, xy_less, "NRA", N);
        }
    }

    return EXIT_SUCCESS;
}

