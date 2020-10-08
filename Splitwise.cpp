//
// Created by ACTECH on 9/27/2020.
//

#include "Splitwise.h"
#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<string> users={"u1", "u2", "u3", "u4"};
    string line, user;
    Splitwise billSplitter(users);

    while(getline(cin,line)){
        if(line=="\n" || line.empty())
            break;
        istringstream sline{line};
        vector<string> data{istream_iterator<string>(sline), istream_iterator<string>()};
//        copy(data.begin(), data.end(), ostream_iterator<string>(cout, "--"));

        if(data[0]=="SHOW"){
            if(!billSplitter.isTransactioned()){
                cout<<"No balances\n";
                continue;
            }
            if(data.size()==1)
                billSplitter.showAll();
            else
                billSplitter.showSingle(data[1]);
        }
        else{
            string lender=data[1];
            float loan=stof(data[2]);
            int split=stoi(data[3]);
            vector<string> bearers(split);
            vector<float> amounts(split);

            for(int i=0;i<split;i++)
                bearers[i]=data[4+i];

            string method=data[3+split+1];
            if(method=="EQUAL")
                billSplitter.expenseEqual(lender, bearers, loan);
            else {
                for(int i=0;i<split;i++)
                    amounts[i]=stoi(data[3+split+2+i]);
                if (method == "EXACT")
                    billSplitter.expenseExact(lender, bearers, amounts);
                else {
                    billSplitter.expensePercentage(lender, bearers, loan, amounts);
                }
            }
        }
    }
    return 0;
}