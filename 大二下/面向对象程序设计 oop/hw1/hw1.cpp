/*
 * @Descripttion: oop hw1
 * @Author: 庄毅非
 * @Date: 2022-02-28 07:54:01
 */
#include<iostream>
#include<vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::string;

class Student{
public:
    Student() = default;
    Student(string name ,int score1,int score2,int score3) : name(name), score1(score1), score2(score2), score3(score3){
        calAverage();
    }
    void calAverage(){
        this -> average = 1.0 * (score1 + score2 + score3) / 3;
    }
    string &getName() {return this -> name;}
    int getScore1() const {return this -> score1;}
    int getScore2() const {return this -> score2;}
    int getScore3() const {return this -> score3;}
    float getAverage() const { return this -> average;}
private:
    string name;
    int score1;
    int score2;
    int score3;
    float average;
};
const int studentNums = 10;
std::vector<int> minScores{100,100,100};
std::vector<int> maxScores{-1,-1,-1};
std::vector<float> totalScore{0,0,0};
std::vector<Student> students;


int main(){
    // freopen( "data.in" , "r" ,stdin);
    string name;
    int score1,score2,score3;
    for(int i = 0;i<studentNums;i++){
        cout<<"enter name and scores of Student:" << std::endl;
        cin>>name>>score1>>score2>>score3;
        students.push_back(Student(name,score1,score2,score3));
    }
    cout<<"no\tname\tscore1\tscore2\tscore3\taverage"<<std::endl;
    int count = 0;
    std::for_each(students.begin(),students.end(),[&](Student &s) -> void {
        cout<< ++count << "\t" << s.getName() << "\t" << s.getScore1() <<
            "\t" << s.getScore2() << "\t" << s.getScore3() << "\t" << s.getAverage() << std::endl;
    });
    // 遍历students数组，获取最高分，最低分，并计算课程总分（用来计算平均分）
    std::for_each(students.begin(),students.end(),[&](Student s) -> void {
        score1 = s.getScore1(),score2 = s.getScore2(),score3 = s.getScore3();
        minScores[0] = minScores[0] < score1 ? minScores[0] : score1,
        minScores[1] = minScores[1] < score2 ? minScores[1] : score2,
        minScores[2] = minScores[2] < score3 ? minScores[2] : score3;

        maxScores[0] = maxScores[0] > score1 ? maxScores[0] : score1,
        maxScores[1] = maxScores[1] > score2 ? maxScores[1] : score2,
        maxScores[2] = maxScores[2] > score3 ? maxScores[2] : score3;

        totalScore[0] += score1;
        totalScore[1] += score2;
        totalScore[2] += score3;
    });
    //输出结果
    cout<<" \taverage\t"<< totalScore[0] /studentNums << "\t" << totalScore[1] / studentNums << "\t" << totalScore[2] / studentNums<<std::endl ;
    cout<<" \tmin\t"<< minScores[0] << "\t" << minScores[1]  << "\t" << minScores[2]<<std::endl;
    cout<<" \tmax\t"<< maxScores[0] << "\t" << maxScores[1]  << "\t" << maxScores[2]<<std::endl;
    return 0;
}