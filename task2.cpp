#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

const int HEAD = 1;
const int CHIEF_ENGINEER = 2;
const int PROGRAMMER = 3;
const int ADMINISTRATOR = 4;

string getPositionName(int position) {
    switch (position) {
    case HEAD:
        return "Department Head";
    case CHIEF_ENGINEER:
        return "Chief Engineer";
    case PROGRAMMER:
        return "Software Engineer";
    case ADMINISTRATOR:
        return "System Administrator";
    default:
        return "Unknown Position";
    }
}

class ISalaryCalculator {
public:
    virtual int calculateSalary(int position) const = 0;

    virtual ~ISalaryCalculator() {}
};

class SalaryService : public ISalaryCalculator {
public:
    int calculateSalary(int position) const override {
        switch (position) {
        case HEAD:
            return 40000;
        case CHIEF_ENGINEER:
            return 35000;
        case PROGRAMMER:
            return 30000;
        case ADMINISTRATOR:
            return 28000;
        default:
            return 0;
        }
    }
};

class Employee {
private:
    string surname;
    string name;
    string patronymic;
    int position;
    int experience;

public:
    Employee(string surname, string name, string patronymic,
        int position, int experience)
        : surname(surname),
        name(name),
        patronymic(patronymic),
        position(position),
        experience(experience) {
    }

    string getSurname() const {
        return surname;
    }

    int calculateSalary(const ISalaryCalculator& calculator) const {
        return calculator.calculateSalary(position);
    }

    void showInformation(const ISalaryCalculator& calculator) const {
        cout << "\n-----------------------------\n";
        cout << "Surname: " << surname << endl;
        cout << "Name: " << name << endl;
        cout << "Patronymic: " << patronymic << endl;
        cout << "Position: " << getPositionName(position) << endl;
        cout << "Work experience: " << experience << " years" << endl;
        cout << "Salary: " << calculateSalary(calculator) << " UAH" << endl;
        cout << "-----------------------------\n";
    }
};

int choosePosition() {
    int position;

    do {
        cout << "\nChoose a position:\n";
        cout << "1. Department Head\n";
        cout << "2. Chief Engineer\n";
        cout << "3. Software Engineer\n";
        cout << "4. System Administrator\n";
        cout << "Your choice: ";

        cin >> position;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Enter a number from 1 to 4.\n";
            position = 0;
        }
        else if (position < 1 || position > 4) {
            cout << "Error! Enter a number from 1 to 4.\n";
        }

    } while (position < 1 || position > 4);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return position;
}

int inputInteger(const string& message) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Error! Please enter an integer.\n";
    }
}

string inputText(const string& message) {
    string value;

    cout << message;
    getline(cin, value);

    return value;
}

int main() {
    SalaryService salaryService;

    vector<Employee> employees;

    int choice;

    do {
        cout << "\n===== COMPUTER DEPARTMENT =====\n";
        cout << "1. Show all employees\n";
        cout << "2. Add an employee\n";
        cout << "3. Find an employee by surname\n";
        cout << "4. Show total salary fund\n";
        cout << "0. Exit\n";

        choice = inputInteger("Your choice: ");

        switch (choice) {

        case 1: {
            if (employees.empty()) {
                cout << "The employee list is empty.\n";
            }
            else {
                for (const Employee& employee : employees) {
                    employee.showInformation(salaryService);
                }
            }
            break;
        }

        case 2: {
            string surname = inputText("Enter surname: ");
            string name = inputText("Enter name: ");
            string patronymic = inputText("Enter patronymic: ");

            int position = choosePosition();

            int experience;

            do {
                experience = inputInteger("Enter work experience (years): ");

                if (experience < 0) {
                    cout << "Experience cannot be negative.\n";
                }

            } while (experience < 0);

            employees.emplace_back(
                surname,
                name,
                patronymic,
                position,
                experience
            );

            cout << "Employee added successfully!\n";
            break;
        }

        case 3: {
            string surname = inputText("Enter surname to search: ");

            bool found = false;

            for (const Employee& employee : employees) {
                if (employee.getSurname() == surname) {
                    employee.showInformation(salaryService);
                    found = true;
                }
            }

            if (!found) {
                cout << "Employee not found.\n";
            }

            break;
        }

        case 4: {
            int totalSalary = 0;

            for (const Employee& employee : employees) {
                totalSalary += employee.calculateSalary(salaryService);
            }

            cout << "Total salary fund: "
                << totalSalary << " UAH\n";

            break;
        }
        case 0:
            cout << "Program terminated.\n";
            break;

        default:
            cout << "Invalid menu option. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}