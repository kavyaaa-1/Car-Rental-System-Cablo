#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


using namespace std;

class customer
{

    string username;
    string firstname;
    string lastname;
    string phone;
    string password;
    vector<string> row;
public:
    void displayInfo()
    {
        cout << "\n\t PERSONAL DETAILS \n";
        cout << "\t Username: \t" << username << "\n";
        cout << "\t First Name: \t" << firstname << "\n";
        cout << "\t Last Name: \t" << lastname << "\n";
        cout << "\t Phone Number: \t" << phone << "\n";

        return;
    }

    void getInputReg()
    {
        cout << "\tEnter Username: ";
        cin >> username;

        cout << "\tEnter First Name: ";
        cin >> firstname;

        cout << "\tEnter Last Name: ";
        cin >> lastname;

        cout << "\tEnter Phone: ";
        cin >> phone;

        cout << "\tEnter Password: ";
        cin >> password;

        return;
    }

    void register_()
    {
        ofstream file("cablo.csv", ios :: app);

        getInputReg();
        file << username << "," << password << "," << firstname << "," << lastname << "," << phone << endl;
        file.close();

        cout << "\n\tYou have successfully registered! \n\n\n";
        system("PAUSE");

        return;
    }

    void getInputLogin()
    {
        cout << "\tEnter Username: ";
        cin >> username;

        cout << "\tEnter Password: ";
        cin >> password;

        return;
    }

    int login()
    {
        ifstream readfile("cablo.csv", ios :: in);
        getInputLogin();


        string line, word;
        int flag = 0;

        while(!readfile.eof())
        {
            row.clear();
            getline(readfile, line);
            stringstream s(line);

            while(getline(s, word, ','))
            {
                row.push_back(word);
            }

            if(row[0] == username && row[1] == password)
            {
                flag = 1;
                cout << "\n\tYou have Logged In successfully !\n\n";
                system("PAUSE");

                username = row[0];
                password = row[1];
                firstname = row[2];
                lastname = row[3];
                phone = row[4];
                break;
            }
        }

        if(flag == 0)
        {
            cout << "\n\tIncorrect username or password !! Try again \n\n";
            return 0;
        }
        return 1;
    }


};


class cars
{


    string location;
    int days;
    vector<string> c_row;
    int rent;

public:
    void carsDisplayInfo()
    {
        ifstream readfile("cars.csv", ios :: in);
        string l, w;

        while(!readfile.eof())
        {
            c_row.clear();
            getline(readfile, l);
            stringstream s(l);

            while(getline(s, w, ','))
            {
                c_row.push_back(w);
            }

            if(c_row[3] == "1")
            {
                cout << "\tCar ID  = " << c_row[0] << "\n";
                cout << "\tName  = " << c_row[1] << "\n";
                cout << "\tPrice = Rs." << c_row[2] << "\n";
            }

            cout << "\n\n";
        }
        return;
    }

    string carData()
    {
        system("CLS");
        cout << "\n\n\t Enter pickup location: ";
        cin >> location;
        cout << "\n\t Enter the number of days you want to rent the car: ";
        cin >> days;

        cout << "\t---------------------------------------------\n\n";
        cout<<"\n\tSearching for cars nearby you.....\n\n\n"<<endl;
        system("PAUSE");


        system("CLS");
        cout << "\n\n";
        //int car1, car2;
        string selectedCarID;
        cout << "\tChoose your Car\n";
        cout << "\t-------------------------------------------------\n\n";
        carsDisplayInfo();

        cout << "\t-----------------------------------------------\n\n";
        cout << "\n\tEnter CarID of the car you want : ";
        cin >> selectedCarID;
        string c_status = selectCar(selectedCarID);

        return c_status;
    }

    string selectCar(string id)
    {
        //status 0 of selected car, retrieve info of car and display and calculate rent
        string confirm;
        ifstream readfile("cars.csv", ios :: in);
        string l, w;

        while(!readfile.eof())
        {
            //cout << temp << endl;
            c_row.clear();
            getline(readfile, l);
            stringstream s(l);

            while(getline(s, w, ','))
            {
                c_row.push_back(w);
            }
            if(c_row[0] == id)
            {
                c_row[3] = "0";    //chnge is happening in vector and not in the main file, open file and make chnges waha.

                system("CLS");
                cout << "\n\n\tCONFIRM YOUR BOOKING\n";
                cout << "\t--------------------------------------\n\n";
                cout << "\tCar ID: " << c_row[0] << "\n";
                cout << "\tCar Name: " << c_row[1] << "\n";
                cout << "\tCar Price per day: Rs." << c_row[2] << "\n";
                cout << "\tNo of days booking for: "<< days << "\n";

                calculateRent();
                cout << "\tTotal Rent(including security i.e(Rs.500): Rs." << rent << "\n\n";
                cout << "\tDo you want to confirm your booking?(yes/no) ";
                cin >> confirm;
                break;

            }


        }
        return confirm;
    }

    void calculateRent()
    {
        int security = 500;
        rent = days * stoi(c_row[2]) + security;
    }

};


int main()
{
    cout << "\t\tWELCOME TO CABLO \n";
    cout << "\t------------------------------------\n\n";
    //cout << "\tLogin / Register" << endl;
    cout << "\t1. Register \n";
    cout << "\t2. Login \n\n";

    int option;
    cout << "\tChoose an option: ";
    cin >> option;
    cout << "\t------------------------------------\n\n";

    if(option == 1)
    {
        customer c1;
        c1.register_();
    }

    else if(option == 2)
    {
        customer c2;
        int loginStatus = c2.login();
        if(loginStatus == 0)
        {
            return 0;
        }
    }
    else
    {
        cout << "\tEnter a valid option!\n";
        return 0;
    }

    cars c3;
    string booking_status = c3.carData();
    if(booking_status == "yes" || booking_status == "Yes")
    {
        cout << "\tGreat! Your booking is successfull.\n";
    }
    else
    {
        cout << "\tOh no! Your booking is failed.\n";
        return 0;
    }


    return 0;
}
