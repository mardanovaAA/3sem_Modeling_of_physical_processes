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
};

class Solution_2{
private:
    float d_t;
    float phi_0;
    float v_0;
    float omega;
    std::vector<float> data_phi;
    std::vector<float> data_vel;
    std::vector<float> data_time;

public:
    Solution_2(float t, float phi, float v, float omega): d_t(t), phi_0(phi), v_0(v), omega(omega){};

    void SOL(float t_min, float t_max) {
        float current_time = t_min;
        float current_phi = phi_0;
        float current_vel = v_0;
        data_phi.push_back(current_phi);
        data_vel.push_back(current_vel);
        data_time.push_back(current_time);
        while (current_time <= t_max){
                current_phi = data_vel.back() * d_t/2 + data_phi.back(); //phi(dt/2)
                current_vel = -omega*omega * current_phi*d_t + data_vel.back(); //vel(t)
                current_phi = current_phi + data_vel.back()* d_t/2; //phi(t)
                data_phi.push_back(current_phi);
                data_vel.push_back(current_vel);
                current_time += d_t;
                data_time.push_back(current_time);
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
};

int main(){
    float w = 1;
    float dt = 0.0001;
    float phi = 1.5;
    float vel = 0;

    Solution_1 sol_1(dt, phi, vel, w);
    sol_1.SOL(0, 10);
    std::vector<float> data_phi = sol_1.information_phi();
    std::vector<float> data_vel = sol_1.information_vel();
    std::vector<float> data_time = sol_1.information_time();
    std::ofstream out_file; //output
    out_file.open("./data_first_sol.txt");
    for (int i = 0; i < data_phi.size(); i++){
        float energy = data_phi[i] * data_phi[i] * w * w/2 + data_vel[i]*data_vel[i] / 2;
        out_file << data_time[i] << " " << data_phi[i] << " " << data_vel[i] << " " <<  energy << std::endl;
    }
    out_file.close();

    data_phi.clear();
    data_time.clear();
    data_vel.clear();


    Solution_2 sol_2(dt, phi, vel, w);
    sol_2.SOL(0, 10);
    data_phi = sol_2.information_phi();
    data_vel = sol_2.information_vel();
    data_time = sol_2.information_time();
    //std::ofstream out_file; //output
    out_file.open("./data_second_sol.txt");
    for (int i = 0; i < data_phi.size(); i++){
        float energy = data_phi[i] * data_phi[i] * w * w/2 + data_vel[i]*data_vel[i] / 2;
        out_file<< data_time[i] << " " << data_phi[i] << " " << data_vel[i] << " " << energy << std::endl;
    }
    out_file.close();


    return 0;
}

