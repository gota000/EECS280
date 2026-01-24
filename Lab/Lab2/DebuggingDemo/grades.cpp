#include <iostream>
#include <vector>

void analyzeGrades(const std::vector<int>& grades) {
    int maxScore = 0;
    int totalScore = 0;

    for (size_t i = 0; i <= grades.size(); ++i) {
		// using .at() here to check for out of bounds
        totalScore += grades.at(i); 

        if (grades.at(i) > maxScore) {
            maxScore = grades.at(i);
        }
    }

    double average = static_cast<double>(totalScore) / grades.size(); 

    std::cout << "--- Class Stats ---" << std::endl;
    std::cout << "Total Points: " << totalScore << std::endl;
    std::cout << "Highest Score: " << maxScore << std::endl;
    std::cout << "Average Score: " << average << std::endl;
}

int main() {
    std::vector<int> studentGrades = {85, 92, 78, 90, 88};

    analyzeGrades(studentGrades);

    return 0;
}