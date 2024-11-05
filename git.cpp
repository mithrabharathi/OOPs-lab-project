#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_MOVIES = 5;  // Max number of movies in the array

// Movie class with constructors, friend functions, and operator overloading
class Movie {
    string title;
    int duration;
    float rating;

public:
    Movie(string t = "Untitled", int d = 120, float r = 0.0) : title(t), duration(d), rating(r) {}
    Movie(const Movie &m) : title(m.title), duration(m.duration), rating(m.rating) {}

    void display() const { cout << "Movie: " << title << ", Duration: " << duration << " mins, Rating: " << rating << endl; }

    friend bool operator>(const Movie &m1, const Movie &m2) { return m1.rating > m2.rating; }
    string getTitle() const { return title; }
};

// User class with simple inheritance and getter methods
class User {
protected:
    string name;
    int age;

public:
    User(string n, int a) : name(n), age(a) {}
    virtual void display() { cout << "User: " << name << ", Age: " << age << endl; }

    string getName() const { return name; }
    int getAge() const { return age; }
};

// Customer inherits from User
class Customer : public User {
public:
    Customer(string n, int a) : User(n, a) {}
    void display() { cout << "Customer: " << name << ", Age: " << age << endl; }
};

// VIPCustomer inherits from Customer (Multi-level inheritance)
class VIPCustomer : public Customer {
    float discountRate;

public:
    VIPCustomer(string n, int a, float d) : Customer(n, a), discountRate(d) {}
    void display() { cout << "VIP Customer: " << name << ", Age: " << age << ", Discount Rate: " << discountRate << "%" << endl; }
};

// Booking class with constructors, operator overloading, and subscript operator overloading
class Booking {
    static int bookingCount;  // Static variable
    int bookingID;
    string movieTitle;
    int *seats;
    int seatCount;

public:
    Booking(string title, int count = 1) : movieTitle(title), seatCount(count) {
        bookingID = ++bookingCount;
        seats = new int[seatCount];
    }
    Booking(const Booking &b) : movieTitle(b.movieTitle), seatCount(b.seatCount) {
        bookingID = ++bookingCount;
        seats = new int[seatCount];
        for (int i = 0; i < seatCount; i++) seats[i] = b.seats[i];
    }
    ~Booking() { delete[] seats; }

    Booking& operator=(const Booking &b) {
        if (this == &b) return *this;
        delete[] seats;
        movieTitle = b.movieTitle;
        seatCount = b.seatCount;
        seats = new int[seatCount];
        for (int i = 0; i < seatCount; i++) seats[i] = b.seats[i];
        return *this;
    }

    int& operator[](int index) { return seats[index]; }  // Subscript operator

    void display() const { cout << "Booking ID: " << bookingID << ", Movie: " << movieTitle << endl; }
    static int getTotalBookings() { return bookingCount; }  // Static function
};

int Booking::bookingCount = 0;

// Function overloading examples using getter for name
void bookTicket(Customer &c) { cout << c.getName() << " booked a ticket." << endl; }
void bookTicket(VIPCustomer &c) { cout << c.getName() << " booked a ticket with VIP discount." << endl; }

void displayMenu() {
    cout << "\n--- Entertainment Management System ---" << endl;
    cout << "1. Add Movie" << endl;
    cout << "2. Add Customer" << endl;
    cout << "3. Add VIP Customer" << endl;
    cout << "4. Create Booking" << endl;
    cout << "5. View Movies" << endl;
    cout << "6. View Bookings" << endl;
    cout << "7. View Total Bookings" << endl;
    cout << "8. Exit" << endl;
    cout << "Select an option: ";
}

int main() {
    vector<Movie> movieList;
    Movie movieArray[MAX_MOVIES];  // Array of Movie objects
    int movieArrayCount = 0;

    vector<Customer> customers;
    vector<VIPCustomer> vipCustomers;
    vector<Booking> bookings;

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  // Clear the newline character from input

        switch (choice) {
            case 1: {
                string title;
                int duration;
                float rating;
                cout << "Enter movie title: ";
                getline(cin, title);
                cout << "Enter movie duration (in minutes): ";
                cin >> duration;
                cout << "Enter movie rating (0-10): ";
                cin >> rating;

                if (movieArrayCount < MAX_MOVIES) {
                    movieArray[movieArrayCount++] = Movie(title, duration, rating);  // Adding to array
                    cout << "Movie added to array successfully." << endl;
                } else {
                    movieList.push_back(Movie(title, duration, rating));  // Adding to vector
                    cout << "Movie added to list successfully." << endl;
                }
                break;
            }
            case 2: {
                string name;
                int age;
                cout << "Enter customer name: ";
                getline(cin, name);
                cout << "Enter customer age: ";
                cin >> age;
                customers.push_back(Customer(name, age));
                cout << "Customer added successfully." << endl;
                break;
            }
            case 3: {
                string name;
                int age;
                float discountRate;
                cout << "Enter VIP customer name: ";
                getline(cin, name);
                cout << "Enter VIP customer age: ";
                cin >> age;
                cout << "Enter VIP discount rate: ";
                cin >> discountRate;
                vipCustomers.push_back(VIPCustomer(name, age, discountRate));
                cout << "VIP Customer added successfully." << endl;
                break;
            }
            case 4: {
                string movieTitle;
                int seatCount;
                cout << "Enter movie title for booking: ";
                getline(cin, movieTitle);
                cout << "Enter number of seats: ";
                cin >> seatCount;
                bookings.push_back(Booking(movieTitle, seatCount));
                cout << "Booking created successfully." << endl;
                break;
            }
            case 5: {
                cout << "\n--- Movie List (Array) ---" << endl;
                for (int i = 0; i < movieArrayCount; i++) {
                    movieArray[i].display();
                }
                cout << "\n--- Movie List (Vector) ---" << endl;
                for (int i = 0; i < movieList.size(); i++) {
                    movieList[i].display();
                }
                break;
            }
            case 6: {
                cout << "\n--- Booking List ---" << endl;
                for (int i = 0; i < bookings.size(); i++) {
                    bookings[i].display();
                }
                break;
            }
            case 7: {
                cout << "Total Bookings: " << Booking::getTotalBookings() << endl;
                break;
            }
            case 8:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

