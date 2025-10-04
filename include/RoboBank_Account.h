#ifndef ROBOBANK_ACCOUNT_H
#define ROBOBANK_ACCOUNT_H

#include "cal.h"
#include <cstring>

using namespace std;
const int kMaxAudit = 256;
//================Enums==================//
enum AccountType {Checking = 0, Savings = 1};
enum TxKind {Deposit = 0, Withdrawal = 1, Fee = 2, Interest = 3};
//==================Structs=============//
struct AccountSettings {
    AccountType type;
    double apr;
    long long fee_flat_cents;
};

struct TxRecord {
    TxKind kind;
    long long amount_cents;
    long long timestamp;
    const char* note;
};
class Account {
    private:
        const char* id_;
        AccountSettings settings_;
        long long balance_cents_;
        TxRecord audit_[kMaxAudit];
        int audit_count_;

        // Private Helper
        void record(TxKind kind, long long amount, long long ts, const char* note);

    public:
        // Constructor
        Account(const char* id, const AccountSettings& settings, long long opening_balance_cents = 0);

        // Getters
        const char* id() const;
        AccountType type() const;
        double apr() const;
        long long balance_cents() const;
        int audit_size() const;
        const TxRecord* audit_data() const;

        // Operations
        void deposit(long long amount_cents, long long ts, const char* note = nullptr);
        void withdrawl(long long amount_cents, long long ts, const char* note = nullptr);
        void charge_fee(long long fee_cents, long long ts, const char* note = nullptr);
        void post_simple_interest(int days, int basis, long long ts, const char* note = nullptr);
        void apply(const TxRecord& tx);

};
#endif


