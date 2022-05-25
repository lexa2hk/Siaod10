#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<int> prefix(string s){
    vector<int> p(s.size());
    p[0] = 0;
    int k = 0;
    for(int i = 1; i < s.size(); i++){
        while(k > 0 && s[i] != s[k]) k = p[k-1];
        if(s[i] == s[k]) k++;
        p[i] = k;
    }
    return p;
}

int kmp(string s, string t){
    vector<int> f = prefix(s);
    int i = 0, j = 0;
    while(i < s.size() && j < t.size()){
        if(s[i] == t[j]){
            i++;
            j++;
        }
        else if(j > 0) j = f[j-1];
        else i++;
    }
    if(j == t.size()) return i-j;
    return -1;
}

//check string with regex
bool isValidIpV4(string s){
    const regex r("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    return regex_match(s, r);
}

int main() {

    //=========================CHECK CYCLES=========================
    ifstream fin_check("../input.txt");
    string s;
    string cycleTemplate[3] = {"while", "for", "do"};
    if(!fin_check.is_open()){
        cout << "File not found!" << endl;
        return 0;
    }
    fin_check.close();
    for(int i = 0; i < 3; i++){
        ifstream fin("../input.txt");

        int pos = -1;
        int max_i = -1;
        while(!fin.eof()){
            fin>>s;
            pos = kmp(s, cycleTemplate[i]);
            max_i = max(max_i, pos);
        }
        if(max_i != -1) cout << "Found  - " << cycleTemplate[i] <<endl;
        else cout << "Not found - " << cycleTemplate[i] << endl;
        fin.close();
    }
    //=========================CHECK IP=========================
    cout<<isValidIpV4("192.168.1.1")<<endl;
}
