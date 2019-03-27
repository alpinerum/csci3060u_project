/**
* Implementation of the main menu, the login function, and reading and writing
* to the daily transaction file.
*
* @author  Zain Ansari
* @author Ammar Khan
* @author Sumeet Dhillon
* @version 1.0
* @since   2019-02-01
*/
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <list>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "main.h"

  /*
  * Enumerates the functions
  */
  enum userEnter {
    eLogin,
    eCreate,
    eDelete,
    eBuy,
    eSell,
    eRefund,
    eAddCredit,
    eLogout,
    eDefault
  };

  /*
  * Matches user entry to enum value
  */
  userEnter hashit (std::string const& inString){
    if (inString == "login") return eLogin;
    if (inString == "create") return eCreate;
    if (inString == "delete") return eDelete;
    if (inString == "buy") return eBuy;
    if (inString == "sell") return eSell;
    if (inString == "refund") return eRefund;
    if (inString == "addCredit") return eAddCredit;
    if (inString == "logout") return eLogout;
    if (inString != "login" || "create" || "delete" || "buy" || "sell" || "refund" || "addCredit" || "logout") return eDefault;
  }

  /**
  * This is the main menu of the program. It prompts the user to enter a
  * value corresponding to a certain menu command. It then calls that user
  * command.
  * @param  Nothing.
  * @return Nothing.
  */
  void mainMenu()
  {
      code.clear();
      userCommand.clear();
      std::cout<<"\nWelcome to the main menu. Please enter a command to continue \n";
      std::cout << "login = Login \n";
      std::cout << "create = Create Account \n";
      std::cout << "delete = Delete Account \n";
      std::cout << "buy = Buy Tickets \n";
      std::cout << "sell = Sell Tickets \n";
      std::cout << "refund = Refund Credits \n";
      std::cout << "addCredit = Add Credits \n";
      std::cout << "logout = Logout \n";
      std::cin >> userCommand;
      switch (hashit(userCommand))
      {
          case eLogin:
            if(isLoggedIn){
              std::cout << "You are already in! \n";
              mainMenu();
              return;
            }
              code = "10";
              login();
              break;
          case eCreate:
            if(!isLoggedIn){
              std::cout << "You must log in first! \n";
              mainMenu();
              return;
            }
              code = "01";
              create();
              break;
          case eDelete:
            if(!isLoggedIn){
              std::cout << "You must log in first! \n";
              mainMenu();
              return;
            }
              code = "02";
              deleteUser(username);
              break;
          case eSell:
            if(!isLoggedIn){
              std::cout << "You must log in first! \n";
              mainMenu();
              return;
            }
            code = "03";
            sell();
            break;
          case eBuy:
            if(!isLoggedIn){
              std::cout << "You must log in first! \n";
              mainMenu();
              return;
            }
              code = "04";
              buy();
              break;
          case eRefund:
            if(!isLoggedIn){
              std::cout << "You must log in first! \n";
              mainMenu();
              return;
            }
              code = "05";
              returnTicket();
              break;
          case eAddCredit:
            if(!isLoggedIn){
              std::cout << "You must log in first! \n";
              mainMenu();
              return;
            }
              code = "06";
              addCredit();
              break;
          case eLogout:
            if(!isLoggedIn){
              std::cout << "You must log in first! \n";
              mainMenu();
              return;
            }
              std::cout << "Logout Succesful! \n";
              code = "00";
              writeToFile();
              break;
          case eDefault:
              std::cout << "Invalid \n";
              mainMenu();
              return;
          default:
            std::cerr << "Invalid \n";
            mainMenu();
            return;
      }
  }


  /**
  * This is the login function that prompts the user to login to the System
  * The user must enter a username which is checked against a user file which
  * then gives the name, status, and balance of that user
  * @param  Nothing.
  * @return Nothing.
  */
  void login()
  {
      if (code != "10"){
        std::cerr << "ERROR PLEASE RETRY \n";
        mainMenu();
        return;
      }
      std::cout << "Welcome to our Ticket Selling System \n";
      std::cout << "Please enter your username: ";
      std::cin >> username;
      readFromFile();
    }

  /**
  * Takes information from the current user accounts file. First checks if the
  * user is logged in and then reads from the file if the file is available.
  * Displays the name, status and balance of the user.
  * @param  Nothing.
  * @return Nothing.
  */
  void readFromFile()
  {
    //checks if user logged in so reads currentUserAccounts file
    if(!isLoggedIn){
      std::ifstream userLoginFile(currentUserAccounts);
      if(!userLoginFile){
        std::cerr << "File not found! \n";
        return;
      }

      /*
      * Logging in
      */
      if(userLoginFile) {
        while (std::getline(userLoginFile, line))
        {
          std::replace(line.begin(), line.end(), ' ', ' ');

          std::stringstream ss(line);

          ss >> name;
          if(name == username && name != "END"){
            ss >> status;
            ss >> balance;
            std::cout << "name = " << name << "\n";
            std::cout << "status = " << status << "\n";
            std::cout << "balance = " << balance << "\n";
            userLoginFile.close();
            isLoggedIn = true;
            writeToFile();
          } else if(name == "END") {
            std::cerr << "Username not found \n\n";
            return;
          }
        }
        userLoginFile.close();
      }


    }

    /*
    * Checks to see if user is logged in, then reads available tickets file
    */
    if(isLoggedIn){
      std::ifstream currentTicketFile(availableTickets);

      if(!currentTicketFile){
        std::cerr << "Available Tickets File not found! \n";
        return;
      }

      if(currentTicketFile) {
        while (std::getline(currentTicketFile, line))
        {
          std::replace(line.begin(), line.end(), ' ', ' ');

          std::stringstream ss(line);

          ss >> eventName;
          ss >> sellerName;
          ss >> amountOfTickets;
          ss >> pricePerTicket;

          std::cout << "Event Name = " << eventName << "\t";
          std::cout << "Seller Name = " << sellerName << "\t";
          std::cout << "Amount of Tickets = " << amountOfTickets << "\t";
          std::cout << "Price per Ticket = $" << pricePerTicket << "\n";
        }
        currentTicketFile.close();
        return;
      }

    }

  }

  //padding for writing to files helper function
  std::string pad(std::string text, char type){
    int size = 0;
    int padSize= 0;
    int textSize = text.size();
    switch(type)
    {
      //username pad with spaces to the right
     case 'u':
       size = 15;
       padSize = size - textSize;
       text.append(padSize, ' ');
       return text;
       break;
       //event name pad with spaces to the right
     case 'e':
       size = 19;
       padSize = size - textSize;
       text.append(padSize, ' ');
       return text;
       break;
       //credit pad with 0's to the left
     case 'c':
       size = 9;
       padSize = size - textSize;
       text.insert(text.begin(), padSize, '0');
       return text;
       break;
       //price pad with 0's to the left
     case 'p':
       size = 6;
       padSize = size - textSize;
       text.insert(text.begin(), padSize, '0');
       std::cout << "text = " << text << ".\n";
       return text;
       break;
       //number of tickets pad with 0's to the left
     case 't':
       size = 3;
       padSize = size - textSize;
       text.insert(text.begin(), padSize, '0');
       return text;
       break;
       //status never pad
     case 's':
       size = 0;
       return text;
       break;
    }
  }

  /**
  * Writes the transaction to the transaction file
  * @param  Nothing.
  * @return Nothing.
  */
  void writeToFile()
  {
    std::ofstream transactionFile("transaction.txt", std::ios::app);

    if(!transactionFile){
      std::cout << "Error transaction file was not created! \n";
      return;
    }

    if(transactionFile){
      if (code == "10"){
        //change int to string for pad function
        std::stringstream precisionValue;
        precisionValue << std::setprecision(6);
        precisionValue << balance;
        auto credit = std::to_string(balance);
        transactionFile << pad(code, 's');
        transactionFile << ' ';
        transactionFile << pad(name, 'u');
        transactionFile << ' ';
        transactionFile << pad(status, 's');
        transactionFile << ' ';
        transactionFile << (credit);
        transactionFile << '\n';
        mainMenu();
        return;
      } else if (code == "01"){
      //change int to string to use in pad function
      std::stringstream precisionValue;
      precisionValue << std::setprecision(6);
      precisionValue << userCredit;
      auto credit = std::to_string(userCredit);
    transactionFile << pad(code, 's');
    transactionFile << ' ';
    transactionFile << pad(newUser, 'u');
    transactionFile << ' ';
    transactionFile << (newUserType);
    transactionFile << ' ';
    transactionFile << (credit);
    transactionFile << '\n';
    mainMenu();
    return;
  } else if (code == "02"){
  //change int to string to use in pad function
  std::stringstream precisionValue;
  precisionValue << std::setprecision(6);
  precisionValue << balance;
  auto credit = std::to_string(balance);
transactionFile << pad(code, 's');
transactionFile << ' ';
transactionFile << pad(wantToDelete, 'u');
transactionFile << ' ';
transactionFile << (statusDeleted);
transactionFile << ' ';
transactionFile << (credit);
transactionFile << '\n';
mainMenu();
return;
} else if (code == "03"){
//change int to string to use in pad function
std::stringstream precisionValue;
precisionValue << std::setprecision(6);
precisionValue << pricePerTicket;
auto amountTickets = std::to_string(amountOfTickets);
auto priceTicket = std::to_string(pricePerTicket);
transactionFile << pad(code, 's');
transactionFile << ' ';
transactionFile << pad(eventName, 'e');
transactionFile << ' ';
transactionFile << pad(name, 'u');
transactionFile << ' ';
transactionFile << pad(amountTickets, 't');
transactionFile << ' ';
transactionFile << (priceTicket);
transactionFile << '\n';
mainMenu();
return;
} else if (code == "04"){
      //change int to string to use in pad function
    std::stringstream precisionValue;
    precisionValue << std::setprecision(6);
    precisionValue << pricePerTicket;
    auto amountTickets = std::to_string(ticketAmount);
    auto priceTicket = std::to_string(pricePerTicket);
    transactionFile << pad(code, 's');
    transactionFile << ' ';
    transactionFile << pad(eventName, 'e');
    transactionFile << ' ';
    transactionFile << pad(sellerName, 'u');
    transactionFile << ' ';
    transactionFile << pad(amountTickets, 't');
    transactionFile << ' ';
    transactionFile << (priceTicket);
    transactionFile << '\n';
    mainMenu();
    return;
  } else if (code == "05"){
  //change int to string to use in pad function
std::stringstream precisionValue;
precisionValue << std::setprecision(6);
precisionValue << creditToTransfer;
auto creditTransfer = std::to_string(creditToTransfer);
transactionFile << pad(code, 's');
transactionFile << ' ';
transactionFile << pad(buyerUser, 'u');
transactionFile << ' ';
transactionFile << pad(sellerUser, 'u');
transactionFile << ' ';
transactionFile << (creditTransfer);
transactionFile << '\n';
mainMenu();
return;
} else if (code == "06"){
//change int to string to use in pad function
std::stringstream precisionValue;
precisionValue << std::setprecision(6);
precisionValue << wantToAdd;
auto addedAmount = std::to_string(wantToAdd);
transactionFile << pad(code, 's');
transactionFile << ' ';
transactionFile << pad(creditUser, 'u');
transactionFile << ' ';
transactionFile << (statusDeleted);
transactionFile << ' ';
transactionFile << (addedAmount);
transactionFile << '\n';
mainMenu();
return;
} else if (code == "00"){
      std::stringstream precisionValue;
      precisionValue << std::setprecision(6);
      precisionValue << balance;
      auto credit = std::to_string(balance);
      transactionFile << pad(code, 's');
      transactionFile << ' ';
      transactionFile << pad(name, 'u');
      transactionFile << ' ';
      transactionFile << pad(status, 's');
      transactionFile << ' ';
      transactionFile << (credit);
      transactionFile << '\n';
      transactionFile.close();
      logout();
      return;
    }
  }
}
