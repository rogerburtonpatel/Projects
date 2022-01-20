#include <unordered_set>
#include <iostream>
#include <functional>

using namespace std; 


struct wordPod {
    string word;
    string filepath;
    size_t index;
    int linenumber; 
    bool operator==(const wordPod& wp) const {
        return (this->word       == wp.word
           and this->filepath    == wp.filepath 
           and this->index       == wp.index
           and this->linenumber  == wp.linenumber);
    }
size_t operator()(const wordPod& wp) const {
        return (std::hash<std::string>() (wp.word)     ^ 
                std::hash<std::string>() (wp.filepath) ^ 
                std::hash<size_t>() (wp.index)         ^ 
                std::hash<int>() (wp.linenumber));}
};



int main() {
    // just a set
    // unordered_set<int> oneset;

    // unordered_set<int> *manysets = new unordered_set<int> [32];

    // Person p {3, "roger"};
    // Person p2 {3, "roger"};
    // Person p3 {3, "rogr"};


    // cout << (p == p2) << endl;

    // unordered_set<Person, Person> personset;

    // personset.insert(p);
    // personset.insert(p2);
    // personset.insert(p3);


    // for (auto per : personset) {
    //     cout << per.age << "\t" << per.name << endl;
    // }


    // unordered_set<Person, Person> *psettable = new unordered_set<Person, Person> [32];

    // psettable[0].insert(p);
    // for (auto per : psettable[0]) {
    //     cout << per.age << "\t \t" << per.name << endl;
    // }

    unordered_set<wordPod, wordPod> wps;

    cout << hash<string>() ("hi") << endl;
    cout << hash<string>() ("Hi") << endl;

    // delete [] manysets; 
    // delete [] psettable; 


}