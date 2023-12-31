#ifndef FMUREADER_H
#define FMUREADER_H

#include <iostream>
#include <fmi4cpp/fmi4cpp.hpp>

using std::cout, std::endl, std::string;
using namespace fmi4cpp;

class FMUReader
{
public:
    FMUReader();
    string fmu_filename;
    string fmu_path;
    std::shared_ptr<const fmi2::cs_model_description> cs_md;
    std::unique_ptr<fmi2::cs_slave> slave;

    float start_time;
    float current_time;
    double time_step; //seconds
    double acceleration;

    double tank_height;
    double tolerance;

    int vr_valve_opening;
    float valve_opening;

    void init_reader(double time_step);
    void init_model_description();

    bool level_in_container(double tank_level);
    void take_a_step();
    double read(string variable_name);

    void open_valve();
    void close_valve();
    void change_valve_opening(float value);
};

#endif // FMUREADER_H
