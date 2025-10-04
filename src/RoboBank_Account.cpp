#include "RoboBank_Account.h"
#include "cal.h"
#include <iostream>
#include <cstring>

//============================== Constructor ======================//
Account::Account(const char* id, const AccountSettings& settings,
                 long long opening_balance_cents)
    : id_(id),
      settings_(settings),
      balance_cents_(opening_balance_cents),
      audit_count_(0) {}

//============================== Private Helper ===================//
void Account::record(TxKind kind, long long amount, long long ts, const char* note) {
    if (audit_count_ < kMaxAudit) {
        audit_[audit_count_] = { kind, amount, ts, note };
        audit_count_++;
    } else {
        // Ignore new transaction if audit is full
        std::cout << "Audit full!\n";
    }
}

//=============================== Getters =========================//
const char* Account::id() const {
    return id_;
}

AccountType Account::type() const {
    return settings_.type;
}

long long Account::balance_cents() const {
    return balance_cents_;
}

int Account::audit_size() const {
    return audit_count_;
}

const TxRecord* Account::audit_data() const {
    return audit_;
}

//=========================== Operations ==========================//
void Account::deposit(long long amount_cents, long long ts, const char* note) {
    balance_cents_ = apply_deposit((int)balance_cents_, (int)amount_cents);
    record(Deposit, amount_cents, ts, note);
}

void Account::withdrawl(long long amount_cents, long long ts, const char* note) {
    balance_cents_ = apply_withdrawal((int)balance_cents_, (int)amount_cents);
    record(Withdrawal, amount_cents, ts, note);
}

void Account::charge_fee(long long fee_cents, long long ts, const char* note) {
    balance_cents_ = apply_fee((int)balance_cents_, (unsigned int)fee_cents);
    record(Fee, fee_cents, ts, note);
}

void Account::post_simple_interest(int days, int basis, long long ts, const char* note) {
    long long interest = simple_interest((int)balance_cents_, settings_.apr, days, basis, true);
    balance_cents_ += interest;
    record(Interest, interest, ts, note);
}

void Account::apply(const TxRecord& tx) {     
    switch (tx.kind) {
        case Deposit:
            deposit(tx.amount_cents, tx.timestamp, tx.note);
            break;
        case Withdrawal:
            withdrawl(tx.amount_cents, tx.timestamp, tx.note);
            break;
        case Fee:
            charge_fee(tx.amount_cents, tx.timestamp, tx.note);
            break;
        case Interest:
            deposit(tx.amount_cents, tx.timestamp, tx.note);
            break;
        default:
            break;
    }
}
