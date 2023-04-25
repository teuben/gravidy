/*
 * Copyright (c) 2016
 *
 * Cristián Maureira-Fredes <cmaureirafredes@gmail.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. The name of the author may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP
#include "../common.hpp"
#include "../NbodySystem.hpp"
#include <cctype>

const std::string color_black   = "\033[0;30m";
const std::string color_red     = "\033[0;31m";
const std::string color_green   = "\033[0;32m";
const std::string color_yellow  = "\033[0;33m";
const std::string color_blue    = "\033[0;34m";
const std::string color_purple  = "\033[0;35m";
const std::string color_cyan    = "\033[0;36m";
const std::string color_white   = "\033[0;37m";
const std::string color_disable = "\033[m";

// #define SSTR( x ) static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()
#define SSTR(x)   std::to_string(x)


/**
 * Class in charge of all the logging system in the code.
 * This class includes the methods to be able to report something on-screen
 * and also writing the infor and snapshot files.
 */
class Logger {
    public:
        Logger(NbodySystem *ns);
        ~Logger();

        NbodySystem *ns;

        bool print_screen;
        std::ofstream out_file;
        std::ofstream info_file;
        std::ostream *gstream;
        std::string ofname;
        std::string ofname_info;

        std::string get_timestamp();
        void print_info();
        void add_info(std::string key, std::string value);
        void write_info();
        void write_snapshot(unsigned int snapshot_number, double ITIME);
        void print_all(double ITIME, unsigned int snapshot_number);
        void print_energy_log(double ITIME, unsigned int iterations,
                              long long interactions, unsigned int nsteps,
                              double new_energy);
        void print_lagrange_radii(double ITIME, std::vector<double> lagrange_radii);


        void log(int type,  std::string msg);
        void log_error(std::string msg);
        void log_warning(std::string msg);
        void log_success(std::string msg);
        void log_info(std::string msg);
};

#endif // LOGGER_HPP
