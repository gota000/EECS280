// stats.cpp
#include "stats.hpp"
#include <cassert>
// #include <iostream>
#include <vector>
#include <algorithm> // sort
#include <cmath> // sqrt, modf

using namespace std;

int count(vector<double> v) {
    return v.size();
}

double sum(vector<double> v) {
    double total = 0.0f;
    for (auto val : v){
        total = total + val;
    }
    return total;
}

double mean(vector<double> v) {
    return sum(v) / static_cast<double>(count(v));
}

double median(vector<double> v) {
    sort(v.begin(), v.end());
    int middle = v.size()/2;
    if (v.size() % 2 == 0) {
        return (v.at(middle) + v.at(middle - 1)) / 2;
    } else {
        return v.at(middle);
    }
}

double min(vector<double> v) {
    double min_value = 1000000.0f;
    for (auto val : v){
        if (val < min_value){
            min_value = val;
        }
    }
    // cout << min_value << endl;
    return min_value;
}

double max(vector<double> v) {
    double max_value = -1000000.0f;
    for (auto val : v){
        if (val > max_value){
            max_value = val;
        }
    }
    return max_value;
}

double stdev(vector<double> v) {
    double summation = 0.0f;
    double mean_value = mean(v);
    for (int i = 0; i < v.size(); i++){
        summation = summation + pow(v.at(i) - mean_value, 2);
    }
    double standard_deviation = sqrt((1.0f / (v.size() - 1.0f)) * summation);
    return standard_deviation;
}

double percentile(vector<double> v, double p) {
    sort(v.begin(), v.end());
    
    if (v.size() == 1) {
        return v.at(0);
    }

    if (p == 0.0f) {
        return v.at(0);
    } 
    if (p == 1.0f) {
        return v.at(v.size()- 1);
    } 

    double rank = p * (v.size() - 1) + 1;
    double intrank = 0;
    double fracrank = 0;
    fracrank = modf(rank, &intrank);
    return v.at(intrank - 1) + fracrank * (v.at(intrank) - v.at(intrank - 1));
}

vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target) {
    vector<double> filtered_list; 
    for (int i = 0; i < criteria.size(); i++){
        if (criteria.at(i) == target){
            filtered_list.push_back(v.at(i));
        }
    }
    return filtered_list;
}
