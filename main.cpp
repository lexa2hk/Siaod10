#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>

using namespace std;

void generate_file() {
    const string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-+";
    ofstream file("../input.txt");
    for (int i = 0; i < 1000000; i++) {
        file << valid[rand()%valid.size()];
    }
    file.close();
}

void printvector(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}


vector<int> prefix(string s){
    vector<int> p(s.size());

    p[0] = 0;
    int k = 0;
    for(int i = 1; i < s.size(); i++){
        while(k > 0 && s[i] != s[k]){
            k = p[k-1];
        }
        if(s[i] == s[k]) k++;
        p[i] = k;
    }
    return p;
}




int kmp2(string p, string t){
    int pl = p.size();
    int tl = t.size();
    vector<int> pr = prefix(p+"#"+t);
    for(int i = pl+1; i < tl+pl+1; i++){
        if(pr[i] == pl){
            return i-2*pl;
        }
    }

    return -1;
}
//check string with regex
void generate_ip_file(){
    ofstream file("../ip_input.txt");
    for(int i = 0; i < 1000; i++){
        string temp = "";
        vector<int> v(4);
        for(int j = 0; j < 4; j++){
            temp+= to_string(rand()%300)+".";
        }
        file << temp.substr(0,temp.size()-1) << endl;
    }
    file.close();
}
bool isValidIpV4(string s){
    const regex r("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    return regex_match(s, r);
}

int main() {
    srand(time(NULL));
    //=========================CHECK CYCLES=========================
    ifstream fin_check("../input.txt");
    string s;
    string cycleTemplate[3] = {"while", "for", "do"};
    if(!fin_check.is_open()){
        cout << "File not found!" << endl;
        return 0;
    }
    fin_check.close();
    /*for(int i = 0; i < 3; i++){
        ifstream fin("../input.txt");

        int pos = -1;
        int max_i = -1;
        while(!fin.eof()){
            fin>>s;
            //pos = kmp2(cycleTemplate[i],s);
            pos=0;
            max_i = max(max_i, pos);
        }
        if(max_i != -1) cout << "Found  - " << cycleTemplate[i] <<endl;
        else cout << "Not found - " << cycleTemplate[i] <<endl;
        fin.close();
    }*/
//    generate_file();
//    return 0;
    for(int i=100;i<=1000000;i*=10){
        ifstream fin("../input.txt");
        const string substr = "for";
        string s;
        fin>>s;
        s = s.substr(0,i);
        //s.insert(i/2,substr);
        int index;
        auto start = chrono::high_resolution_clock::now();
        index  = kmp2(substr,s);
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish-start);
        cout<<"i: "<<i<<" position: "<<index<<" time: "<<duration.count()<<" mks"<<endl;
        fin.close();
    }

    //=========================CHECK IP=========================
    cout<<isValidIpV4("192.168.1.1")<<endl;
    generate_ip_file();
    ifstream fin("../ip_input.txt");
    string st;
    if(!fin.is_open()){
        cout << "File not found!" << endl;
        return 0;
    }
    int suscess = 0;
    int fail = 0;
    while(!fin.eof()){
        fin>>st;
        bool state = isValidIpV4(st);
        cout << st << " " << state<< endl;
        if(state) suscess++;
        else fail++;
    }
    cout << "Success: " << suscess << endl;
    cout << "Fail: " << fail << endl;
}
