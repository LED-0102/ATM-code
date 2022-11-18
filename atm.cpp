#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
#include<algorithm>
#include<climits>
using namespace std;

class bank {
    public:
    int ind;
    void create_acc(){
        long long int acc_num;
        lab1:
        cout<<"Enter a 10 digit account number"<<endl;
        cin>>acc_num;
        if (acc_num<=999999999 || acc_num>9999999999){
            cout<<"Invalid input"<<endl;
            goto lab1;
        }
        string z = to_string(acc_num);
        ifstream in("accnum.txt");
        string st[10];
        for (int i=0; i<10; i++){
            in>>st[i];
        }
        in.close();
        for (int i=0; i<10; i++){
            if (z == st[i].substr(0, 10)){
                cout<<"This account number already exists. Login instead??"<<endl;
                goto lab1;
            }
        }
        string password;
        cout<<"Enter your password"<<endl;
        cin>>password;

        string com;
        com = z + password;
        ofstream out("accnum.txt", ios_base::app);
            out<<com<<"\n";
        out.close();
        cout<<"Account created successfully"<<endl;
    }
    void login(){
        long long int acc_num;
        string password;
        
        int index;
        lab2:
        cout<<"Enter your 10 digit account number"<<endl;
        cin>>acc_num;
        string z = to_string(acc_num);

        ifstream in("accnum.txt");
        string st[10];
        for (int i=0; i<10; i++){
            in>>st[i];
        }
        in.close();
        for (int i=0; i<10; i++){
            if (z == st[i].substr(0, 10)){
                index = i;
                goto lab3;
            }
        }
        cout<<"This account number does not exist. Press 1 to sign up."<<endl;
        goto lab2;
        lab3:
        cout<<"Enter your Password ";
        cin>>password;
        string pass = st[index].substr(10, st[index].length());
        if (pass == password){
            cout<<"User Verified"<<endl;
            ind = index;
        }
        else{
            cout<<"Wrong password. Please try again"<<endl;
            goto lab3;
        }
    }
    void account(){
        float balance[10];
        ifstream in("balance.txt", ios_base::app);
        for (int i=0; i<10; i++){
            in>>balance[i];
        }
        
        in.close();
        cout<<"Your current balance is "<<(balance[ind]-1)<<endl;
        int sw;
        menu:
        cout<<"Press 1 to deposit\nPress 2 to withdraw\nPress 3 to transfer\nPress 4 to delete your account.\nPress 5 to exit\n";
        cin>>sw;
        switch (sw){
            case 1:{
                float depmon;
                cout<<"Enter the money you want to deposit ";
                cin>>depmon;
                balance[ind] = balance[ind] + depmon;
                ofstream out("balance.txt");
                for (int i=0; i<10; i++){
                    out<<balance[i]<<endl;
                }
                out.close();
                cout<<"Your current balance is "<<(balance[ind]-1)<<endl;
                goto menu;
            }
            case 2:{
                float withmon;
                labnoob:
                cout<<"Enter the money you want to withdraw ";
                cin>>withmon;
                if (withmon>(balance[ind]-1)){
                    cout<<"Stay within your limits";
                    goto labnoob;
                }
                balance[ind]-=withmon;
                ofstream out("balance.txt");
                for (int i=0; i<10; i++){
                    out<<balance[i]<<endl;
                }
                out.close();
                cout<<"Your current balance is "<<(balance[ind]-1)<<endl;
                goto menu;
            }
            case 3:{
                int ind1;
                float trans;
                long long int reciever;
                labnoob1:
                cout<<"Enter the money you want to withdraw ";
                cin>>trans;
                if (trans>(balance[ind]-1)){
                    cout<<"Stay within your limits"<<endl;
                    goto labnoob1;
                }
                laba:
                cout<<"Enter the account number you want to transfer to ";
                cin>>reciever;
                string z = to_string(reciever);
                ifstream in("accnum.txt");
                string st[10];
                for (int i=0; i<10; i++){
                    in>>st[i];
                }
                in.close();
                for (int i=0; i<10; i++){
                    if (z == st[i].substr(0, 10)){
                        ind1 = i;
                        goto labn;
                    }
                }
                cout<<"This account number does not exist. Try again"<<endl;
                goto laba;
                labn:
                balance[ind]-=trans;
                balance[ind1]+=trans;
                ofstream out("balance.txt");
                for (int i=0; i<10; i++){
                    out<<balance[i]<<endl;
                }
                out.close();
                cout<<"Your current balance is "<<(balance[ind]-1)<<endl;
                goto menu;
            }
            case 4:{
                ifstream in("accnum.txt");
                string st[10];
                for (int i=0; i<10; i++){
                    in>>st[i];
                }
                for (int i=ind; i<9; i++){
                    st[i] = st[i+1];
                }
                in.close();
                ofstream out("accnum.txt");
                for (int i=0; i<10; i++){
                    out<<st[i]<<endl;
                }
                out.close();

                ifstream ina("balance.txt");
                string stbal[10];
                for (int i=0; i<10; i++){
                    ina>>stbal[i];
                }
                for (int i=ind; i<9; i++){
                    stbal[i] = stbal[i+1];
                }
                ina.close();
                ofstream outa("balance.txt");
                for (int i=0; i<10; i++){
                    outa<<stbal[i]<<endl;
                }
                outa.close();
                cout<<"Account deleted succesfully. Goodbye!"<<endl;
            }
            case 5:{
                break;
            }
        }
    }
};

int main()
{
    bank b;
    cout<<"Welcome!";
    int beg;
    cout<<"Press 1 to create an account\nPress 2 to login to your account\n";
    cin>>beg;
    switch (beg){
        case 1:
            b.create_acc();
            cout<<"Now please login to your account"<<endl;
            goto lab10;
        case 2:
            lab10:
            b.login();
            b.account();
    }
    return 0;
}
