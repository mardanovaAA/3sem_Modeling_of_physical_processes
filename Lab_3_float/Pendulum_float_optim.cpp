#include <iostream>
#include <fstream>
#include <vector>

class Solution_1{
private:
    float d_t;
    float  phi_0;
    float  v_0;
    float  omega;
    std::vector<float> data_phi;
    std::vector<float> data_vel;
    std::vector<float> data_time;

public:
    Solution_1(float t, float phi, float v, float omega): d_t(t), phi_0(phi), v_0(v), omega(omega){};

    void SOL(float t_min, float t_max) {
        float current_time = t_min;
        float current_phi = phi_0;
        float current_vel = v_0;
        float prev_time = t_min;
        float prev_phi = phi_0;
        float prev_vel = v_0;
        int counter = 0;
        while (current_time <= t_max){
                if (counter % 10000 == 0){
                    data_phi.push_back(current_phi);
                    data_vel.push_back(current_vel);
                    data_time.push_back(current_time);
                }
                current_vel = prev_vel+ (- omega * omega * prev_phi * d_t);
                current_phi = prev_phi+ prev_vel * d_t;
                current_time += d_t;
                prev_phi = current_phi;
                prev_vel = current_vel;
                prev_time = current_time;
                counter++;
        }
    }

    std::vector<float> information_phi(){
        return data_phi;
    }

    std::vector<float> information_vel(){
        return data_vel;
    }

    std::vector<float> information_time(){
        return data_time;
    }

    std::vector<float> information_energy(){
        std::vector <float> energy;
        float energy_0 = data_phi[0] * data_phi[0] * omega * omega/2 + data_vel[0]*data_vel[0] / 2;
        for (int i = 0; i < data_phi.size(); i++){
            float energy_val = data_phi[i] * data_phi[i] * omega * omega/2 + data_vel[i]*data_vel[i] / 2;
            energy.push_back((energy_val - energy_0)/energy_0);
        }
        return energy;
    }
};

class Solution_2{
private:
    float d_t;
    float  phi_0;
    float  v_0;
    float  omega;
    float compensation_phi = 0.f;
    float compensation_vel = 0.f;
    float compensation_time = 0.f;
    float compensation_energy = 0.f;
    std::vector<float> data_phi;
    std::vector<float> data_vel;
    std::vector<float> data_time;

    float kahan_summation(float tmp1, float tmp2, float &compensation){
        float sum = 0.f;
        tmp1 = tmp1 - compensation;
        tmp2 = sum + tmp1;
        compensation = (tmp2 - sum) - tmp1;
        sum = tmp2;

        return sum;
    }

public:
    Solution_2(float t, float phi, float v, float omega): d_t(t), phi_0(phi), v_0(v), omega(omega){};

    void SOL(float t_min, float t_max) {
        float current_time = t_min;
        float current_phi = phi_0;
        float current_vel = v_0;
        float prev_time = t_min;
        float prev_phi = phi_0;
        float prev_vel = v_0;
        int counter = 0;
        while (current_time <= t_max){
                if (counter % 10000 == 0){
                    data_phi.push_back(current_phi);
                    data_vel.push_back(current_vel);
                    data_time.push_back(current_time);
                }
                current_vel = kahan_summation(prev_vel, - omega * omega * prev_phi * d_t, compensation_vel);
                current_phi = kahan_summation(prev_phi, prev_vel * d_t, compensation_phi);
                current_time = kahan_summation(current_time, d_t, compensation_time);
                prev_phi = current_phi;
                prev_vel = current_vel;
                prev_time = current_time;
                counter++;
        }
    }

    std::vector<float> information_phi(){
        return data_phi;
    }

    std::vector<float> information_vel(){
        return data_vel;
    }

    std::vector<float> information_time(){
        return data_time;
    }

    std::vector<float> information_energy(){
        float energy;
        float energy_0 = data_phi[0] * data_phi[0] * omega * omega/2 + data_vel[0]*data_vel[0] / 2;
        std::vector<float> energy_const;
        for (int i = 0; i < data_phi.size(); i++){
            energy = data_phi[i] * data_phi[i] * omega * omega/2 + data_vel[i]*data_vel[i] / 2;
            energy_const.push_back((energy - energy_0) / energy_0);
        }
        return energy_const;
    }
};

int main(){
    float w = 1;
    float dt = 0.0000001;
    float phi = 0;
    float vel = 0.5;

    Solution_1 sol_1(dt, phi, vel, w);
    sol_1.SOL(0, 2);
    std::vector<float> data_phi = sol_1.information_phi();
    std::vector<float> data_vel = sol_1.information_vel();
    std::vector<float> data_time = sol_1.information_time();
    std::vector<float> data_energy = sol_1.information_energy();
    std::ofstream out_file; //output
    out_file.open("./data_first_sol.txt");
    for (int i = 0; i < data_phi.size(); i++){
        if (i % 1 == 0) {
            out_file << data_time[i] << " " << data_phi[i] << " " << data_vel[i] << " " <<  data_energy[i] << "\n";
        }
    }
    out_file.close();

    data_phi.clear();
    data_time.clear();
    data_vel.clear();
    data_energy.clear();


    Solution_2 sol_2(dt, phi, vel, w);
    sol_2.SOL(0, 2);
    data_phi = sol_2.information_phi();
    data_vel = sol_2.information_vel();
    data_time = sol_2.information_time();
    data_energy = sol_2.information_energy();

    out_file.open("./data_second_sol.txt");
    for (int i = 0; i < data_phi.size(); i++){
        if (i % 1 == 0) {
            out_file<< data_time[i] << " " << data_phi[i] << " " << data_vel[i] << " " << data_energy[i] << "\n";
        }
    }
    out_file.close();



    return 0;
}





