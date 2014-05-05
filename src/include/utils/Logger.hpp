#ifndef LOGGER_HPP
#define LOGGER_HPP
#include "../common.hpp"
#include "../NbodySystem.hpp"

class Logger {
    public:
        Logger(NbodySystem *ns);
        ~Logger();

        NbodySystem *ns;

        std::ofstream out_file;
        std::ostream *gstream;
        bool print_screen;
        std::string ofname;

        std::string get_timestamp();
        void print_info();
        void print_all(double ITIME);
        void print_energy_log(double ITIME, int iterations, long long interactions,
                              int nsteps, double new_energy);
        void print_lagrange_radii(double ITIME, std::vector<double> lagrange_radii);
};

#endif // LOGGER_HPP
