#include <iostream>
#include <fstream>

/*
Methods to sum with float:
1. Small quantity firstly;
2. Sum parties (bucket methods);
3. Kahan algorithm.
*/

float kahan_summation(std::vector <float> const &number){
    float sum = 0.f;
    float compensation = 0.f;
    float tmp1, tmp2;

    for (unsigned pos = 0; pos != number.size(); ++pos){
        tmp1 = number[pos] - compensation;
        tmp2 = sum + tmp1;
        compensation = (tmp2 - sum) - tmp1;
        sum = tmp2;
    }

    return sum;
}

int main(){
    float sum_direct = 0;
    float sum_indirect = 0;
    float ceil = 10000000;
    std::ofstream out;
    out.open("./data_garmon_sum.txt");
    float i = 1;
    int counter = 0;
    int j = 10000000;
    while (i <= ceil){
        sum_direct += 1.0 / i;
        sum_indirect += 1.0 / float(j);
        if (counter % 10000 == 0){
            out << i << " " << j << " " << sum_direct << " " << sum_indirect << "\n";
        }
        i += 1.0;
        j -= 1.0;
        counter++;
    }
    out.close();
    return 0;
}
