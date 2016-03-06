// ****************************************************************************************
                    //HEADER FILES USED IN THE PROGRAM
// *****************************************************************************************

#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>

// ****************************************************************************************

// *****************************************************************************************

using namespace std;

// ****************************************************************************************
                    //CLASSES USED IN THE PROGRAM
// *****************************************************************************************

class account
{
    char username[50];
    char acc_type;
    float acc_amt;
    int acc_no;

    public:

        // ****************************************************************************************
                            //MEMBER FUNCTION DECLERATIONS
        // *****************************************************************************************

        void createAccount();    // FUNCTION TO CREATE A NEW ACCOUNT
        void depositAmt(float);       // FUNCTION TO DEPOSIT AN AMONT TO MONEY IN THE USER'S ACCOUNT
        void withdrawAmt(float);     //FUNCTION TO WITHDRAW AN AMOUNT
        void accountEnquery();  //FUNCTION TO DISPLAY COMPLETE INFORMATION OF THE USER'S ACCOUNT
        void change();   //FUNCTION TO MODIFY THE CONTENTS OF A USER'S ACCOUNT

        char* returnUsername() {return username;} //A FUNCTION TO RETURN THE NAME OF THE CUSTOMER
        float returnAmt() {return acc_amt;} //FUNCTION TO RETURN THE AMOUNT PRESENT IN THE ACCOUNT
        int returnAccno() {return acc_no;}  //FUNCTION TO RETURN THE ACCOUNT NUMBER
        char returnAcctype(){return acc_type;} //FUNCTION TO RETURN THE TYPE OF ACCOUNT OF THE USER
                                              //EITHER SAVINGS OR FIXED
};

// ****************************************************************************************
                        //MEMBER FUNCTION DEFINATIONS
// *****************************************************************************************

void account::createAccount()   //BEGIN FUNCTION createAccout()
{
    cout<<"enter your name "; cin>>username;
    cout<<"enter the account number ";cin>>acc_no;
    cout<<"\n\nFixed account minimun Rs.5000 "<<endl
        <<"Savings account minimum Rs. 1000 "<<endl;

    cout<<"\nenter the account type(S for Saving and F for fixed) "; cin>>acc_type;
    aa:     //LINE LABEL
        cout<<"enter the amount to be deposited "; cin>>acc_amt;

        acc_type=toupper(acc_type);
        if(acc_type=='S'&&acc_amt<1000)
            {
                    cout<<"invalid entry "<<endl;
                    goto aa;
            }

        if(acc_type=='F'&&acc_amt<5000)
            {
                    cout<<"invalid entry "<<endl;
                    goto aa;
            }

                            // END FUNCTION createAccount()
}

void account::withdrawAmt(float num) //BEGIN FUNCTION withdrawAmt()
{
    acc_amt=acc_amt-num;
}

void account::accountEnquery() //BEGIN FUNCTION acountEnquery()
{
    cout<<"Name: "<<username<<endl
        <<"Account no.: "<<acc_no<<endl
        <<"Account type: "<<acc_type<<endl
        <<"Account amount: Rs."<<acc_amt<<endl;
}                              //END FUNCION accountEnquery()

void account::depositAmt(float num)
{
    acc_amt=acc_amt+num;
}

void account::change()
{
   cout<<"enter the account number ";cin>>acc_no;
    cout<<"enter new name "; cin>>username;
    cout<<"\n\nFixed account minimun Rs.5000 "<<endl
        <<"Savings account minimum Rs. 1000 "<<endl;

    cout<<"\nenter the new account type(S for Saving and F for fixed)\n "; cin>>acc_type;
    aa:     //LINE LABEL
        cout<<"enter the amount to be deposited "; cin>>acc_amt;

        acc_type=toupper(acc_type);
        if(acc_type=='S'&&acc_amt<1000)
            {
                    cout<<"invalid entry "<<endl;
                    goto aa;
            }

        if(acc_type=='F'&&acc_amt<5000)
            {
                    cout<<"invalid entry "<<endl;
                    goto aa;
            }

}

// ****************************************************************************************
                        //END MEMBER FUNCTION DEFINATIONS
// *****************************************************************************************


// ****************************************************************************************
            //FUCTIONS RELATED TO FILE(FUNCTION DECLERATIONS)
// *****************************************************************************************

void write_account();   //A FUNCTION TO WRITE USER ACCOUNT INFORMATION TO A FILE
void display_records(); //A FUNCTION TO DISPLAY THE RECORDS OF A SPECFIC USER
void modify_account();  // A FUNCTION TO MODIFY THE RECORDS OF A SPECIFIC USER
void delete_account();  // A FUNCTION TO DELETE THE RECORDS OF THE USER
void withdraw_amount(); //A FUNCTION TO WITHDRAW AN AMOUNT FROM THE USER'S ACCOUNT
void deposit_amount();  //A FUNCTION TO DEPOSIT AN AMOUNT INTO THE USER'S ACCOUNT

void display_all_records(); //AN ADMIN LEVEL FUNCTION THAT CAN BE USED
                           //TO DISPLAY ALL THE RECORDS OF ALL THE USERS
void total_cash();         //AN ADMIN LEVEL FUNCTION THAT SHOWS THE TOTAL
                           // AMOUNT OF CASH THAT HAS BEEN COLLECTED
// ****************************************************************************************
            //END FUNCTIONS RELATED TO FILES
// ****************************************************************************************

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// ****************************************************************************************
            //FUCTIONS TO CALL USER AND ADMIN ACCOUNTS
// *****************************************************************************************
void startMenu();    // A FUNCTION THAT CALLS THE START MENU OF THE PROGRAM
void user();        // A FUNCTION THAT CALLS THE USER ACCOUNT
void admin();       // A FUNCTION THAT CALLS THE ADMINSTRATOR ACCOUNT

// ****************************************************************************************
            //END FUMCTION DECLERATIONS
// *****************************************************************************************

// ****************************************************************************************
            //FUNCTIONS RELATED TO DESIGN
// *****************************************************************************************
void decorate(int);    // A FUNCTION THAT PRINTS A SERIES OF ASTERIEKS(*) AS REQUIRED
void bank_box();    // A FUNCTION THAT DISPLAYS THE NAME OF THE BANK'S NAME

// ****************************************************************************************
            //FUNCTIONS RELATED TO DESIGN
// *****************************************************************************************

void write_account()
{
    fstream file;
    account ac;
    file.open("try1.txt",ios::out|ios::app|ios::binary); //OPENS A FILE NAMED "try1.txt" IN WRITE AND AND APPEND MODE


    ac.createAccount();         //CALLS THE createAccount OF THE CLASS account
    file.write((char*)&ac,sizeof(ac));
    file.close();
}

void deposit_amount()
{
    account ac;
    fstream file;
    ofstream outf;
    float tempamt;
    int tempaccno,found=0;

    cout<<"enter the account number "; cin>>tempaccno;
    file.open("try1.txt",ios::binary|ios::in|ios::out);
    outf.open("deposit.txt",ios::binary);
    while(file.read((char*)&ac, sizeof(ac))&&found==0)
          {
              if(ac.returnAccno()==tempaccno)
                {
                    ac.accountEnquery();
                    cout<<"\n\n\n";

                    cout<<"TO DEPOSIT AMOUNT\n\n";
                    cout<<"enter the amount to be deposited "; cin>>tempamt;
                    outf<<tempamt;
                    outf<<ac.returnUsername();
                    ac.depositAmt(tempamt);

                    cout<<"\n\n\n AFTER DEPOSIT\n\n";
                    ac.accountEnquery();
                    found=1;
                }

          }
          file.close();
}
void withdraw_amount()
{
    account ac;
    fstream file;
    float tempamt,balance;
    int found=0;

    file.open("try1.txt",ios::out|ios::in|ios::app|ios::binary);
    if(!file)
        cout<<"the file cannot be opened... "<<endl;

    while(file.read((char*)&ac,sizeof(ac)))
    {
        cout<<"enter the amount to be withdrawn "; cin>>tempamt;
        balance=ac.returnAmt()-tempamt;
        if((balance<500&&ac.returnAccno()=='S')||balance<1000&&ac.returnAccno()=='F')
        {
            cout<<"Insufficient balance...\n";
        }
        else
            ac.withdrawAmt(tempamt);

        int pos=(-1)* sizeof(ac);
        file.seekp(pos,ios::cur);
        file.write((char *) &ac, sizeof(account));
        cout<<"\n\n\t Record Updated.... The amount has been withdrawn\n";
        found=1;

}
    file.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

void modify_account()
{
    int found=0,tempaccno;
	account ac;
	fstream file;
    file.open("try1.txt",ios::binary|ios::in|ios::out);
	if(!file)
	{
		cout<<"file could not be open !! Press any Key...";
	}
    cout<<"enter the account number "; cin>>tempaccno;
    while(file.read((char *)&ac, sizeof(ac)) && found==0)
	{
		if(ac.returnAccno()==tempaccno)
		{
			ac.accountEnquery();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.change();
			int pos=(-1)*sizeof(ac);
			file.seekp(pos,ios::cur);
		    file.write((char *) &ac, sizeof(ac));
		    cout<<"\n\n\t Record Updated\n";
		    found=1;
		  }
	}
	file.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

void display_records()
{
    int tempaccno;
    account ac;
    int flag=0;

    fstream file;
    file.open("try1.txt",ios::in|ios::binary);
    if(!file)
    {
        cout<<"the file could not be opened "<<endl;
    }
    cout<<"enter the account number "; cin>>tempaccno;
    cout<<"balance details "<<endl<<endl;
    while(file.read((char*)&ac,sizeof(ac)))
    {
        if(tempaccno==ac.returnAccno())
        {
            ac.accountEnquery();
            flag=1;
        }
    }
    file.close();
    if(flag==0)
        cout<<"Record not found....."<<endl;

}

void display_all_records()
{
    fstream file;
    account ac;

    file.open("try1.txt",ios::in|ios::binary);
    system("cls");

  while(file.read((char*)&ac,sizeof(ac)))
    {
        ac.accountEnquery();
        cout<<"********\n";
    }

     file.close();

}

void delete_account()
{
    account ac;
	ifstream inf;
	ofstream outf;
	int tempaccno;

	inf.open("try1.txt",ios::binary);
	if(!inf)
	{
		cout<<"File could not be open !! Press any Key...\n";
	}

	cout<<"enter the account number to be deleted \n"; cin>>tempaccno;
	outf.open("Temp.txt",ios::binary);
	inf.seekg(0,ios::beg);
	while(inf.read((char*)&ac,sizeof(ac)))
	{
		if(ac.returnAccno()!=tempaccno)
		{
			outf.write((char *) &ac, sizeof(ac));
		}
	}
    inf.close();
	outf.close();
	remove("try1.txt");
	rename("Temp.txt","try1.txt");
	cout<<"\n\n\tRecord Deleted ..";
}

void total_cash()
{
    ifstream inf;
    account ac;
    float sum=0,amount;
    inf.open("deposit.txt",ios::binary);
    inf.seekg(0,ios::beg);
    while(inf)
    {
        inf>>amount;
        sum=sum+amount;
        inf>>ac.returnUsername();
    }
    char name[50];
    strcpy(name,ac.returnUsername());
    cout<<"the total cash deposited is "<<sum<<endl;
    cout<<"the name is "<<name<<endl;
}

void startMenu()
{
    char ch;
    do
    {
        system("cls");
        cout<<"\n\t****************MENU*************************\n\n";
        cout<<"\t1. USER \n\n"
            <<"\t2. ADMIN \n\n";

        cout<<"enter your choice "; cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1':
                user();
                break;

            case '2':
                admin();
                break;

            case '3':
                exit(0);
                break;

            default:
                cout<<"invalid choice \n";
                cout<<"\a";
        }


    }while(ch!='4');
}

void user()
{
    char ch;
    do
    {

        system("cls");
        cout<<"\n\n\n\t****************MENU*************************\n\n\n";
        cout<<"\t1. Create Account \n\n"
        <<"\t2. Display Records \n\n"
        <<"\t3. Deposit Amount \n\n"
        <<"\t4. Withdraw Amount \n\n"
        <<"\t5. Modify Account \n\n"
        <<"\t6. Delete Account \n\n"
        <<"\t7. Exit \n\n"
        <<"\t8. Go back to main menu\n\n";

        cout<<"enter your choice "; cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1':
                system("cls");
                write_account();
                break;

            case '2':

                system("cls");
                display_records();
                break;

            case '3':
                system("cls");
                deposit_amount();
                break;

            case '4':
                system("cls");
                withdraw_amount();
                break;

            case '5':
                system("cls");
                modify_account();
                break;

            case '6':
                system("cls");
                delete_account();
                break;

            case '7':
                exit(0);
                break;

            case '8':
                system("cls");
                startMenu();
                break;

            default:
                cout<<"invalid choice \n"<<'\a';
        }
        system("pause");

    }while(ch!='8');



    }


void admin()
{
    char ch,choice;
    char password[8];
    int inc=0, counter=0;

    cout<<"you have three chances to enter the password...\n"
        <<"the password must be 8 characters long \n";

        do
        {
            while(inc!=8)
            {
                ch=getch();
                if(ch!=13)
                {
                    cout<<"*";
                    password[inc]=ch;
                    inc++;
                }

                else
                    break;
            }
            password[inc]='\0';

            if(strcmpi("password",password)==0)
            {
                cout<<"\n\nTHE PASSWORD IS CORRECT... ACCESS GRANTED....\n\n";
                system("pause");
                system("cls");
                do
                {
                    system("cls");
                    cout<<"\n\n\t****************MENU*************************\n\n\n";
                    cout<<"\t1. Display all accounts \n\n"
                        <<"\t2. Total Cash Deposited \n\n"
                        <<"\t3. Go back to main menu\n\n"
                        <<"\t4. Exit\n\n";

                    cout<<"enter your choice "; cin>>choice;
                    switch(choice)
                    {
                        case '1':
                        display_all_records();
                        system("pause");
                        break;

                    case '2':
                        total_cash();
                        system("pause");
                        break;

                    case '3':
                      system("cls");
                        startMenu();
                        break;

                    case '4':
                        exit(0);
                        break;

                    default:
                        cout<<"invalid choice \n";
                        cout<<"\a";
                    }

                }while(ch!='4');
        break;
     }
     else
            {
                counter=counter+1;
                cout<<"\npassword incorrect... \n ";
                cout<<"you have "<<3-counter<<" chances\n";
                inc=0;
                strcpy(password," ");
            }

        }while(counter!=3);

}

void decorate(int n)
    {
        for(int i=1;i<=n;i++)
            cout<<"*";
        cout<<endl;
    }

    void bank_box()
    {
        cout<<"\t\t";
        decorate(33);
        cout<<"\n\t\t*\t\t\t\t*"<<endl;

        cout<<"\n\t\t*\tPRABMK BANK SERVICE\t*"<<endl;
        cout<<"\n\t\t*\t\t\t\t*\n\n";

        cout<<"\t\t";
        decorate(33);
    }

int main()
{

    bank_box();
    cout<<setw(46)<<"\n\nWELCOME TO PRABKM BANK\n\n "<<endl;
    system("pause");
    startMenu();

}
