#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Train
{
public:
    int trainNo;
    char trainName[50];
    int seats;

    void addTrain()
    {
        cout << "Enter Train Number: ";
        cin >> trainNo;
        cin.ignore();

        cout << "Enter Train Name: ";
        cin.getline(trainName, 50);

        cout << "Enter Total Seats: ";
        cin >> seats;
    }

    void showTrain()
    {
        cout << "\nTrain No: " << trainNo;
        cout << "\nTrain Name: " << trainName;
        cout << "\nAvailable Seats: " << seats << endl;
    }
};

class Passenger
{
public:
    int pnr;
    char name[50];
    int trainNo;

    void bookTicket()
    {
        cout << "Enter PNR Number: ";
        cin >> pnr;
        cin.ignore();

        cout << "Enter Passenger Name: ";
        cin.getline(name, 50);

        cout << "Enter Train Number: ";
        cin >> trainNo;
    }

    void showTicket()
    {
        cout << "\nPNR: " << pnr;
        cout << "\nPassenger Name: " << name;
        cout << "\nTrain Number: " << trainNo << endl;
    }
};

void addTrainRecord()
{
    Train t;
    ofstream fout("train.dat", ios::binary | ios::app);

    t.addTrain();
    fout.write((char*)&t, sizeof(t));

    fout.close();
}

void displayTrains()
{
    Train t;
    ifstream fin("train.dat", ios::binary);

    while (fin.read((char*)&t, sizeof(t)))
    {
        t.showTrain();
    }

    fin.close();
}

void bookReservation()
{
    Passenger p;
    Train t;

    fstream file("train.dat", ios::binary | ios::in | ios::out);

    int tno, found = 0;

    cout << "Enter Train Number for Booking: ";
    cin >> tno;

    while (file.read((char*)&t, sizeof(t)))
    {
        if (t.trainNo == tno)
        {
            found = 1;

            if (t.seats > 0)
            {
                p.bookTicket();

                ofstream fout("passenger.dat", ios::binary | ios::app);
                fout.write((char*)&p, sizeof(p));
                fout.close();

                t.seats--;

                file.seekp(-sizeof(t), ios::cur);
                file.write((char*)&t, sizeof(t));

                cout << "Ticket Booked Successfully\n";
            }
            else
            {
                cout << "No Seats Available\n";
            }

            break;
        }
    }

    if (found == 0)
        cout << "Train Not Found\n";

    file.close();
}

void cancelReservation()
{
    int pnrNo;
    Passenger p;

    ifstream fin("passenger.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);

    cout << "Enter PNR to Cancel: ";
    cin >> pnrNo;

    int found = 0;
    int cancelledTrainNo = 0;

    while (fin.read((char*)&p, sizeof(p)))
    {
        if (p.pnr == pnrNo)
        {
            found = 1;
            cancelledTrainNo = p.trainNo;   // store train number
            cout << "Reservation Cancelled Successfully\n";
        }
        else
        {
            fout.write((char*)&p, sizeof(p));
        }
    }

    fin.close();
    fout.close();

    remove("passenger.dat");
    rename("temp.dat", "passenger.dat");

    if (found == 0)
    {
        cout << "PNR Not Found\n";
        return;
    }

    // Increase seats in train.dat
    Train t;
    fstream file("train.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&t, sizeof(t)))
    {
        if (t.trainNo == cancelledTrainNo)
        {
            t.seats++;   // Increase seat after cancellation

            file.seekp(-sizeof(t), ios::cur);
            file.write((char*)&t, sizeof(t));

            break;
        }
    }

    file.close();
}

void displayPassengers()
{
    Passenger p;
    ifstream fin("passenger.dat", ios::binary);

    while (fin.read((char*)&p, sizeof(p)))
    {
        p.showTicket();
    }

    fin.close();
}

int main()
{
    int ch;

    do
    {
        cout << "\n1.Add Train";
        cout << "\n2.Display Trains";
        cout << "\n3.Book Ticket";
        cout << "\n4.Cancel Ticket";
        cout << "\n5.Display Passengers";
        cout << "\n6.Exit";
        cout << "\nEnter Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            addTrainRecord();
            break;

        case 2:
            displayTrains();
            break;

        case 3:
            bookReservation();
            break;

        case 4:
            cancelReservation();
            break;

        case 5:
            displayPassengers();
            break;

        case 6:
            cout << "Exiting...";
            break;

        default:
            cout << "Invalid Choice";
        }

    } while (ch != 6);

    return 0;
}
