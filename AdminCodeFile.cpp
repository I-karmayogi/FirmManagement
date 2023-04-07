//HEADER FILES
#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<tr1/unordered_map>
#include<stdio.h>
using namespace std;

//CLASS FOR ACCOUNT RECORDS
class account
{
	int ac_no;      //account number
	char name[20];  //name of account holder
	int balance;    //account balance (in Rs)
    int min_bal;    //min balance limit
    int max_bal;    //max balance limit
public:
	void create_account();	    //function to get data from user
	void show_account() const;	//function to show data on screen
	void modify_account();	    //function to add new data
	void deposite(int);	        //function to accept amount and add to balance amount
	void withdraw(int);	        //function to accept amount and subtract from balance amount
	void show() const;	        //function to show data in tabular format
    void show_name() const;
	int get_ac_no() const;	    //function to return account number
	int get_balance() const;	//function to return balance amount
    int get_min_bal() const;    //function to return min balance limit
    int get_max_bal() const;    //function to return max balance limit
    void set_balance(int);      //function to modify balance amount
};

//STRUCTURE FOR TRANSACTION
struct Transaction
{
    int tid;        //transaction ID
    int from;       //from account number
    int to;         //to account number
    int amount;     //amount to be transfered
};
typedef struct Transaction Transaction;

vector<account> Accounts;
std::tr1::unordered_map<int,int> ID;

//function declaration
void write_account();	                            //function to write record for new account
void display_sp(int);	                            //function to display account details given by user
void modify_account(int);	                        //function to modify record of existing account
void delete_account(int);	                        //function to delete record of existing account
void display_all();		                            //function to display all account details
void deposit_withdraw(int, int, int, bool=false);   //function to desposit/withdraw amount for given account 
int ac_exists(int);                                 //function to check if account number already exists

//ACCOUNT FUNCTIONS DEFINATION
void account::create_account(){
    do{
        cout<<"Enter Account No. : ";
	    cin>>ac_no;
        if(ac_exists(ac_no) == -1){ break; }
        cout<<"Account Number Already Exists.\n\n";
    }while(1);

	cout<<"\nEnter Account Holder\'s Name : ";
	cin.ignore();
	cin.getline(name,20);

    cout<<"\nEnter Minimum Balance Limit : ";
	cin>>min_bal;
    min_bal = max(min_bal, 0);
    cout<<"\nEnter Maximum Balance Limit : ";
	cin>>max_bal;
    max_bal = max(max_bal, min_bal);
    do{
        cout<<"\nEnter Initial Deposite Amount : ";
	    cin>>balance;
        if(balance < min_bal){
            cout<<"\nMinimum Balance Limit : "<<min_bal;
        }
        else if(balance > max_bal){
            cout<<"\nMaximum Balance Limit : "<<max_bal;
        }
    }while(balance < min_bal || balance > max_bal);
}

void account::show_account() const
{
	cout<<"\nAccount Number      : "<<ac_no;
	cout<<"\nAccount Holder Name : "<<name;
	cout<<"\nBalance Amount      : Rs "<<balance;
	cout<<"\nMin Balance Limit   : Rs "<<min_bal;
	cout<<"\nMax Balance Limit   : Rs "<<max_bal;
}

void account::modify_account()
{
	cout<<"\nAccount No. : "<<ac_no;
	cout<<"\nModify Account Holder\'s Name : ";
	cin.ignore();
	cin.getline(name,20);
    cout<<"\nModify Min Balance Limit : ";
	cin>>min_bal;
    min_bal = max(min_bal, 0);
    cout<<"Modify Max Balance Limit : ";
	cin>>max_bal;
    max_bal = max(max_bal, min_bal);
    do{
        cout<<"\nModify Balance Amount : ";
	    cin>>balance;
        if(balance < min_bal){
            cout<<"\nMinimum Balance Limit : "<<min_bal;
        }
        else if(balance > max_bal){
            cout<<"\nMaximum Balance Limit : "<<max_bal;
        }
    }while(balance < min_bal || balance > max_bal);
}

	
void account::deposite(int x)
{
	balance+=x;
}
	
void account::withdraw(int x)
{
	balance-=x;
}
	
void account::show() const
{
	cout<<ac_no<<"\t";
    int size = printf("%s", name);
    if(size < 8){ cout<<"\t\t"; }
    else if(size < 16){ cout<<"\t"; }
    cout<<"\t";
    cout<<balance<<endl;
}

void account::show_name() const
{ 
    printf("%s", name);
}
	
int account::get_ac_no() const
{
	return ac_no;
}

int account::get_balance() const
{
	return balance;
}

void account::set_balance(int x)
{
	balance = x;
}

int account::get_min_bal() const
{
	return min_bal;
}

int account::get_max_bal() const
{
	return max_bal;
}

// MENU FUNCTIONS
void intro();               //introductory screen
void show_main_menu();      //main menu
void show_ac_menu();        //accounts menu
void show_cash_menu();      //money withdraw/deposite menu

void intro()
{
	cout<<"\n| BANK";
	cout<<"\n| MANAGEMENT";
	cout<<"\n| SYSTEM";
	cout<<"\n\nMADE BY : Priyanshu Sharma, Raghvan Pareek, Rahil Godha, Swamy Pulaparthi";
	cout<<"\n\nPress enter to continue...";
    cin.get();
}

void show_main_menu(){
	system("cls");
	cout<<"===============================\n";
	cout<<"          MAIN MENU\n";
	cout<<"===============================\n";
	cout<<"\n1. ACCOUNTS";
	cout<<"\n2. ACCOUNT ENQUIRY";
	cout<<"\n3. MONEY TRANSFER";
	cout<<"\n4. MONEY WITHDRAW/DEPOSIT";
	cout<<"\n5. RUN TRANSACTION SCRIPT";
	cout<<"\n0. EXIT";
}

void show_ac_menu(){
	system("cls");
	cout<<"==============================\n";
	cout<<"          ACCOUNTS\n";
	cout<<"==============================\n";
	cout<<"\n1. NEW ACCOUNT";
	cout<<"\n2. MODIFY ACCOUNT";
	cout<<"\n3. CLOSE AN ACCOUNT";
	cout<<"\n4. ACCOUNT ENQUIRY";
	cout<<"\n5. SHOW ALL ACCOUNTS";
	cout<<"\n6. MONEY TRANSFER";
	cout<<"\n7. MONEY WITHDRAW/DEPOSIT";
	cout<<"\n0. RETURN TO MAIN MENU";
}

void show_cash_menu(){
	system("cls");
	cout<<"================================\n";
	cout<<"     MONEY WITHDRAW/DEPOSIT\n";
	cout<<"================================\n";
	cout<<"\n1. DEPOSIT";
	cout<<"\n2. WITHDRAW";
	cout<<"\n0. RETURN TO MAIN MENU";
}

//BACKEND FUNCTIONS
//function to fetch saved data
void get_data();        //function to fetch saved data from file
void save_data();       //function to save data to file

void get_data()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		fstream f;
        f.open("account.dat",ios::out);
        f.close();
        inFile.open("account.dat",ios::binary);
	}
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		Accounts.push_back(ac);
	}
	inFile.close();
}

//function to save data
void save_data()
{
	ofstream outFile;
	outFile.open("Temp.dat",ios::binary);
    int n = Accounts.size();
	for(int i=0; i<n; i++)
	{
        outFile.write(reinterpret_cast<char *> (&Accounts[i]), sizeof(account));
	}
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
}

// MENU DRIVER FUNCTIONS
//money transfer menu driver function
void money_transfer();      //driver function for money transfer
void cash_main();           //driver function for money withdraw/deposite
void accounts_main();       //driver function for accounts
void transcript();          //driver function for transaction script

void money_transfer(){
    int ac1, ac2, amount;
    system("cls");
    cout<<"================================\n";
	cout<<"         MONEY TRANSFER\n";
	cout<<"================================\n";
    cout<<"\n\nFROM ACCOUNT NO. : "; cin>>ac1;
    int id1 = ac_exists(ac1);
    if(id1 == -1){ 
        cout<<"\nAccount does not exist.";
        return;
    }
    Accounts[id1].show_account();
    cout<<"\n\nTO ACCOUNT NO. : "; cin>>ac2;
    int id2 = ac_exists(ac2);
    if(id2 == -1){ 
        cout<<"\nAccount does not exist.";
        return;
    }
    Accounts[id2].show_account();
    cout<<"\n\nENTER AMOUNT  : "; cin>>amount;
    if(Accounts[id1].get_balance() < amount){
        cout<<"\nInsufficient balance.";
        return;
    }
    if((Accounts[id1].get_balance()-amount) < Accounts[id1].get_min_bal()){
        cout<<"\nAccounts Violating Balance Limit. \nTransaction Not Possible.";
        return;
    }
    if((Accounts[id2].get_balance()+amount) > Accounts[id2].get_max_bal()){
        cout<<"\nAccounts Violating Balance Limit. \nTransaction Not Possible.";
        return;
    }
    deposit_withdraw(ac1, amount, 2);
    deposit_withdraw(ac2, amount, 1);
    cout<<"\n\nMoney Transfered Successfully.";
}

//money transfer menu driver function
void cash_main(){
    int ch, num, amount;
    do
    {
        show_cash_menu();
        cout<<"\n\nSELECT AN OPTION (0-2) : ";
        cin>>ch;
        if(ch<=0 || ch>2){ continue; }
        system("cls");
        if(ch == 1){
            cout<<"================================\n";
            cout<<"         MONEY DEPOSIT\n";
            cout<<"================================\n";
        }
        else if(ch == 2){
            cout<<"================================\n";
            cout<<"         MONEY WITHDRAW\n";
            cout<<"================================\n";
        }
        cout<<"\n\nENTER THE ACCOUNT NO. : "; cin>>num;
        int id = ac_exists(num);
        if(id == -1){ 
            cout<<"\nAccount does not exist.";
            continue; 
        }
        Accounts[id].show_account();
        cout<<"\n\nENTER AMOUNT  : "; cin>>amount;
        if(ch==2 && Accounts[id].get_balance() < amount){
            cout<<"\nInsufficient balance.";
            continue;
        }
        if(ch==2 && (Accounts[id].get_balance()-amount) < Accounts[id].get_min_bal()){
            cout<<"\nAccount Violating Min Balance Limit. \nTransaction Not Possible.";
            return;
        }
        if(ch==1 && (Accounts[id].get_balance()+amount) > Accounts[id].get_max_bal()){
            cout<<"\nAccounts Violating Max Balance Limit. \nTransaction Not Possible.";
            return;
        }
        deposit_withdraw(num, amount, ch, true);
    }while(ch<0 || ch>2);
}

//accounts menu driver function
void accounts_main(){
    int ch, num;
    do
    {
        show_ac_menu();
        cout<<"\n\nSELECT AN OPTION (0-7) : ";
        cin>>ch;
        if(ch<0 || ch>7){ continue; }
        system("cls");
        switch(ch){
            case 0:
                return;
            case 1:
                write_account();
                break;
            case 2:
                cout<<"================================\n";
                cout<<"        MODIFY ACCOUNT\n";
                cout<<"================================\n";
                cout<<"\n\nENTER THE ACCOUNT NO. : "; cin>>num;
                modify_account(num);
                break;
            case 3:
                cout<<"================================\n";
                cout<<"        DELETE ACCOUNT\n";
                cout<<"================================\n";
                cout<<"\n\nENTER THE ACCOUNT NO. : "; cin>>num;
                delete_account(num);
                break;
            case 4:
                cout<<"================================\n";
                cout<<"        ACCOUNT DETAILS\n";
                cout<<"================================\n";
                cout<<"\n\nENTER THE ACCOUNT NO. : "; cin>>num;
                display_sp(num);
                break;
            case 5:
                display_all();
                break;
            case 6:
                money_transfer();
                break;
            case 7: 
                cash_main();
                break;
        }
        cout<<"\n\nPress enter to continue...";
        cin.ignore();
        cin.get();
    }while(ch!=0);
}

//Helper Functions for Transcript
vector<account> acc;
vector<vector<int> > safe_seq;

//function to remove dublicate safe sequences
void remove_dublicates(vector<vector<int> > &safe_seq){
    int size = safe_seq.size();
    int num = safe_seq[0].size();
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            int k;
            for(k=0; k<num; k++){
                if(safe_seq[i][k] != safe_seq[j][k]){ break; }
            }
            if(k == num){
                safe_seq.erase(safe_seq.begin()+j);
                size--;
                j--;
            }
        }
    }
}

//function to update account balance
void update_ac_bal(int ac_no, int bal){
    int n = Accounts.size();
    for(int i=0; i<n; i++){
        if(Accounts[i].get_ac_no() == ac_no){
            Accounts[i].set_balance(bal);
            Accounts[i].show();
            break;
        }
    }
}

//function for deadlock detection and prevention
void bankers_algo(vector<Transaction> &tran){
    int size = tran.size();
    vector<int> seq(size);
    for(int i=0; i<size; i++){ seq[i] = i; }

    do
    {
        vector<account> temp_acc = acc;
        vector<Transaction> temp_tran;
        for(int i=0; i<size; i++){
            temp_tran.push_back(tran[seq[i]]);
        }

        int temp_size = temp_tran.size();
        vector<int> ss;
        while(temp_size){
            bool waiting = true;
            for(int i=0; i<temp_size; i++){
                if((temp_acc[ID[temp_tran[i].from]].get_balance()-temp_tran[i].amount) < temp_acc[ID[temp_tran[i].from]].get_min_bal()){
                    continue;
                }
                if((temp_acc[ID[temp_tran[i].to]].get_balance()+temp_tran[i].amount) > temp_acc[ID[temp_tran[i].to]].get_max_bal()){
                    continue;
                }
                
                waiting = false;
                temp_acc[ID[temp_tran[i].from]].withdraw(temp_tran[i].amount);
                temp_acc[ID[temp_tran[i].to]].deposite(temp_tran[i].amount);
                ss.push_back(temp_tran[i].tid);
                temp_tran.erase(temp_tran.begin()+i);
                temp_size--;
                i--;
            }
            if(waiting){ break; }
        }
        if(temp_size == 0){
            safe_seq.push_back(ss);
        }
    }while(next_permutation(seq.begin(), seq.end()));
}

//function to check if transactions are possible or not
bool tran_is_possible(vector<Transaction> &tran){
    vector<account> temp_acc = acc;
    vector<Transaction> temp_tran = tran;

    int size = temp_tran.size();

    for(int i=0; i<size; i++){
        temp_acc[ID[temp_tran[i].from]].withdraw(temp_tran[i].amount);
        temp_acc[ID[temp_tran[i].to]].deposite(temp_tran[i].amount);
    }

    bool is_possible = true;
    int x = 1;
    size = acc.size();
    for(int i=0; i<size; i++){
        if(temp_acc[i].get_balance() < temp_acc[i].get_min_bal()){
            if(is_possible){
                cout<<"\n\nTRANSACTIONS NOT POSSIBLE BECAUSE OF FOLLOWING ISSUE(S) :";
                cout<<"\n---------------------------------------------------------\n";
                is_possible = false;
            }
            int diff = temp_acc[i].get_min_bal()-temp_acc[i].get_balance();

            cout<<x++<<".)\tACC NO : "<<temp_acc[i].get_ac_no()<<" (";
            temp_acc[i].show_name();
            cout<<")\n";

            cout<<"\tISSUE : Insufficient Balance OR Minimum Balance Limit Violated.\n";
            cout<<"\tSOLUTION : Add Rs "<<diff<<" to account.\n";
            if(acc[i].get_balance() + diff > acc[i].get_max_bal()){
                cout<<"\t           Set Maximum Balance Limit to at least Rs "<<(acc[i].get_balance() + diff)<<".\n";
            }
            cout<<endl;
        }
        else if(temp_acc[i].get_balance() > temp_acc[i].get_max_bal()){
            if(is_possible){
                cout<<"\n\nTRANSACTIONS NOT POSSIBLE BECAUSE OF FOLLOWING ISSUE(S) :";
                cout<<"\n---------------------------------------------------------\n";
                is_possible = false;
            }
            cout<<x++<<".)\tACC NO : "<<temp_acc[i].get_ac_no()<<" (";
            temp_acc[i].show_name();
            cout<<")\n";

            cout<<"\tISSUE : Maximum Balance Limit Violated.\n";
            cout<<"\tSOLUTION : Set Maximum Balance Limit to at least Rs "<<temp_acc[i].get_balance()<<".\n";
            cout<<endl;
        }
    }

    return is_possible;
}

//transcript menu driver function
void transcript(){
    system("cls");
    ID.clear();
    acc.clear();

    cout<<"================================\n";
    cout<<"      TRANSACTION SCRIPT\n";
    cout<<"================================\n";
    int num;
    cout<<"\nENTER NUMBER OF TRANSACTIONS TO RUN : ";
    cin>>num;
    vector<Transaction> tran(num);
    for(int i=0; i<num; i++){
        int ac1, ac2, amount;
        cout<<"\nTRANSACTION "<<i+1<<" :\n";
        cout<<"----------------\n";
        tran[i].tid = i+1;
        cout<<"FROM AC NO. : "; cin>>ac1;
        int id1 = ac_exists(ac1);
        if(id1 == -1){
            cout<<"\nAccount does not exist.";
            return;
        }
        if(ID.count(ac1) == 0){
            ID[ac1] = acc.size();
            acc.push_back(Accounts[id1]);
        }
        cout<<"TO AC NO.   : "; cin>>ac2;
        int id2 = ac_exists(ac2);
        if(id2 == -1){ 
            cout<<"\nAccount does not exist.";
            return;
        }
        if(ID.count(ac2) == 0){
            ID[ac2] = acc.size();
            acc.push_back(Accounts[id2]);
        }
        cout<<"AMOUNT      : "; cin>>amount;
        tran[i].from = ac1;
        tran[i].to = ac2;
        tran[i].amount = amount;
    }

    if(!tran_is_possible(tran)){ return; }

    bankers_algo(tran);

    if(safe_seq.size() == 0){
        cout<<"\n\nTRANSACTIONS NOT POSSIBLE BECAUSE OF DEADLOCK.";
    }
    else{
        remove_dublicates(safe_seq);
        cout<<"\n\nSAFE SEQUENCE(S) : \n";
        cout<<"------------------ \n";
        int size = safe_seq.size();
        for(int i=0; i<size; i++){
            cout<<i+1<<".) ";
            for(int j=0; j<num; j++){
                cout<<"T"<<safe_seq[i][j]<<" ";
            }
            cout<<endl;
        }
        for(int j=0; j<num; j++){
            int id = safe_seq[0][j];
            acc[ID[tran[id-1].from]].withdraw(tran[id-1].amount);
            acc[ID[tran[id-1].to]].deposite(tran[id-1].amount);
        }

        cout<<"\n\nUPDATED ACCOUNTS :\n\n";
        cout<<"====================================================\n";
        cout<<"A/c no.\tNAME\t\t\tBalance\n";
        cout<<"====================================================\n";
        size = acc.size();
        for(int i=0; i<size; i++){
            update_ac_bal(acc[i].get_ac_no(), acc[i].get_balance());
        }
        
        cout<<"\nMoney Transfered Successfully.";
    }
}

//MAIN FUNCTION
int main()
{
    get_data();
	int ch, num;
	system("cls");
	intro();
	do
	{
		show_main_menu();
		cout<<"\n\nSELECT AN OPTION (0-5) : ";
		cin>>ch;
		if(ch<0 || ch>5){ continue; }

		system("cls");
		switch(ch)
		{
            case 0:
                break;
            case 1:
                accounts_main();
                break;
            case 2:
                cout<<"================================\n";
                cout<<"        ACCOUNT DETAILS\n";
                cout<<"================================\n";
                cout<<"\n\nENTER THE ACCOUNT NO. : "; cin>>num;
                display_sp(num);
                break;
            case 3:
                money_transfer();
                break;
            case 4: 
                cash_main();
                break;
            case 5:
                transcript();
                break;
            case 6:
                break;
		}
        cout<<"\n\nPress enter to continue...";
		cin.ignore();
        cin.get();
    }while(ch!=0);
	system("cls");
    save_data();
	return 0;
}


//FUNCTION DEFINATIONS
void write_account()
{
    cout<<"================================\n";
	cout<<"           NEW ACCOUNT\n";
	cout<<"================================\n";
	account ac;
	ac.create_account();
	Accounts.push_back(ac);
    cout<<"\n\nAccount Created Successfully.";
}

void display_sp(int num)
{
    int i, n = Accounts.size();
    for(i=0; i<n; i++){
        if(Accounts[i].get_ac_no()==num)
		{
			Accounts[i].show_account();
			break;
		}
    }
	if(i == n)
		cout<<"\n\nAccount number does not exist";
}

void modify_account(int num)
{
    int i, n = Accounts.size();
    for(i=0; i<n; i++){
        if(Accounts[i].get_ac_no()==num)
		{
			Accounts[i].show_account();
            cout<<"\n\nENTER NEW DETAILS :"<<endl;
			Accounts[i].modify_account();
            cout<<"\n\nAccount Updated.";
			break;
		}
    }
	if(i == n)
		cout<<"\n\nAccount number does not exist";
}

void delete_account(int num)
{
    int i, n = Accounts.size();
    for(i=0; i<n; i++){
        if(Accounts[i].get_ac_no()==num)
		{
			Accounts.erase(Accounts.begin()+i);
            cout<<"\n\n\tRecord Deleted ..";
			break;
		}
    }
    if(i == n)
		cout<<"\n\nAccount number does not exist";
}


void display_all()
{
	cout<<"\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.\tNAME\t\t\tBalance\n";
	cout<<"====================================================\n";
    int i, n = Accounts.size();
    for(i=0; i<n; i++){
		Accounts[i].show();
    }
}

void deposit_withdraw(int num, int amount, int option, bool out)
{
    int i, n = Accounts.size();
    for(i=0; i<n; i++){
        if(Accounts[i].get_ac_no()==num)
		{
			if(option==1)
			{
				Accounts[i].deposite(amount);
                if(out)
                cout<<"\n\nMoney Deposited Successfully.";
			}
		    else if(option==2)
			{
                if(Accounts[i].get_balance() >= amount){
                    Accounts[i].withdraw(amount);
                    if(out)
                    cout<<"\n\nMoney Withdrawn Successfully.";
                }
		    }
			break;
		}
    }
}

int ac_exists(int num){
    int i, n = Accounts.size();
    for(int i=0; i<n; i++){
        if(Accounts[i].get_ac_no() == num){
            return i;
        }
    }
    return -1;
}

//END OF PROJECT
