//
// Created by ACTECH on 9/27/2020.
//
#include <bits/stdc++.h>
#ifndef SPLIT_WISE_SPLITWISE_H
#define SPLIT_WISE_SPLITWISE_H

using namespace std;

class Splitwise {
private:
    int totalUsers;
    map<string, int> userCode;
    map<int, string> userName;
    vector<vector<float>> expenseTable;
    bool isTransacted;
public:
    explicit Splitwise(vector<string> users){
        totalUsers = users.size();
        expenseTable.resize(totalUsers,vector<float>(totalUsers,0));
        for(int i=0;i<users.size();i++) {
            userCode[users[i]] = i;
            userName[i] = users[i];
        }
        isTransacted= false;
    }

    void expenseEqual(string &lender, vector<string> &bearers, float totalAmount){
        isTransacted = true;
        int totBearers=bearers.size();
        float amount = totalAmount/(float)totBearers;
        for(const auto & bearer : bearers){
//            cout<<"Updating for "<<lender<<" "<<userCode[lender]<<" and bearer "<<bearer <<" "<<userCode[bearer]<<endl;
            expenseTable[userCode[lender]][userCode[bearer]]+=amount;
            expenseTable[userCode[bearer]][userCode[lender]]-=amount;
        }
    }
    void expenseExact(string &lender, vector<string> &bearers, vector<float> &amounts){
        isTransacted = true;
        for(int i=0;i<bearers.size();i++){
            expenseTable[userCode[lender]][userCode[bearers[i]]]+=amounts[i];
            expenseTable[userCode[bearers[i]]][userCode[lender]]-=amounts[i];
        }
    }
    void expensePercentage(string &lender, vector<string> &bearers, float totalAmount, vector<float> &percentages){
        isTransacted = true;
        for(int i=0;i<bearers.size();i++){
            expenseTable[userCode[lender]][userCode[bearers[i]]]+=totalAmount*(percentages[i]/100.0);
            expenseTable[userCode[bearers[i]]][userCode[lender]]-=totalAmount*(percentages[i]/100.0);
        }
    }
    bool isTransactioned(){
        return isTransacted;
    }

    void printDebt(int i, int j){
        cout<<userName[i]<<" owes "<<userName[j]<<": "<<abs(expenseTable[i][j])<<endl;
    }
    void showAll(){
        cout<<"Showing all debts\n";
        for(int i=0;i<totalUsers;i++){
            for(int j=0;j<totalUsers;j++){
                if(i==j) continue;
                if(expenseTable[i][j] < 0)
                    printDebt(i,j);
            }
        }
    }

    void showSingle(string &user){
        cout<<"showing single debt\n";
        int uid=userCode[user];
        for(int j=0;j<totalUsers;j++) {
            if(uid==j || expenseTable[uid][j]==0)
                continue;
            if (expenseTable[uid][j] < 0)
                printDebt(uid, j);
            else
                printDebt(j, uid);
        }
    }
};


#endif //SPLIT_WISE_SPLITWISE_H
