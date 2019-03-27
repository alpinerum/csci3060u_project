/**
* Implementation of all the admin functions; create, deleteUser, addCredit, and
* returnTicket. For each of the functions, the logged in user's status is checked
* and if it is admin, then they are given permission to use the functions
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

/**
* The create function creates a user that has a name, a status, and a set amount
* of credits. First the system checks if a user is logged in, then it checks if
* they are an admin. Once the status is confirmed the function will prompt the
* user to enter the username of the new account, its status, and the amount of
* credit it recieves. Checks are done to make sure the username is not already
* in use and if it complies with the 15 character limit. The credit value entered
* is also limited to 1000.00.
*
* @param  Nothing.
* @return Nothing.
*/
void create()
{
    std::string checkUsername;


    if(!isLoggedIn){
      std::cerr << "you must login first! \n";
      mainMenu();
      return;
    }

    if(code == "01") {
      if(status != "AA"){
        std::cerr << "you don't have privilege to do this \n";
        mainMenu();
        return;
      }

      if(status == "AA"){
      createIn: std::cout << "To create a user, please enter a valid username: \n";
      std::cin >> checkUsername;
        std::ifstream userLoginFile(currentUserAccounts);
        if(userLoginFile) {
          while (std::getline(userLoginFile, line))
          {
            std::replace(line.begin(), line.end(), ' ', ' ');
            std::stringstream ss(line);
            ss >> name;
            if(name == checkUsername){
              std::cout << "This username is already in use, please try again: \n";
              goto createIn;
            }
          }
          userLoginFile.close();
        }

        if(checkUsername.length() > 15){
          std::cout << "The username must be 15 characters or less, please try again: \n";
          goto createIn;
        } else {
          newUser = checkUsername;
        }

      statusIn: std::cout << "Please enter the type of user (AA, FS, BS, or SS) \n";
      std::cin >> newUserType;
      if(newUserType == "AA" || newUserType == "FS" ||
         newUserType == "BS" || newUserType == "SS"){
        goto creditIn;
      } else {
        std::cerr << "Invalid type, try again \n";
        goto statusIn;
      }

      creditIn: std::cout << "Enter the amount of credit to give this user \n";
      std::cin >> userCredit;
      if(userCredit > 999.99 || userCredit < 0){
        std::cerr << "Invalid amount, try again \n";
        goto creditIn;
      }
      std::cout << "User created! name = " << checkUsername << " status = " << newUserType << " credit = $" << userCredit << "\n";
      writeToFile();
      return;
    }
  }
}

/**
* This function deletes a user from the daily transaction file. It first checks
* if a user is logged in, and then checks their status to make sure they are an
* admin. Once that is confirmed, it prompts the user to enter the username of the
* user they wish to delete. If the user does not exist or if the user enters their
* own username, an error message will appear.
*
* @param  username  the current logged in user account
* @return Nothing.
*/
void deleteUser(std::string username)
{
  bool deleted = false;
  std::string deletedUser;

  if(!isLoggedIn){
    std::cerr << "you must login first! \n";
    mainMenu();
    return;
  }

  if(code == "02") {
    if(status != "AA"){
      std::cerr << "you don't have privilege to do this! \n";
      mainMenu();
      return;
    }
    if(status == "AA"){
    deleteIn: std::cout << "Which user would you like to delete? \n";
    while(!deleted){
      std::cin >> wantToDelete;
      if(wantToDelete == username){
        std::cout << "You cannot delete a currently logged in account. Try again. \n";
        goto deleteIn;
      }
      std::ifstream userLoginFile(currentUserAccounts);
      if(userLoginFile) {
        while (std::getline(userLoginFile, line))
        {
          std::replace(line.begin(), line.end(), ' ', ' ');
          std::stringstream ss(line);
          ss >> name;
          if(wantToDelete == name){
            std::cout << "Success user deleted \n";
            userLoginFile.close();
          writeToFile();
          return;
          }
        }
          userLoginFile.close();
          std::cerr << "Cannot delete user that doesn't exist, try again \n";
          goto deleteIn;
        }
      }
    }
  }
}


/**
* Add credit to the system to allow the user to purchase tickets. First the system
* checks if the user is logged in, and then checks if they are an admin. Once
* confirmed, the user will be prompted to enter the username of the user they
* would like to add credit to. If the user exists, the user is prompted to enter
* the amount of credit to add, which is then checked against that users current
* credit amount to check if it does not go past the 999.99 credit limit.
*
* @param  Nothing.
* @return Nothing.
*/
void addCredit()
{
    float addedCredit;

    if(!isLoggedIn){
      std::cerr << "you must login first! \n";
      mainMenu();
      return;
    }

    if(code == "06") {
      if(status != "AA"){
          std::cerr << "You don't have privilege for this feature! \n";
          mainMenu();
          return;
      }

      if(status == "AA"){
        userIn: std::cout << "Which user would you like to add the credit to? \n";
        std::cin >> creditUser;
        std::ifstream userLoginFile(currentUserAccounts);
        if(userLoginFile) {
          while (std::getline(userLoginFile, line))
          {
            std::replace(line.begin(), line.end(), ' ', ' ');
            std::stringstream ss(line);
            ss >> name;
            if(creditUser == name){
              ss >> status;
              ss >> balance;
              userLoginFile.close();
              goto credit2In;
          }
        }
        std::cerr << "Account doesn't exist, try again \n";
        goto userIn;
    }
      credit2In: std::cout << "How much credit would you like to add? \n";
      while(addedCredit==0){
        std::cin >> wantToAdd;
        if(wantToAdd + balance > 999.99){
          std::cout << "Users cannot have more than $999.99 in their accounts. \n";
          goto credit2In;
        } else {
          addedCredit = wantToAdd + balance;
          std::cout << "username = " << creditUser << " new balance = $" << addedCredit << "\n";
          writeToFile();
          return;
        }
      }
    }
  }
}

/**
* Refund credit from seller to buyer. First checks if user is logged in and they
* are admin. Then asks for buyer name and checks their status to see if they can
* purchase. Asks for seller name and also checks status to see if they can sell.
* Once confirmed, user is prompted for credit amount to transfer and also makes
* sure the 999.99 credit limit is not broken.
*
* @param  Nothing.
* @return Nothing.
*/
void returnTicket()
{


  if(!isLoggedIn){
    std::cerr << "you must login first! \n";
    mainMenu();
    return;
  }

  if(code == "05") {
    if(status != "AA"){
      std::cerr << "you don't have privilege for this! \n";
      mainMenu();
      return;
    }
    if(status == "AA"){
      std::string temp1;
      std::string temp2;
      user2In: std::cout << "Enter the buyers name \n";
      std::cin >> buyerUser;
      std::ifstream userLoginFile(currentUserAccounts);
      if(userLoginFile) {
        while (std::getline(userLoginFile, line))
        {
          std::replace(line.begin(), line.end(), ' ', ' ');
          std::stringstream ss(line);
          ss >> temp1;
          if(buyerUser == temp1){
            ss >> status;
            if(status == "SS"){
              std::cerr << "This user cannot purchase tickets invalid attempt, try again \n";
              goto user2In;
            }
            ss >> balance;
            userLoginFile.close();
            goto user3In;
        }
      }
      std::cerr << "Account doesn't exist, try again \n";
      goto user2In;
  }

  user3In: std::cout << "Enter the sellers name \n";
  std::cin >> sellerUser;
  std::ifstream userLoginFilee(currentUserAccounts);
  if(userLoginFilee) {
    while (std::getline(userLoginFilee, line))
    {
      std::replace(line.begin(), line.end(), ' ', ' ');
      std::stringstream ss(line);
      ss >> temp2;
      if(sellerUser == temp2){
        ss >> status;
        if(status == "BS"){
          std::cerr << "This user cannot sell tickets invalid attempt, try again \n";
          goto user3In;
        }
        userLoginFilee.close();
        if(buyerUser == sellerUser){
          std::cerr << "cannot have same user for buy and sell, try again \n";
          goto user3In;
        }
        goto credit3In;
    }
  }
  std::cerr << "Account doesn't exist, try again \n";
    goto user3In;

}

    credit3In: std::cout << "How much credit would you like to transfer? \n";
      std::cin >> creditToTransfer;
      if(creditToTransfer + balance > 999.99){
        std::cout << "Users cannot have more than $999.99 in their accounts. \n";
        goto credit3In;
      } else {
        balance += creditToTransfer;
        std::cout << "buyer = " << buyerUser << " seller = " << sellerUser << " amount = $" << creditToTransfer << "\n";
        writeToFile();
        return;
      }
    }

  }
}
