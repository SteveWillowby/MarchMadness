#include<iostream>
#include<string>
#include<map>
#include<set>

using namespace std;

int main(void) {
    // Updated as of pre-2019
    double odds[2][14] = {{0.525, 0.525, 0.525, 0.525,
        0.613, 0.613, 0.613, 0.613,
        0.635, 0.635,
        0.679, 0.679, 0.679, 0.679},
           {0.475, 0.475, 0.475, 0.475,
               0.387, 0.387, 0.387, 0.387,
               0.365, 0.365,
               0.321, 0.321, 0.321, 0.321}};

    int points[2][14] = {{5,5,5,5,5,5,5,5,5,5,5,5,5,5},
        {6,6,6,6,
            8,8,8,8,
            10,10,
            12,12,12,12}};

    bool pick_better_seed[14] = {1,1,1,1,
        1,1,1,1,
        1,1,
        1,1,1,1};

    bool matches_prediction[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    bool done = false;

    double prob;
    int score;
    map<int, double> probabilities;
    int iterations = 0;
    while(!done) {
        score = 0;
        prob = 1.0;
        for(int i = 0; i < 14; i++) {
            score -= matches_prediction[i]*points[!pick_better_seed[i]][i];
            prob *= odds[matches_prediction[i] != pick_better_seed[i]][i];
        }
        probabilities[score] += prob;
        for(int i = 13; i >= 0; i--) {
            if(matches_prediction[i]) {
                matches_prediction[i] = 0;
                break;
            }
            else {
                matches_prediction[i] = 1;
                if(i == 0) {
                    done = true;
                }
            }
        }
        iterations++;
    }
    double running_sum = 0;
    for(auto i = probabilities.begin(); i != probabilities.end(); i++) {
        running_sum += i->second;
        if(running_sum > 0 && running_sum < 1) {
            cout<<"Score: "<<-1 * i->first<<" Prob: "<<running_sum<<endl;
        }
    }

    return 0;
}
