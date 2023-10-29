#include<bits/stdc++.h>
using namespace std;
vector<string> v;
void generatePar(string &s,int op,int cl){
        if(op == 0 && cl==0){
            v.push_back(s);
            return;
        }
        
        if(op>0){
            s.push_back('(');
            generatePar(s,op-1,cl);
            s.pop_back();
        }
        
        if(cl>0){
            if(op<cl){
                s.push_back(')');
                generatePar(s,op,cl-1);
                s.pop_back();
            }
        }
    }
    
    vector<string> generateParenthesis(int n) {
        string s;
        generatePar(s,n,n);
        return v;
        
        
    }
int main(){
   int n;cin>>n;
   vector<string> ans = generateParenthesis(n);
   for(auto it:ans){
    cout<<it<<endl;
   }

}