#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace fs = std::filesystem;

vector<string> split(const string& text, char delimiter) {
    vector<string> parts;
    string item;
    stringstream stream(text);
    while (getline(stream, item, delimiter)) {
        parts.push_back(item);
    }
    return parts;
}

string inputLine(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

int inputInt(const string& prompt) {
    while (true) {
        string text = inputLine(prompt);
        try {
            return stoi(text);
        } catch (...) {
            cout << "Please enter a valid number.\n";
        }
    }
}

double inputDouble(const string& prompt) {
    while (true) {
        string text = inputLine(prompt);
        try {
            return stod(text);
        } catch (...) {
            cout << "Please enter a valid amount.\n";
        }
    }
}

struct Customer {
    int id{};
    string name;
    string phone;
    string address;
    string joinedDate;

    string serialize() const {
        return to_string(id) + "|" + name + "|" + phone + "|" + address + "|" + joinedDate;
    }

    static Customer from(const string& line) {
        vector<string> p = split(line, '|');
        Customer c;
        if (p.size() >= 5) {
            c.id = stoi(p[0]);
            c.name = p[1];
            c.phone = p[2];
            c.address = p[3];
            c.joinedDate = p[4];
        }
        return c;
    }
};

struct Vehicle {
    int id{};
    int customerId{};
    string registrationNo;
    string make;
    string model;
    int year{};

    string serialize() const {
        return to_string(id) + "|" + to_string(customerId) + "|" + registrationNo + "|" +
               make + "|" + model + "|" + to_string(year);
    }

    static Vehicle from(const string& line) {
        vector<string> p = split(line, '|');
        Vehicle v;
        if (p.size() >= 6) {
            v.id = stoi(p[0]);
            v.customerId = stoi(p[1]);
            v.registrationNo = p[2];
            v.make = p[3];
            v.model = p[4];
            v.year = stoi(p[5]);
        }
        return v;
    }
};

struct Policy {
    int id{};
    int customerId{};
    int vehicleId{};
    string type;
    double premium{};
    string startDate;
    string endDate;
    string status;

    string serialize() const {
        ostringstream out;
        out << id << "|" << customerId << "|" << vehicleId << "|" << type << "|"
            << premium << "|" << startDate << "|" << endDate << "|" << status;
        return out.str();
    }

    static Policy from(const string& line) {
        vector<string> p = split(line, '|');
        Policy policy;
        if (p.size() >= 8) {
            policy.id = stoi(p[0]);
            policy.customerId = stoi(p[1]);
            policy.vehicleId = stoi(p[2]);
            policy.type = p[3];
            policy.premium = stod(p[4]);
            policy.startDate = p[5];
            policy.endDate = p[6];
            policy.status = p[7];
        }
        return policy;
    }
};

struct Workshop {
    int id{};
    string name;
    string address;
    string phone;

    string serialize() const {
        return to_string(id) + "|" + name + "|" + address + "|" + phone;
    }

    static Workshop from(const string& line) {
        vector<string> p = split(line, '|');
        Workshop w;
        if (p.size() >= 4) {
            w.id = stoi(p[0]);
            w.name = p[1];
            w.address = p[2];
            w.phone = p[3];
        }
        return w;
    }
};

struct Staff {
    int id{};
    string name;
    string role;
    string phone;

    string serialize() const {
        return to_string(id) + "|" + name + "|" + role + "|" + phone;
    }

    static Staff from(const string& line) {
        vector<string> p = split(line, '|');
        Staff s;
        if (p.size() >= 4) {
            s.id = stoi(p[0]);
            s.name = p[1];
            s.role = p[2];
            s.phone = p[3];
        }
        return s;
    }
};

struct Claim {
    int id{};
    int customerId{};
    int vehicleId{};
    int policyId{};
    int workshopId{};
    string incidentDate;
    string description;
    double estimatedAmount{};
    string status;

    string serialize() const {
        ostringstream out;
        out << id << "|" << customerId << "|" << vehicleId << "|" << policyId << "|"
            << workshopId << "|" << incidentDate << "|" << description << "|"
            << estimatedAmount << "|" << status;
        return out.str();
    }

    static Claim from(const string& line) {
        vector<string> p = split(line, '|');
        Claim claim;
        if (p.size() >= 9) {
            claim.id = stoi(p[0]);
            claim.customerId = stoi(p[1]);
            claim.vehicleId = stoi(p[2]);
            claim.policyId = stoi(p[3]);
            claim.workshopId = stoi(p[4]);
            claim.incidentDate = p[5];
            claim.description = p[6];
            claim.estimatedAmount = stod(p[7]);
            claim.status = p[8];
        }
        return claim;
    }
};

struct Inspection {
    int id{};
    int claimId{};
    int surveyorId{};
    string inspectionDate;
    string report;
    double approvedAmount{};
    string recommendation;

    string serialize() const {
        ostringstream out;
        out << id << "|" << claimId << "|" << surveyorId << "|" << inspectionDate << "|"
            << report << "|" << approvedAmount << "|" << recommendation;
        return out.str();
    }

    static Inspection from(const string& line) {
        vector<string> p = split(line, '|');
        Inspection inspection;
        if (p.size() >= 7) {
            inspection.id = stoi(p[0]);
            inspection.claimId = stoi(p[1]);
            inspection.surveyorId = stoi(p[2]);
            inspection.inspectionDate = p[3];
            inspection.report = p[4];
            inspection.approvedAmount = stod(p[5]);
            inspection.recommendation = p[6];
        }
        return inspection;
    }
};

class FileDatabase {
public:
    vector<Customer> customers;
    vector<Vehicle> vehicles;
    vector<Policy> policies;
    vector<Claim> claims;
    vector<Inspection> inspections;
    vector<Workshop> workshops;
    vector<Staff> staff;

    explicit FileDatabase(string directory) : dataDir(std::move(directory)) {
        fs::create_directories(dataDir);
    }

    void loadAll() {
        customers = load<Customer>("customers.txt");
        vehicles = load<Vehicle>("vehicles.txt");
        policies = load<Policy>("policies.txt");
        claims = load<Claim>("claims.txt");
        inspections = load<Inspection>("inspections.txt");
        workshops = load<Workshop>("workshops.txt");
        staff = load<Staff>("staff.txt");
    }

    void saveAll() const {
        save("customers.txt", customers);
        save("vehicles.txt", vehicles);
        save("policies.txt", policies);
        save("claims.txt", claims);
        save("inspections.txt", inspections);
        save("workshops.txt", workshops);
        save("staff.txt", staff);
    }

private:
    string dataDir;

    template <typename T>
    vector<T> load(const string& fileName) const {
        vector<T> records;
        ifstream file(dataDir + "/" + fileName);
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                records.push_back(T::from(line));
            }
        }
        return records;
    }

    template <typename T>
    void save(const string& fileName, const vector<T>& records) const {
        ofstream file(dataDir + "/" + fileName);
        for (const T& record : records) {
            file << record.serialize() << '\n';
        }
    }
};

class InsuranceSystem {
public:
    explicit InsuranceSystem(FileDatabase database) : db(std::move(database)) {
        db.loadAll();
    }

    ~InsuranceSystem() {
        db.saveAll();
    }

    void registerCustomer() {
        Customer c;
        c.id = nextId(db.customers);
        c.name = inputLine("Name: ");
        c.phone = inputLine("Phone: ");
        c.address = inputLine("Address: ");
        c.joinedDate = inputLine("Joined date (YYYY-MM-DD): ");
        db.customers.push_back(c);
        db.saveAll();
        cout << "Customer registered with ID " << c.id << ".\n";
    }

    void registerVehicle() {
        int customerId = inputInt("Customer ID: ");
        if (!findCustomer(customerId)) {
            cout << "Customer not found.\n";
            return;
        }

        Vehicle v;
        v.id = nextId(db.vehicles);
        v.customerId = customerId;
        v.registrationNo = inputLine("Registration number: ");
        v.make = inputLine("Make: ");
        v.model = inputLine("Model: ");
        v.year = inputInt("Year: ");
        db.vehicles.push_back(v);
        db.saveAll();
        cout << "Vehicle registered with ID " << v.id << ".\n";
    }

    void registerWorkshop() {
        Workshop w;
        w.id = nextId(db.workshops);
        w.name = inputLine("Workshop name: ");
        w.address = inputLine("Address: ");
        w.phone = inputLine("Phone: ");
        db.workshops.push_back(w);
        db.saveAll();
        cout << "Registered workshop ID " << w.id << ".\n";
    }

    void registerStaff() {
        Staff s;
        s.id = nextId(db.staff);
        s.name = inputLine("Name: ");
        s.role = inputLine("Role (Salesman/Surveyor/Manager): ");
        s.phone = inputLine("Phone: ");
        db.staff.push_back(s);
        db.saveAll();
        cout << "Staff member registered with ID " << s.id << ".\n";
    }

    void createPolicy() {
        int customerId = inputInt("Customer ID: ");
        int vehicleId = inputInt("Vehicle ID: ");
        if (!findCustomer(customerId) || !findVehicle(vehicleId, customerId)) {
            cout << "Customer or vehicle not found.\n";
            return;
        }

        Policy p;
        p.id = nextId(db.policies);
        p.customerId = customerId;
        p.vehicleId = vehicleId;
        p.type = inputLine("Policy type: ");
        p.premium = inputDouble("Premium: ");
        p.startDate = inputLine("Start date (YYYY-MM-DD): ");
        p.endDate = inputLine("End date (YYYY-MM-DD): ");
        p.status = "Active";
        db.policies.push_back(p);
        db.saveAll();
        cout << "Policy created with ID " << p.id << ".\n";
    }

    void fileClaim() {
        int policyId = inputInt("Policy ID: ");
        const Policy* policy = findPolicy(policyId);
        if (!policy || policy->status != "Active") {
            cout << "Active policy not found.\n";
            return;
        }

        int workshopId = inputInt("Registered workshop ID: ");
        if (!findWorkshop(workshopId)) {
            cout << "Workshop is not registered. Claim cannot be filed.\n";
            return;
        }

        Claim claim;
        claim.id = nextId(db.claims);
        claim.customerId = policy->customerId;
        claim.vehicleId = policy->vehicleId;
        claim.policyId = policy->id;
        claim.workshopId = workshopId;
        claim.incidentDate = inputLine("Incident date (YYYY-MM-DD): ");
        claim.description = inputLine("Damage description: ");
        claim.estimatedAmount = inputDouble("Estimated repair amount: ");
        claim.status = "PendingInspection";
        db.claims.push_back(claim);
        db.saveAll();
        cout << "Claim filed with ID " << claim.id << ".\n";
    }

    void assignInspection() {
        int claimId = inputInt("Claim ID: ");
        Claim* claim = findClaim(claimId);
        if (!claim) {
            cout << "Claim not found.\n";
            return;
        }

        int surveyorId = inputInt("Surveyor staff ID: ");
        if (!findStaffByRole(surveyorId, "Surveyor")) {
            cout << "Surveyor not found.\n";
            return;
        }

        Inspection inspection;
        inspection.id = nextId(db.inspections);
        inspection.claimId = claimId;
        inspection.surveyorId = surveyorId;
        inspection.inspectionDate = inputLine("Inspection date (YYYY-MM-DD): ");
        inspection.report = "Pending";
        inspection.approvedAmount = 0.0;
        inspection.recommendation = "Pending";
        db.inspections.push_back(inspection);
        claim->status = "InspectionAssigned";
        db.saveAll();
        cout << "Inspection assigned with ID " << inspection.id << ".\n";
    }

    void submitInspectionReport() {
        int inspectionId = inputInt("Inspection ID: ");
        Inspection* inspection = findInspectionById(inspectionId);
        if (!inspection) {
            cout << "Inspection not found.\n";
            return;
        }

        inspection->report = inputLine("Report: ");
        inspection->approvedAmount = inputDouble("Approved amount recommended: ");
        inspection->recommendation = inputLine("Recommendation (Approve/Reject): ");
        Claim* claim = findClaim(inspection->claimId);
        if (claim) {
            claim->status = "InspectionSubmitted";
        }
        db.saveAll();
        cout << "Inspection report submitted.\n";
    }

    void decideClaim() {
        int claimId = inputInt("Claim ID: ");
        Claim* claim = findClaim(claimId);
        Inspection* inspection = findInspectionByClaim(claimId);
        if (!claim || !inspection || inspection->recommendation == "Pending") {
            cout << "Claim or completed inspection report not found.\n";
            return;
        }

        cout << "Inspection report: " << inspection->report << "\n";
        cout << "Recommended amount: " << fixed << setprecision(2) << inspection->approvedAmount << "\n";
        string decision = inputLine("Manager decision (Approve/Reject): ");
        claim->status = (decision == "Approve") ? "Approved" : "Rejected";
        db.saveAll();
        cout << "Claim status updated to " << claim->status << ".\n";
    }

    void showCustomers() const {
        for (const Customer& c : db.customers) {
            cout << c.id << " | " << c.name << " | " << c.phone << " | "
                 << c.address << " | joined " << c.joinedDate << "\n";
        }
    }

    void showVehicles() const {
        for (const Vehicle& v : db.vehicles) {
            cout << v.id << " | customer " << v.customerId << " | " << v.registrationNo
                 << " | " << v.make << " " << v.model << " | " << v.year << "\n";
        }
    }

    void showPolicies() const {
        for (const Policy& p : db.policies) {
            cout << p.id << " | customer " << p.customerId << " | vehicle " << p.vehicleId
                 << " | " << p.type << " | premium " << p.premium << " | " << p.status << "\n";
        }
    }

    void showWorkshops() const {
        for (const Workshop& w : db.workshops) {
            cout << w.id << " | " << w.name << " | " << w.address << " | " << w.phone << "\n";
        }
    }

    void showStaff() const {
        for (const Staff& s : db.staff) {
            cout << s.id << " | " << s.name << " | " << s.role << " | " << s.phone << "\n";
        }
    }

    void reportNewCustomersByMonth() const {
        string month = inputLine("Month (YYYY-MM): ");
        for (const Customer& c : db.customers) {
            if (c.joinedDate.rfind(month, 0) == 0) {
                cout << c.id << " | " << c.name << " | " << c.joinedDate << "\n";
            }
        }
    }

    void reportPendingClaims() const {
        for (const Claim& claim : db.claims) {
            if (claim.status != "Approved" && claim.status != "Rejected") {
                printClaim(claim);
            }
        }
    }

    void reportInspectionReports() const {
        for (const Inspection& inspection : db.inspections) {
            cout << "Inspection " << inspection.id << " | claim " << inspection.claimId
                 << " | surveyor " << inspection.surveyorId << " | " << inspection.inspectionDate
                 << " | " << inspection.recommendation << " | amount "
                 << inspection.approvedAmount << "\n";
            cout << "  Report: " << inspection.report << "\n";
        }
    }

    void reportPreviousClaimsByCustomer() const {
        int customerId = inputInt("Customer ID: ");
        for (const Claim& claim : db.claims) {
            if (claim.customerId == customerId) {
                printClaim(claim);
            }
        }
    }

private:
    FileDatabase db;

    template <typename T>
    static int nextId(const vector<T>& records) {
        int maxId = 0;
        for (const T& record : records) {
            maxId = max(maxId, record.id);
        }
        return maxId + 1;
    }

    const Customer* findCustomer(int id) const {
        for (const Customer& c : db.customers) {
            if (c.id == id) {
                return &c;
            }
        }
        return nullptr;
    }

    const Vehicle* findVehicle(int id, int customerId) const {
        for (const Vehicle& v : db.vehicles) {
            if (v.id == id && v.customerId == customerId) {
                return &v;
            }
        }
        return nullptr;
    }

    const Policy* findPolicy(int id) const {
        for (const Policy& p : db.policies) {
            if (p.id == id) {
                return &p;
            }
        }
        return nullptr;
    }

    const Workshop* findWorkshop(int id) const {
        for (const Workshop& w : db.workshops) {
            if (w.id == id) {
                return &w;
            }
        }
        return nullptr;
    }

    const Staff* findStaffByRole(int id, const string& role) const {
        for (const Staff& s : db.staff) {
            if (s.id == id && s.role == role) {
                return &s;
            }
        }
        return nullptr;
    }

    Claim* findClaim(int id) {
        for (Claim& claim : db.claims) {
            if (claim.id == id) {
                return &claim;
            }
        }
        return nullptr;
    }

    Inspection* findInspectionById(int id) {
        for (Inspection& inspection : db.inspections) {
            if (inspection.id == id) {
                return &inspection;
            }
        }
        return nullptr;
    }

    Inspection* findInspectionByClaim(int claimId) {
        for (Inspection& inspection : db.inspections) {
            if (inspection.claimId == claimId) {
                return &inspection;
            }
        }
        return nullptr;
    }

    void printClaim(const Claim& claim) const {
        cout << "Claim " << claim.id << " | customer " << claim.customerId
             << " | vehicle " << claim.vehicleId << " | policy " << claim.policyId
             << " | workshop " << claim.workshopId << " | " << claim.incidentDate
             << " | amount " << claim.estimatedAmount << " | " << claim.status << "\n";
        cout << "  Damage: " << claim.description << "\n";
    }
};

class ConsoleUI {
public:
    explicit ConsoleUI(InsuranceSystem& system) : insurance(system) {}

    void run() {
        while (true) {
            printMainMenu();
            int choice = inputInt("Choice: ");
            cout << "\n";
            if (choice == 0) {
                cout << "Goodbye.\n";
                return;
            }
            handleChoice(choice);
            cout << "\n";
        }
    }

private:
    InsuranceSystem& insurance;

    static void printMainMenu() {
        cout << "==== Automobile Insurance System ====\n"
             << "1. Register customer\n"
             << "2. Register vehicle\n"
             << "3. Register workshop\n"
             << "4. Register staff\n"
             << "5. Create insurance policy\n"
             << "6. File claim\n"
             << "7. Assign inspection to surveyor\n"
             << "8. Submit inspection report\n"
             << "9. Manager claim decision\n"
             << "10. List customers\n"
             << "11. List vehicles\n"
             << "12. List policies\n"
             << "13. List workshops\n"
             << "14. List staff\n"
             << "15. Report: new customers by month\n"
             << "16. Report: pending claims\n"
             << "17. Report: inspection reports\n"
             << "18. Report: previous claims by customer\n"
             << "0. Exit\n";
    }

    void handleChoice(int choice) {
        switch (choice) {
            case 1: insurance.registerCustomer(); break;
            case 2: insurance.registerVehicle(); break;
            case 3: insurance.registerWorkshop(); break;
            case 4: insurance.registerStaff(); break;
            case 5: insurance.createPolicy(); break;
            case 6: insurance.fileClaim(); break;
            case 7: insurance.assignInspection(); break;
            case 8: insurance.submitInspectionReport(); break;
            case 9: insurance.decideClaim(); break;
            case 10: insurance.showCustomers(); break;
            case 11: insurance.showVehicles(); break;
            case 12: insurance.showPolicies(); break;
            case 13: insurance.showWorkshops(); break;
            case 14: insurance.showStaff(); break;
            case 15: insurance.reportNewCustomersByMonth(); break;
            case 16: insurance.reportPendingClaims(); break;
            case 17: insurance.reportInspectionReports(); break;
            case 18: insurance.reportPreviousClaimsByCustomer(); break;
            default: cout << "Unknown option.\n"; break;
        }
    }
};

int main() {
    FileDatabase database("data");
    InsuranceSystem system(database);
    ConsoleUI ui(system);
    ui.run();
    return 0;
}
