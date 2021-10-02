#include <iostream>
#include <vector>
#include <array>
#include <set> //based on binary_tree
#include <unordered_set> //based on hash tables
#include <algorithm>
#include <cmath>
#include <fstream> //for files
#include <string>

//create class Point with private float x,y;

float pow_f(float a, int degree){
    float res = a;
    for (int i = 0; i < degree -1; ++i){
        res *= res;
    }
    return res;
}

class Point{
private:
    float coord_x;
    float coord_y;

public:
    Point(float x, float y){
        coord_x = x;
        coord_y = y;
    };

    Point(): Point(0, 0){
    };

    void print(){
        std::cout << "(" << coord_x << ", " << coord_y << ")" << std::endl;
    }

    float get_x(){
        return coord_x;
    }

    float get_y(){
        return coord_y;
    }

    float distance(Point b) const{
        return std::sqrt(pow_f((coord_x - b.get_x()), 2) + pow_f((coord_y - b.get_y()), 2));
    }
};

float distance_by_points (const std::vector <Point> &vec){
    float res = 0;
    for (int i = 0; i < vec.size() - 1; i++){
        res += vec[i].distance(vec[i+1]);
    }
    return res;
}

float move_by_points(const std::vector <Point> &vec){
    return vec.front().distance(vec.back());
}

int main(){
    std::ofstream out_file; //output
    out_file.open("./out.txt");
    out_file << "Hello world!" << std::endl;
    out_file.close(); //it is unnecessary;

    std::ifstream in_file;
    in_file.open("./out.txt");
    std::string s;
    //in_file >> s;
    std::getline(in_file, s);
    in_file.close();
    std::cout << s;
    return 0;
}
