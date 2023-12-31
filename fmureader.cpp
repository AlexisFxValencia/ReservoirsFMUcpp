#include "fmureader.h"

FMUReader::FMUReader()
{

}

void FMUReader::init_reader(double time_step){
    fmu_filename = "";
    fmu_path = "Reservoirs_valve.fmu";
    start_time = 0.0;
    current_time = start_time;
    this->time_step = time_step; //seconds
    acceleration = 1;

    tank_height = 1; // il faudra lire la hauteur du tank
    tolerance = 0.05 * tank_height;

    valve_opening = 1.0; // il faudra la déterminer automatiquement par rapport au modèle
}

void FMUReader::init_model_description()
{
    auto cs_fmu = fmi2::fmu(fmu_path).as_cs_fmu();
    cs_md = cs_fmu->get_model_description(); //smart pointer to a cs_model_description instance
    cout << "model_identifier = " << cs_md->model_identifier << endl;
    cout << endl;

    cout << "Starting Simulation..." << endl;
    slave = cs_fmu->new_instance();
    slave->setup_experiment();
    slave->enter_initialization_mode();
    slave->exit_initialization_mode();

    auto valve_opening = cs_md->get_variable_by_name("u").as_real();
    vr_valve_opening = valve_opening.valueReference();
    slave->write_real(vr_valve_opening, 1);

}

bool FMUReader::level_in_container(double tank_level){
    if (tank_level < 0.0 || tank_level > tank_height){
        return false;
    }else{
        return true;
    }
}

void FMUReader::take_a_step() //in secs
{
    slave->step(acceleration * time_step);
    current_time += time_step;
}

double FMUReader::read(string variable_name){
    auto variable = cs_md->get_variable_by_name(variable_name).as_real();
    int vr = variable.valueReference();
    double value;
    slave->read_real(vr, value);
    return value;
}

void FMUReader::open_valve(){
    valve_opening = 1.0;
    slave->write_real(vr_valve_opening, valve_opening);

}

void FMUReader::close_valve(){
    valve_opening = 0.0;
    slave->write_real(vr_valve_opening, valve_opening);
}

void FMUReader::change_valve_opening(float value){
    valve_opening = value;
    slave->write_real(vr_valve_opening, valve_opening);
}
