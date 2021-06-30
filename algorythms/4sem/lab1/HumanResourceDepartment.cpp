//
// Created by User on 026 26.02.21.
//
#include "HumanResourceDepartment.h"

int Subdepartment::free_ID = 0;
int Worker::free_ID = 0;

string departmentnames[] = {"General",
                            "Marketing",
                            "Operationrthfdfg",
                            "Finance",
                            "Sales",
                            "HumanResource",
                            "Purchase",
                            "Tourism ",
                            "Anthropology",
                            "CELT","Health","Happiness"
                                      ,"chebureki"
                                      ,"smokingkills"
                                      ,"pivolechit",
                                      "daytedeneg",
                                      "askskaksa",
                                      "dsadsa",
                                      "dsartt"
                                      , "kopec"

};

Subdepartment::Subdepartment() {
    _id = free_ID++;
    _name = "";

    _workers_id.clear();
}
Subdepartment::Subdepartment(const string& name) {
    _id = free_ID++;
    _name = name;

}
Subdepartment::Subdepartment(const string& name,const int foundyear) {
    _id = free_ID++;
    _name = name;
    _found_year=foundyear;

}
Subdepartment::Subdepartment(const string& name,const int foundyear,  const vector<int>& workers_id) {
    _id = free_ID++;
    _name = name;
_found_year=foundyear;
    for (auto i : workers_id)
        _workers_id.push_back(i);
}

string Subdepartment::getName() {
    return _name;
}

void Subdepartment::setName(string name){
    _name = name;
}
void Subdepartment::setFY(int fy){
    _found_year=fy;
};
int Subdepartment::getFY(){
    return _found_year;
};
vector<Subdepartment> Subdepartment::genSubdepartment(int count) {
    int id, foundyear;
    string name;
    vector<Subdepartment> result;
    for (int i = 0; i < count; i++){
        foundyear=rand()%50+1900;
        name = departmentnames[i];
        Subdepartment newPerformer(name,foundyear);
        result.push_back(newPerformer);
    }
    return result;
}

Worker::Worker() {
    _id = free_ID++;
    _name = "";
    age = -1;
    _performersId = -1;

}
Worker::Worker(const string &name, int performersId, int countOfSongs) {
    _id = free_ID++;
    _name = name;
    _performersId = performersId;
    age = countOfSongs;

}
