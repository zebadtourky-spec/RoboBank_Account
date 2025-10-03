#include <iostream>
#include <cstring>
#include "function.h"
#include "cal.h"
using namespace std;

int find_account_index(char ac_account_id[][MAX_ID_LEN], int ac_count, char* account_id) {
    for(int i = 0; i < ac_count; i++)
        if(strcmp(ac_account_id[i], account_id) == 0)
            return i;
    return -1;
}
int get_or_create_account(char ac_account_id[][MAX_ID_LEN], int* ac_balance,
                          const int ac_capacity, int& ac_count, char* account_id) {
    int index = find_account_index(ac_account_id, ac_count, account_id);
    if(index != -1) {
        return index;
    }

    if(ac_count < ac_capacity) {
        strcpy(ac_account_id[ac_count], account_id);
        ac_balance[ac_count] = 0;
        return ac_count++;
    }
    return -1;
}

void apply_one(char ac_account_id[][MAX_ID_LEN], int* ac_balance, const int ac_capacity, int& ac_count,
               char* account_id, int tx_type, int amount_cents) {
    int idx = get_or_create_account(ac_account_id, ac_balance, ac_capacity, ac_count, account_id);
    if(idx == -1) return;

    switch(tx_type) {
        case Deposit:
        case TransferIn:
        case Interest:
            ac_balance[idx] = apply_deposit(ac_balance[idx], amount_cents);
            break;
        case Withdrawal:
        case TransferOut:
        case Fee:
            ac_balance[idx] = apply_withdrawal(ac_balance[idx], amount_cents);
            break;
        default:
            cout << "Invalid transaction type!\n";
    }
}

void apply_all(char tx_account_id[][MAX_ID_LEN], int* tx_type, int* tx_amount_cents, int tx_count,
               char ac_account_id[][MAX_ID_LEN], int* ac_balance, const int ac_capacity, int& ac_count) {
    for(int i = 0; i < tx_count; i++)
        apply_one(ac_account_id, ac_balance, ac_capacity, ac_count, tx_account_id[i], tx_type[i], tx_amount_cents[i]);
}


int balance_of(char ac_account_id[][MAX_ID_LEN], int* ac_balance, int ac_count, char* account_id) {
    for(int i = 0; i < ac_count; i++)
        if(strcmp(ac_account_id[i], account_id) == 0)
            return ac_balance[i];
    return 0;
}

void bank_summary(int* tx_type, int* tx_amount_cents, int tx_count, int* ac_balance, int ac_count,
                  int& out_total_deposits, int& out_total_withdrawals, int& out_total_fees,
                  int& out_total_interest, int& out_net_exposure) {
    out_total_deposits = 0; out_total_withdrawals = 0;
    out_total_fees = 0; out_total_interest = 0;
    out_net_exposure = 0;

    for(int i = 0; i < tx_count; i++) {
        switch(tx_type[i]) {
            case Deposit: case TransferIn: out_total_deposits += tx_amount_cents[i]; break;
            case Withdrawal: case TransferOut: out_total_withdrawals += tx_amount_cents[i]; break;
            case Fee: out_total_fees += tx_amount_cents[i]; break;
            case Interest: out_total_interest += tx_amount_cents[i]; break;
        }
    }

    for(int i = 0; i < ac_count; i++)
        out_net_exposure += ac_balance[i];
}
