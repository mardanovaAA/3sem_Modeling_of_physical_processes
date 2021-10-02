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
        while (current_time <= t_max){
                data_phi.push_back(current_phi);
                data_vel.push_back(current_vel);
                data_time.push_back(current_time);
                current_vel = data_vel.back() + (- omega * omega * data_phi.back() * d_t);
                current_phi = data_phi.back() + data_vel.back() * d_t;
                current_time += d_t;
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

    float kahan_summation(std::vector <float> const &number, float compensation){
        float sum = 0.f;
        float tmp1, tmp2;

        for (unsigned pos = 0; pos != number.size(); ++pos){
            tmp1 = number[pos] - compensation;
            tmp2 = sum + tmp1;
            compensation = (tmp2 - sum) - tmp1;
            sum = tmp2;
        }

        return sum;
    }

public:
    Solution_2(float t, float phi, float v, float omega): d_t(t), phi_0(phi), v_0(v), omega(omega){};

    void SOL(float t_min, float t_max) {
        float current_time = t_min;
        float current_phi = phi_0;
        float current_vel = v_0;
        while (current_time <= t_max){
                data_phi.push_back(current_phi);
                data_vel.push_back(current_vel);
                data_time.push_back(current_time);
                current_vel = kahan_summation(std::vector<float> {data_vel.back(), - omega * omega * data_phi.back() * d_t}, compensation_vel);
                current_phi = kahan_summation(std::vector<float> {data_phi.back(), data_vel.back() * d_t}, compensation_phi);
                current_time = kahan_summation(std::vector<float> {current_time, d_t}, compensation_time);
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
        float energy_0 = kahan_summation(std::vector<float> {data_phi[0] * data_phi[0] * omega * omega/2, data_vel[0]*data_vel[0] / 2}, 0.f);
        std::vector<float> energy_const;
        for (int i = 0; i < data_phi.size(); i++){
            energy = kahan_summation(std::vector<float> {data_phi[i] * data_phi[i] * omega * omega/2, data_vel[i]*data_vel[i] / 2}, 0.f);
            energy_const.push_back(kahan_summation(std::vector<float> {energy, -energy_0}, 0.f) / energy_0);
        }
        return energy_const;
    }
};

int main(){
    float w = 1;
    float dt = 0.0001;
    float phi = 1;
    float vel = 0;

    Solution_1 sol_1(dt, phi, vel, w);
    sol_1.SOL(0, 10);
    std::vector<float> data_phi = sol_1.information_phi();
    std::vector<float> data_vel = sol_1.information_vel();
    std::vector<float> data_time = sol_1.information_time();
    std::vector<float> data_energy = sol_1.information_energy();
    std::ofstream out_file; //output
    out_file.open("./data_first_sol.txt");
    for (int i = 0; i < data_phi.size(); i++){
        if (i % 1000 == 0) {
            out_file << data_time[i] << " " << data_phi[i] << " " << data_vel[i] << " " <<  data_energy[i] << "\n";
        }
    }
    out_file.close();

    data_phi.clear();
    data_time.clear();
    data_vel.clear();
    data_energy.clear();


    Solution_2 sol_2(dt, phi, vel, w);
    sol_2.SOL(0, 10);
    data_phi = sol_2.information_phi();
    data_vel = sol_2.information_vel();
    data_time = sol_2.information_time();
    data_energy = sol_2.information_energy();

    out_file.open("./data_second_sol.txt");
    for (int i = 0; i < data_phi.size(); i++){
        if (i % 1000 == 0) {
            out_file<< data_time[i] << " " << data_phi[i] << " " << data_vel[i] << " " << data_energy[i] << "\n";
        }
    }
    out_file.close();



    return 0;
}





