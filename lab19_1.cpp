#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string f,vector<string> &n,vector<int> &s,vector<char> &g){
    string t;
    char format [] = "%[^:]: %d %d %d";
    ifstream source;
	source.open(f) ;

    char names[100];
    int scores1, scores2, scores3;
    while (getline(source, t)){
        const char *cStr = t.c_str();
        sscanf(cStr, format, names, &scores1, &scores2, &scores3);
        n.push_back(string(names));
        s.push_back(int(scores1+scores2+scores3));
        g.push_back(score2grade(int(scores1+scores2+scores3)));
    }
}

void getCommand(string &c,string &k){
    string text;
    char command[100], key[100];
    char format [] = "%s %[^\n]";
    cout << "Please input your command: ";
    getline(cin,text);
    const char * sctext = text.c_str();
    sscanf(sctext, format, command, key);
    c = command;
    k = key;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int count = 0;
    cout << "---------------------------------" << endl;
    for(int i = 0; i  < int(names.size()) ; i++){
        if (toUpperStr(names.at(i)).compare(toUpperStr(key)) == 0) 
        cout << names.at(i) << "'s score = " << scores.at(i) << "\n" <<  
        names.at(i) << "'s grade = " << grades.at(i) << endl;
        else count++;
    }
    if(count == 26) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------" << endl;
    for(int i = 0; i  < int(names.size()) ; i++)
        if (grades.at(i) == (key[0])) cout << names.at(i) << " (" << scores.at(i) << ")" << endl;
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}


