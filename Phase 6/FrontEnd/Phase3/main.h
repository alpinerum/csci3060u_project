#include <string>
#ifndef MAIN_H
#define MAIN_H

void login();
void mainMenu();
void create();
void deleteUser(std::string);
void buy();
void sell();
void addCredit();
void returnTicket();
std::string pad();
std::string hashit();
void writeToFile();
void readFromFile();
void logout();

extern std::string username;
extern bool isLoggedIn;
extern std::string code;
extern std::string eventName;
extern std::string sellerName;
extern std::string userCommand;
extern int amountOfTickets;
extern float pricePerTicket;
extern int ticketAmount;
extern std::string line;
extern int userChoice;
extern int seek;
extern std::string buyerUser;
extern std::string sellerUser;
extern float creditToTransfer;
extern float totalTicketCost;
extern float wantToAdd;
extern std::string creditUser;
extern std::string name;
extern std::string status;
extern std::string statusDeleted;
extern float balance;
extern std::string newUser;
extern std::string newUserType;
extern float userCredit;
extern std::string wantToDelete;
extern const char *currentUserAccounts;
extern const char *availableTickets;

#endif
