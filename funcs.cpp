//https://contest.yandex.ru/contest/27665/problems/G/

#include "funcs.h"
#include <bits/stdc++.h>

class Bank{
    //! @brief name - deposit
    std::map<const std::string, long long int> clients;
public:
    void deposit(const std::string & name, long long int sum){
        clients[name] += sum;
    }
    void income(long long int procent){
        double scale = (100.+procent)/100.;
        for(auto & client : clients){
            if(client.second > 0)
                client.second = (long long int)(client.second*scale);
        }
    }
    void transfer(const std::string & from,
                  const std::string & to,
                  long long int sum){
        deposit(from,-sum);
        deposit(to,sum);
    }
    void withdraw(const std::string & name, long long int sum){
        deposit(name,-sum);
    }
    std::string balance(const std::string & name){
        if(clients.count(name)){
            return std::to_string(clients[name]);
        } else {
            return "ERROR";
        }
    }
};

void parseFile(std::istream & input, std::ostream & output){

    Bank bank;
    std::string command, name1, name2;
    long long int sum;
    while (input >> command){
        if(command == "DEPOSIT"){
            input >> name1 >> sum;
            bank.deposit(name1,sum);
        } else if(command == "INCOME"){
            input >> sum;
            bank.income(sum);
        } else if(command == "WITHDRAW"){
            input >> name1 >> sum;
            bank.withdraw(name1, sum);
        } else if(command == "TRANSFER"){
            input >> name1 >> name2 >> sum;
            bank.transfer(name1,name2,sum);
        } else if(command == "BALANCE"){
            input >> name1;
            output << bank.balance(name1)<<'\n';
        }
    }
}
