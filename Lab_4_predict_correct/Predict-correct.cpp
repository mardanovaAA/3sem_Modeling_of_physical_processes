#include <iostream>
#include <cmath>
#include <fstream>

//Физ.маятник Метод Эйлера и Метод Хойна


int main(){
    double vel_0 = 2;
    double phi_0 = 0;
    double dt = 0.0001;
    double t = 0;
    double omega = 1;
    double t_max = 10;
    int counter = 0;

    double phi_t = phi_0;
    double vel_t = vel_0;
    double phi_h;
    double vel_h;
    double phi_next;
    double vel_next;

    std::ofstream out;
    out.open("./Eiler_sol_2.txt");

    //Eiler

    while (t < t_max){
        if (counter % 100 == 0){
            out << t << " " << phi_t << " " << vel_t << " " << (1-cos(phi_t))*omega*omega + vel_t*vel_t/2 << "\n";
        }
        phi_next = phi_t + vel_t * dt;
        vel_next = vel_t - omega*omega*dt * sin(phi_t);
        t += dt;
        counter++;

        phi_t = phi_next;
        vel_t = vel_next;

    }

    out.close();

    //Khoin
    phi_t = phi_0;
    vel_t = vel_0;
    counter = 0;
    t = 0;
    out.open("./Khoin_sol_2.txt");

    while (t < t_max){
        if (counter % 100 == 0){
            out << t << " " << phi_t << " " << vel_t << " " << (1-cos(phi_t))*omega*omega + vel_t*vel_t/2 << "\n";
        }
        phi_h = phi_t + vel_t * dt;
        vel_h = vel_t - omega*omega * sin(phi_t)* dt;

        phi_next = phi_t + 0.5 * dt * (vel_t + vel_h);
        vel_next = vel_t - 0.5 * omega*omega * dt * (sin(phi_t) + sin(phi_h));
        t += dt;
        counter++;

        phi_t = phi_next;
        vel_t = vel_next;
    }

    out.close();

    return 0;
}
