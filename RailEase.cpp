#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

const int LINE_WIDTH = 58;

void printLine(char ch = '=') {
    for (int i = 0; i < LINE_WIDTH; i++) cout << ch;
    cout << '\n';
}

void printHeading(const string& heading) {
    printLine('=');
    int leftPadding = (LINE_WIDTH - static_cast<int>(heading.length())) / 2;
    if (leftPadding < 0) leftPadding = 0;
    cout << string(leftPadding, ' ') << heading << '\n';
    printLine('=');
}

const int ROWS = 5;
const int COLS = 5;
const int TRAINS = 5;
const int MAX_TICKETS = ROWS * COLS * TRAINS;

// ---------------- GLOBALS ----------------
char seats[TRAINS][ROWS][COLS];
int totalRevenue = 0;
int bookingCount = 0;

// ---------------- PASSENGER INFO ----------------
string passengerName[MAX_TICKETS];
int passengerAge[MAX_TICKETS];
char passengerGender[MAX_TICKETS];
int ticketTrain[MAX_TICKETS];
int ticketRow[MAX_TICKETS];
int ticketCol[MAX_TICKETS];
int ticketID[MAX_TICKETS];
bool ticketCancelled[MAX_TICKETS];

// ---------------- TRAIN INFO ----------------
string trainNames[TRAINS] = {
    "Lahore - Karachi",
    "Lahore - Islamabad",
    "Lahore - Multan",
    "Lahore - Peshawar",
    "Lahore - Quetta"
};

int trainDistance[TRAINS] = {1200, 380, 320, 460, 900};
int rowPriceMultiplier[ROWS] = {1,2,3,4,5};
string rowClasses[ROWS] = {
    "Economy", "Economy+", "Business", "First Class", "Executive"
};

// -------- FUNCTION PROTOTYPES --------
void initializeSeats();
void displayTrainInfo();
void displaySeats(int);
void userTab();
void bookTicket();
void cancelTicket();
void viewTicket();
void managerTab();
int calculateFare(int,int,int);
int generateTicketID();
void enterPassengerDetails(int);

// -------- FILE HANDLING --------
void saveData();
void loadData();

// ---------------- MAIN ----------------
int main(){
    initializeSeats();
    loadData();

    int choice;
    do{
        cout << "\n";
        printHeading("RailEase — A Railway Ticketing Application in C++ TRAIN TICKET BOOKING SYSTEM");
         printHeading("TRAIN TICKET BOOKING SYSTEM");
        cout << "  1.  View Trains\n";
        cout << "  2.  User Menu\n";
        cout << "  3.  View Ticket\n";
        cout << "  4.  Manager Panel\n";
        cout << "  0.  Exit\n";
        printLine('-');
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1: displayTrainInfo(); break;
            case 2: userTab(); break;
            case 3: viewTicket(); break;
            case 4: managerTab(); break;
            case 0: saveData(); cout<<"System Closed.\n"; break;
            default: cout<<"Invalid choice!\n";
        }
    }while(choice!=0);

    return 0;
}

// ------------ INITIALIZE SEATS ------------
void initializeSeats(){
    for(int t=0;t<TRAINS;t++)
        for(int r=0;r<ROWS;r++)
            for(int c=0;c<COLS;c++)
                seats[t][r][c]='X';
}

// ------------ DISPLAY TRAIN INFO ------------
void displayTrainInfo(){
    cout << "\n";
    printHeading("DISCOUNT POLICY");
    cout << "  Children (under 10)       : 50% discount\n";
    cout << "  Senior citizens (60+)     : 20% discount\n";

    cout << "\n";
    printHeading("TRAIN DETAILS");
    for(int t=0;t<TRAINS;t++){
        cout << "\nTrain " << t+1 << ": " << trainNames[t]
             << " | Distance: " << trainDistance[t] << " km\n";
        for(int r=0;r<ROWS;r++){
            cout << "Row " << r+1 << " (" << rowClasses[r] << ") : Rs. "
                 << trainDistance[t] * rowPriceMultiplier[r] << endl;
        }
    }
}

// ------------ DISPLAY SEATS ------------
void displaySeats(int train){
    cout << "\n";
    printHeading("SEAT LAYOUT: " + trainNames[train]);
    cout << left << setw(18) << "Class" << "Seats\n";
    printLine('-');

    for(int r = 0; r < ROWS; r++){
        cout << left << setw(18) << rowClasses[r];
        for(int c = 0; c < COLS; c++)
            cout << seats[train][r][c] << "   ";
        cout << endl;
    }
}

// ------------ USER TAB ------------
void userTab(){
    int ch;
    do{
        cout << "\n";
        printHeading("USER MENU");
        cout << "  1.  View Seats\n";
        cout << "  2.  Book Ticket\n";
        cout << "  3.  Cancel Ticket\n";
        cout << "  0.  Back\n";
        printLine('-');
        cout << "Enter choice: ";
        cin >> ch;

        if(ch==1){
            int t;
            cout<<"Select Train (1-5): ";
            cin>>t;
            if(t < 1 || t > TRAINS){
                cout<<"Invalid train number!\n";
                continue;
            }
            displaySeats(t-1);
        }
        else if(ch==2) bookTicket();
        else if(ch==3) cancelTicket();
    }while(ch!=0);
}

// ------------ PASSENGER DETAILS ------------
void enterPassengerDetails(int i){
    cin.ignore();
    cout<<"Passenger Name: ";
    getline(cin, passengerName[i]);
    do{
        cout<<"Age: ";
        cin>>passengerAge[i];
        if(passengerAge[i] <= 0 || passengerAge[i] > 120)
            cout<<"Invalid age! Try again.\n";
    }while(passengerAge[i] <= 0 || passengerAge[i] > 120);


    cout<<"Gender (M/F): ";
    cin>>passengerGender[i];
}

// ------------ FARE ------------
int calculateFare(int t,int r,int age){
    int fare = trainDistance[t]*rowPriceMultiplier[r];
    if(age<10) fare/=2;
    else if(age>=60) fare = static_cast<int>(fare * 0.8);
    return fare;
}

// ------------ BOOK TICKET ------------
void bookTicket(){
    if(bookingCount>=MAX_TICKETS){
        cout<<"All seats booked!\n"; return;
    }

    int t,r,c;
    cout<<"Select Train (1-5): ";
    cin>>t;
    if(t < 1 || t > TRAINS){
        cout<<"Invalid train number!\n";
        return;
    }
    t--;

    displaySeats(t);

    cout<<"Row (1-5): "; cin>>r;
    cout<<"Seat (1-5): "; cin>>c;
    if(r < 1 || r > ROWS || c < 1 || c > COLS){
        cout<<"Invalid row or seat number!\n";
        return;
    }
    r--; c--;

    if(seats[t][r][c]=='*'){ cout<<"Seat already booked!\n"; return; }

    enterPassengerDetails(bookingCount);

    seats[t][r][c]='*';
    ticketTrain[bookingCount]=t;
    ticketRow[bookingCount]=r;
    ticketCol[bookingCount]=c;
    ticketID[bookingCount]=generateTicketID();
    ticketCancelled[bookingCount]=false;

    int fare = calculateFare(t,r,passengerAge[bookingCount]);
    totalRevenue+=fare;

    cout << "\n========== TICKET CONFIRMED ==========\n";
cout << "Ticket ID:\t" << ticketID[bookingCount] << endl;
cout << "Passenger:\t" << passengerName[bookingCount] << endl;
cout << "Train:\t\t" << trainNames[t] << endl;
cout << "Seat:\t\tRow " << r+1 << " (" << rowClasses[r]
     << "), Seat " << c+1 << endl;
cout << "Fare:\t\tRs. " << fare << endl;
cout << "=====================================\n";
    bookingCount++;
    saveData();
}

// ------------ CANCEL TICKET ------------
void cancelTicket(){
    int id;
    cout<<"Enter Ticket ID: ";
    cin>>id;

    for(int i=0;i<bookingCount;i++){
        if(ticketID[i]==id && !ticketCancelled[i]){
            ticketCancelled[i]=true;
            seats[ticketTrain[i]][ticketRow[i]][ticketCol[i]]='X';

            int fare = calculateFare(ticketTrain[i], ticketRow[i], passengerAge[i]);
            int fine = ceil(fare * 0.1);
            int refund = fare - fine;

            totalRevenue -= refund;

            cout<<"Ticket Cancelled\n";
            cout<<"Refund: Rs. "<<refund<<"\n";
            cout<<"Cancellation Fine: Rs. "<<fine<<"\n";
            saveData();
            return;
        }
    }
    cout<<"Ticket not found.\n";
}

// ------------ VIEW TICKET ------------
void viewTicket(){
    int id;
    cout<<"Enter Ticket ID: ";
    cin>>id;

    for(int i=0;i<bookingCount;i++){
        if(ticketID[i]==id){
            cout<<"\nPassenger: "<<passengerName[i]<<endl;
            cout<<"Train: "<<trainNames[ticketTrain[i]]<<endl;
            cout<<"Seat: Row "<<ticketRow[i]+1<<" ("<<rowClasses[ticketRow[i]]<<") Seat "<<ticketCol[i]+1<<endl;
            cout<<"Status: "<<(ticketCancelled[i]?"Cancelled":"Confirmed")<<endl;
            return;
        }
    }
    cout<<"Ticket not found.\n";
}

// ------------ MANAGER PANEL ------------
void managerTab(){
    string pwd;
    cout<<"Enter Manager Password: ";
    cin>>pwd;
    if(pwd!="123456@mng"){ cout<<"Access Denied!\n"; return; }

    cout<<"\n=========== MANAGER DASHBOARD ===========\n";

    cout<<"\n--- Seat Status (All Trains) ---\n";
    for(int t=0;t<TRAINS;t++)
        displaySeats(t);

    int trainCount[TRAINS]={0};
    int classCount[ROWS]={0};
    int totalBookings=0;

    for(int i=0;i<bookingCount;i++){
        if(!ticketCancelled[i]){
            trainCount[ticketTrain[i]]++;
            classCount[ticketRow[i]]++;
            totalBookings++;
        }
    }

    cout<<"\n--- Bookings Per Train ---\n";
    for(int t=0;t<TRAINS;t++)
        cout<<trainNames[t]<<": "<<trainCount[t]<<" bookings\n";

    cout<<"\n--- Bookings Per Class ---\n";
    for(int r=0;r<ROWS;r++)
        cout<<rowClasses[r]<<": "<<classCount[r]<<" bookings\n";

    cout<<"\nTotal Active Bookings: "<<totalBookings<<endl;
    cout<<"Total Revenue: Rs. "<<totalRevenue<<endl;
}

// ------------ FILE SAVE ------------
void saveData(){
    ofstream fout("bookings.txt");
    fout<<bookingCount<<endl;
    for(int i=0;i<bookingCount;i++){
        fout<<ticketID[i]<<endl
            <<passengerName[i]<<endl
            <<passengerAge[i]<<" "<<passengerGender[i]<<endl
            <<ticketTrain[i]<<" "<<ticketRow[i]<<" "<<ticketCol[i]<<endl
            <<ticketCancelled[i]<<endl;
    }
    fout<<totalRevenue;
    fout.close();
}

// ------------ FILE LOAD ------------
void loadData(){
    ifstream fin("bookings.txt");
    if(!fin) return;

    fin>>bookingCount;
    fin.ignore();

    for(int i=0;i<bookingCount;i++){
        fin>>ticketID[i]; fin.ignore();
        getline(fin, passengerName[i]);
        fin>>passengerAge[i]>>passengerGender[i];
        fin>>ticketTrain[i]>>ticketRow[i]>>ticketCol[i];
        fin>>ticketCancelled[i];
        fin.ignore();

        if(!ticketCancelled[i])
            seats[ticketTrain[i]][ticketRow[i]][ticketCol[i]]='*';
    }
    fin>>totalRevenue;
    fin.close();
}

// ------------ TICKET ID ------------
int generateTicketID(){
    return 1000 + bookingCount;
}

