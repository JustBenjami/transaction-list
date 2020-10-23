#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::ofstream;
using std::ifstream;
using std::ostream;
using std::istream;

const int MAX_TRANSACTIONS = 5;

struct Transaction{
	unsigned short int day;
	unsigned short int month;
	unsigned short int year;
	double amount;
	string merchant;
};

struct Transactions{
	unsigned int count;
	Transaction transactions[MAX_TRANSACTIONS];



};

bool ReadTransaction(istream& input, Transaction& transaction);
bool WriteTransaction(ostream& output, const Transaction& transaction);
void InitTransactions(Transactions& transactions);
bool AddTransaction(Transactions& transactions, const Transaction& transaction);
int WriteTransactions(ostream& output, const Transactions& transactions);
int ReadTransactions(istream& input, Transactions& transactions);
double TotalTransactions(const Transactions& transactions);


int main() {
	Transactions myTransactions;
	InitTransactions(myTransactions);

	return 0;
}

bool ReadTransaction(istream& input, Transaction& transaction){
	if (input.fail())
		return false;
	input >> transaction.day >> transaction.month >> transaction.year
		>> transaction.merchant >> transaction.amount;
	return !input.fail();
}
bool WriteTransaction(ostream& output, const Transaction& transaction){
	output << transaction.day << transaction.month << transaction.year
		   << transaction.merchant << transaction.amount;
	return !output.fail();
}
void InitTransactions(Transactions& transactions){
	transactions.count = 0;
}
bool AddTransaction(Transactions& transactions, const Transaction& transaction){
	if (transactions.count == MAX_TRANSACTIONS)
		return false;
	transactions.transactions[transactions.count] = transaction;
	transactions.count++;
}
int WriteTransactions(ostream& output, const Transactions& transactions){
	if (output.fail()){
		return -1;
	}
	unsigned int transactionsWritten = 0;
	for (unsigned int i = 0; i < transactions.count; ++i) {
		WriteTransaction(output, transactions.transactions[i]);
		transactionsWritten++;
	}
	return transactionsWritten;
}
int ReadTransactions(istream& input, Transactions& transactions){
	if (input.fail())
		return -1;
	Transaction aTransaction;
	unsigned int transactionsRead = 0;
	for (unsigned int i = 0; i < transactions.count; ++i) {
		if (ReadTransaction(input, aTransaction)){
			if (AddTransaction(transactions, aTransaction))
				transactionsRead++;
			else
				break;
		}else{
			break;
		}
	}
	return transactionsRead;
}
double TotalTransactions(const Transactions& transactions){
	double total = 0.0;
	for (unsigned int i = 0; i < transactions.count; ++i) {
		total += transactions.transactions[i].amount;
	}
}
