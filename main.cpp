#include <iostream>
#include "RoboBank_Account.h"
#include "cal.h"

using namespace std;

int main() {
    char continu;
        do {
            int choice;
            cout << "============== RoboBank Account ==================" << endl;
            cout << "1. Checking account with fee" << endl;
            cout << "2. Savings interest" << endl;
            cout << "3. Apply prebuilt records" << endl;
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

        switch(choice) {
            case 1: {
                AccountSettings chk_settings = {Checking, 0.00, 150};
                Account A("CHK-001", chk_settings, 0);
                A.deposit(100000, 20250101100000);
                A.withdrawl(25000, 20250102120000);
                A.charge_fee(1500, 20250104180000);
                
                cout << "balance(A) = " << A.balance_cents() << endl;
                cout << "Audit size = " << A.audit_size() << endl;
                break;
            }
           case 2: {
               AccountSettings sav_settings = {Savings, 0.05, 0};
               Account S("SAV-010", sav_settings, 500000);
               S.post_simple_interest(31, 365, 20250131235959);

               cout << "balance(S) = " << S.balance_cents() << endl;

    // ================== Print last audit entry ==================
              const TxRecord* S_audit = S.audit_data();
              int S_count = S.audit_size();
              if (S_count > 0) {
                  const TxRecord& last = S_audit[S_count - 1];
                  cout << "Last audit entry (S) = {";
        switch (last.kind) {
            case Deposit: cout << "Deposit";
                break;
            case Withdrawal: cout << "Withdrawal";
                break;
            case Fee: cout << "Fee";
                break;
            case Interest: cout << "Interest"; 
                break;
        }
        cout << ", " << last.amount_cents
             << ", " << last.timestamp
             << ", " << (last.note ? last.note :"no note")
             << " }" << endl;
    }
                break;}
            case 3: {
                AccountSettings chk_settings = { Checking, 0.00, 150 };
                Account A("CHK-002", chk_settings, 0);

                TxRecord t1 = {Deposit, 100000, 20250101100000, "Payroll"};
                TxRecord t2 = {Withdrawal, 25000, 20250102120000, "ATM"};
                TxRecord t3 = {Fee, 1500, 20250104180000, "Monthly"};
                A.apply(t1);
                A.apply(t2);
                A.apply(t3);
                cout << "balance = " << A.balance_cents() << endl;
                break;
            }
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

        if (choice != 0) {
            cout << "\nIf you want to continue enter c: ";
            cin >> continu;
        }

    } while(continu == 'c');

    cout << "Thank you for using RoboBank Account!" << endl;
    return 0;
}
