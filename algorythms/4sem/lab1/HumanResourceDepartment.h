//
// Created by User on 026 26.02.21.
//

#ifndef ALGO_HUMANRESOURCEDEPARTMENT_H
#define ALGO_HUMANRESOURCEDEPARTMENT_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Subdepartment{    int _id;
    string _name;
      int _found_year;
    vector<int> _workers_id;
    static int free_ID;

public:
    Subdepartment();
    Subdepartment(const string& name);
    Subdepartment(const string& name,const int foundyear);
    Subdepartment(const string& name,const int foundyear, const vector<int>& workers_id);

    string getName();
    void setName(string name);
    void setFY(int fy);
    int getFY();
    static vector<Subdepartment> genSubdepartment(int count);

};

class Worker{
    int _id;
    string _name;
    int _performersId;
    int age;

    static int free_ID;
public:
    Worker();
    Worker(const string& name, int performersId, int countOfSongs);
};



#endif //ALGO_HUMANRESOURCEDEPARTMENT_H
