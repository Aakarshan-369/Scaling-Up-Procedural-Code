#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class music {
public:
    string type;
    int months;

    void setMonth(string type) {
        if (type == "FREE" || type == "PERSONAL") {
            months = 1;
        } else if (type == "PREMIUM") {
            months = 3;
        }
    }

    int amount(string type) {
        if (type == "FREE") {
            return 0;
        } else if (type == "PERSONAL") {
            return 100;
        } else if (type == "PREMIUM") {
            return 250;
        } else {
            return 0;
        }
    }
};

class video {
public:
    string type;
    int months;

    void setMonth(string type) {
        if (type == "FREE" || type == "PERSONAL") {
            months = 1;
        } else if (type == "PREMIUM") {
            months = 3;
        }
    }

    int amount(string type) {
        if (type == "FREE") {
            return 0;
        } else if (type == "PERSONAL") {
            return 200;
        } else if (type == "PREMIUM") {
            return 500;
        } else {
            return 0;
        }
    }
};

class podcast {
public:
    string type;
    int months;

    void setMonth(string type) {
        if (type == "FREE" || type == "PERSONAL") {
            months = 1;
        } else if (type == "PREMIUM") {
            months = 3;
        }
    }

    int amount(string type) {
        if (type == "FREE") {
            return 0;
        } else if (type == "PERSONAL") {
            return 100;
        } else if (type == "PREMIUM") {
            return 300;
        } else {
            return 0;
        }
    }
};

class Subscription {
public:
    string start_date;
    bool music;
    bool video;
    bool podcast;
    bool topup;
    int topupMonth;
    string topType;

    int amount_topup(int month) {
        if (topType == "FOUR_DEVICE") {
            return month * 50;
        } else if (topType == "TEN_DEVICE") {
            return month * 100;
        } else {
            return 0;
        }
    }
};

string getRenewalDate(const string& start_date, int months) {
    int day, month, year;
    sscanf(start_date.c_str(), "%d-%d-%d", &day, &month, &year);
    month += months;
    year += month / 12;
    month %= 12;

    stringstream ss;
    ss << setw(2) << setfill('0') << day << "-" << setw(2) << setfill('0') << month << "-" << year;
    return ss.str();
}

int main() {
    Subscription SUB;
    music MUS;
    video VID;
    podcast POD;

    string command;
    while (cin >> command) {
        if (command == "START_SUBSCRIPTION") {
            string start_date;
            cin >> start_date;
            if (start_date.length() != 10 || start_date[2] != '-' || start_date[5] != '-') {
                cout << "INVALID_DATE" << endl;
                return 0;
            }
            SUB.start_date = start_date;
        } else if (command == "ADD_SUBSCRIPTION") {
            string category, plan;
            cin >> category >> plan;

            if (category == "MUSIC") {
                if (MUS.type.empty()) {
                    MUS.type = plan;
                    MUS.setMonth(plan);
                } else {
                    cout << "ADD_SUBSCRIPTION_FAILED" << endl;
                    return 0;
                }
            } else if (category == "VIDEO") {
                if (VID.type.empty()) {
                    VID.type = plan;
                    VID.setMonth(plan);
                } else {
                    cout << "ADD_SUBSCRIPTION_FAILED" << endl;
                    return 0;
                }
            } else if (category == "PODCAST") {
                if (POD.type.empty()) {
                    POD.type = plan;
                    POD.setMonth(plan);
                } else {
                    cout << "ADD_SUBSCRIPTION_FAILED" << endl;
                    return 0;
                }
            } else {
                cout << "ERROR" << endl;
                return 0;
            }
        } else if (command == "ADD_TOPUP") {
            string topup, months;
            cin >> topup >> months;

            if (SUB.topType.empty()) {
                SUB.topType = topup;
                SUB.topupMonth = stoi(months);
            } else {
                cout << "ADD_TOPUP_FAILED" << endl;
                return 0;
            }
        } else if (command == "PRINT_RENEWAL_DETAILS") {
            if (MUS.type.empty() && VID.type.empty() && POD.type.empty()) {
                cout << "SUBSCRIPTIONS_NOT_FOUND" << endl;
                return 0;
            }

            int total_amount = 0;
            if (!MUS.type.empty()) {
                total_amount += MUS.amount(MUS.type);
                string renewal_date = getRenewalDate(SUB.start_date, MUS.months);
                cout << "RENEWAL_REMINDER MUSIC " << renewal_date << endl;
            }
            if (!VID.type.empty()) {
                total_amount += VID.amount(VID.type);
                string renewal_date = getRenewalDate(SUB.start_date, VID.months);
                cout << "RENEWAL_REMINDER VIDEO " << renewal_date << endl;
            }
            if (!POD.type.empty()) {
                total_amount += POD.amount(POD.type);
                string renewal_date = getRenewalDate(SUB.start_date, POD.months);
                cout << "RENEWAL_REMINDER PODCAST " << renewal_date << endl;
            }
            if (!SUB.topType.empty()) {
                total_amount += SUB.amount_topup(SUB.topupMonth);
                string renewal_date = getRenewalDate(SUB.start_date, SUB.topupMonth);
                cout << "RENEWAL_REMINDER TOPUP " << renewal_date << endl;
            }

            cout << "RENEWAL_AMOUNT " << total_amount << endl;
        } else {
            cout << "ERROR" << endl;
            return 0;
        }
    }

    return 0;
}
