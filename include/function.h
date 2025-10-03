#ifndef FUNCTION_H
#define FUNCTION_H

const int MAX_ACCOUNTS = 100;
const int MAX_ID_LEN = 20;

 /*enum TxType { Deposit=0, Withdrawal=1, Fee=2, Interest=3, TransferIn=4, TransferOut=5 };*/

// Ledger functions
int find_account_index(char ac_account_id[][MAX_ID_LEN], int ac_count, char* account_id);
int get_or_create_account(char ac_account_id[][MAX_ID_LEN], int* ac_balance, const int ac_capacity, int& ac_count,char* account_id);
void apply_one(char ac_account_id[][MAX_ID_LEN], int* ac_balance, const int ac_capacity, int& ac_count, const char* account_id, int tx_type, int amount_cents);
void apply_all(char tx_account_id[][MAX_ID_LEN], int* tx_type, int* tx_amount_cents, int tx_count,
               char ac_account_id[][MAX_ID_LEN], int* ac_balance, const int ac_capacity, int& ac_count);

int balance_of(char ac_account_id[][MAX_ID_LEN], int* ac_balance, int ac_count, char* account_id);
void bank_summary(int* tx_type, int* tx_amount_cents, int tx_count, int* ac_balance, int ac_count,
                  int& out_total_deposits, int& out_total_withdrawals, int& out_total_fees,
                  int& out_total_interest, int& out_net_exposure);

#endif
