/**
* Implementation of the buying and selling of tickets.
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
    * This is the buy function which will first check if the user has enough
    * balance to purchase a ticket, as well as if they have permission to
    * purchase one. Then it will ask the user which ticket they want, check the
    * number of available tickets for sale and go through with the transaction
    * and subsequently subtract funds from the user and notify the user of their
    * new balance.
    *
    * @param  Nothing.
    * @return Nothing.
    */
    void buy()
    {
      std::string userChoice;
      char input;

        if(balance <= 0){
          std::cerr << "Invalid Funds! \n";
          mainMenu();
        } else if(status == "SS"){
          std::cerr << "You do not have permission to buy! \n";
          mainMenu();
        } else {
          int count = 0;
          std::string lines;
          std::ifstream currentTicketFilee(availableTickets);
          while (getline(currentTicketFilee, lines)){
            count++;
          }
          std::cout << "You have $" << balance << " balance in your account. \n";
          std::cout << "Here are the current tickets for sale: \n";
          readFromFile();
          currentTicketFilee.close();


          eventIn:std::cout << "Enter which option you would like to buy tickets from :";
          std::cin >> userChoice;
          std::ifstream currentTicketFile(availableTickets);
          if(currentTicketFile) {
            while (std::getline(currentTicketFile, line))
            {
              std::replace(line.begin(), line.end(), ' ', ' ');
              std::stringstream ss(line);
              ss >> eventName;
              if(eventName == userChoice){
                ss >> sellerName;
                ss >> amountOfTickets;
                ss >> pricePerTicket;
                currentTicketFile.close();
                goto quantIn;
            }
          }
          std::cerr << "Event doesn't exist, try again \n";
          goto eventIn;
      }


            quantIn: std::cout << "Enter the amount of tickets you wish to buy: ";
              std::cin >> ticketAmount;
              //quantity cannot exceed maximum
            if(ticketAmount > amountOfTickets) {
              std::cout << "Error: ticket quantity cannot exceed tickets available." << "\n";
              goto quantIn;
            }

            confirmIn: std::cout << "Are you sure you want to buy these tickets? (Y/N):";
              std::cin >> input;
            if(input == 'Y' || input =='y'){
              std::cout << "Tickets were purchased \n";
              writeToFile();
              return;
            } else if (input == 'N' || input == 'n'){
              std::cout << "Sale aborted! \n";
              mainMenu();
              return;
            } else {
              std::cerr << "Invalid input, try again \n";
              goto confirmIn;
            }
          }

    }

    /**
    * Sell ticket(s) to an event
    * @param  Nothing.
    * @return Nothing.
    */
    void sell() {

      if(status == "BS"){
        std::cerr << "You do not have permission to sell! \n";
        mainMenu();
      }

    	//take in event name
    	eventIn: std::cout << "Enter the event name: ";
    	std::cin >> eventName;

    	//getline(std::cin,eventName);

    	// if the name of the event is too long don't allow it.
    	if(eventName.length() > 25) {
    		std::cout << "Error: event name cannot exceed 25 characters." << "\n";
    		goto eventIn;
    	}

    	//take in ticket price
    	priceIn: std::cout << "Enter the ticket price: ";
        std::cin >> pricePerTicket;
    	if(pricePerTicket > 999.99) {
    		std::cout << "Error: ticket price cannot exceed 999.99" << "\n";
    		goto priceIn;
    	}

    	//take in quantity of tickets
    	amountIn: std::cout << "Enter the amount of tickets: ";
        std::cin >> amountOfTickets;
    	if(amountOfTickets > 100) {
    		std::cout << "Error: ticket quantity cannot exceed 100." << "\n";
    		goto amountIn;
    	}
      std::cout << "Tickets have been put up for sale" << "\n";
      std::cout << "Eventname = " << eventName << " price per ticket = $" << pricePerTicket << " amount of ticks = " << amountOfTickets << "\n";
      writeToFile();
      return;
    }
