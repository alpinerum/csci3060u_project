/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package phase4;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.*;
public class Accounts1 {
    //this method gets the username from a normal daily Transaction file
    public String getUserName(String newUserAccEntry){ //assuming we have converted the .output file into a string
        int i = 15;
        int firstChar =3;
        int endChar= 0;
        String newUserName;
        while(i>0){
            char firstCharName = newUserAccEntry.charAt(firstChar);
            char neighbourCharName= newUserAccEntry.charAt(firstChar+1);
            if ((firstCharName==' ') && (neighbourCharName==' ')){
                endChar= firstChar-1;
                i=0;
            }
            else{
                i--;
                firstChar++;
            }
        }
        return newUserName = newUserAccEntry.substring(3,(endChar+1));
    }
    
    public String getSellerUserNameRefund(String refundOutputEntry){ //this mtd gets the seller username,for refund .output file
        int i = 15;
        int firstChar =19;
        int endChar= 0;
        String sellerUserName;
        while(i>0){
            char firstCharName = refundOutputEntry.charAt(firstChar);
            char neighbourCharName= refundOutputEntry.charAt(firstChar+1);
            if ((firstCharName==' ') && (neighbourCharName==' ')){
                endChar= firstChar-1;
                i=0;
            }
            else{
                i--;
                firstChar++;
            }
        }
        return sellerUserName = refundOutputEntry.substring(19,(endChar+1));
    }
    
    public boolean uniqueUserNameCheck(String newUserName, ArrayList<String> oldAccTixFile){ //gets username from.output file and check 
                                                                                            //check against accountfile
        for ( int i = 0; i < oldAccTixFile.size();i++ ){
            String entryInOldAccFile= oldAccTixFile.get(i);
            if(entryInOldAccFile.contains(newUserName)){
                System.out.println("The newly created username already exist!!");
                return false;
            }
        }
        System.out.println("The newly created username is unique!!");
        return true;
        //might need to delete the output file that is not valid?
    } 
    
    public float getUserCreditFromOutputFile(String newUserAccEntry){ //use this if ID code is 01,02,06,00
        //get the credit from the .output file
        int userCreditIndex= 22;
        int k = 9;
        float userCredit= 0;
        while( k >0){
            if (newUserAccEntry.charAt(22)==0){
                k--;
                userCreditIndex++;
            }
            else{
                k = 0;
            }
            
        }
       return userCredit= Float.parseFloat(newUserAccEntry.substring(userCreditIndex,31));
    }
    
    public void appendRefundCredit(String sellerName, String buyerName,float refundCredit, ArrayList<String> updatedParseAccList){
      
        String sellerNameinAcc= getCorrespondingLineInParseAccFile(sellerName,updatedParseAccList);//getting output line in accfile for seller
        String buyerNameinAcc= getCorrespondingLineInParseAccFile(buyerName,updatedParseAccList);
        float sellerCreditinAccFile= getCreditFromAccFile(sellerNameinAcc);
        float buyerCreditInAccFile= getCreditFromAccFile(buyerName);
        String newSellerCredit= Float.toString(sellerCreditinAccFile - refundCredit);
        String newBuyerCredit= Float.toString(buyerCreditInAccFile + refundCredit);  // assume credit is not negative value and all the rules in fe are checked there
        String buyerAppendFormat= convertCreditFormat(newBuyerCredit);//
        String sellerAppendFormat= convertCreditFormat(newSellerCredit);
        editCreditInAccFile(updatedParseAccList,sellerName,  sellerAppendFormat);
        editCreditInAccFile(updatedParseAccList,buyerName, buyerAppendFormat);       
                
        

    }
    
    public float getCreditFromAccFile(String lineInAccParseFile){
        int userCreditIndex= 19;
        int k = 9;
        float userCredit= 0;
        while( k >0){
            if (lineInAccParseFile.charAt(19)==0){
                k--;
                userCreditIndex++;
            }
            else{
                k = 0;
            }
            
        }
       return userCredit= Float.parseFloat(lineInAccParseFile.substring(userCreditIndex,28));
    }
    
      
    public String getCorrespondingLineInParseAccFile(String userNameToSearch, ArrayList<String> updatedParseAccList){
           String lineInAccParseFile;
           for (int i = 0; i < updatedParseAccList.size(); i ++){
               lineInAccParseFile= updatedParseAccList.get(i);
               if ( lineInAccParseFile.contains(userNameToSearch)){
                   return lineInAccParseFile;
               }
              
        }
           return null;
    }
    
    public String convertCreditFormat(String creditValue){ //convert the credit from str to the correct format listed in the proj
        String creditValueToAppend= "";
        if (creditValue.length()< 9){
            for ( int i = 0; i < (3-creditValue.length()); i ++){
                            creditValueToAppend+='0';
                            creditValueToAppend+=creditValue;
                        }
               }else{
                         creditValueToAppend+=creditValue;
                    }
        return creditValueToAppend;
        }
    public void editCreditInAccFile(ArrayList<String> updatedParseAccList, String userNametoSearch, String creditToAppend){
        for(int i = 0; i < updatedParseAccList.size(); i++){
                    
               if ( updatedParseAccList.get(i).contains(userNametoSearch)){
                   String newUserrAccLineToRemove= updatedParseAccList.get(i);
               
                   String userAccLineAdd = updatedParseAccList.get(i).substring(0, 19) + creditToAppend;
                   updatedParseAccList.remove(newUserrAccLineToRemove);
                   updatedParseAccList.add(userAccLineAdd);
                        
               }
            }
        }
    
    public void deleteUser(String userNameToDelete,ArrayList<String> updatedParseAccList ){
        for(int i = 0; i < updatedParseAccList.size(); i++){
            if ( updatedParseAccList.get(i).contains(userNameToDelete)){
                String deleteUserEntry= updatedParseAccList.get(i);
                updatedParseAccList.remove(deleteUserEntry);
            } 
        }
    }  
    
    public void addNewUserToAccFile(boolean userNameUnique,String newUserTransFile, ArrayList<String> updatedParseAccList){
        if (userNameUnique== true){
            updatedParseAccList.add(newUserTransFile);
            //note, for this mtd, we need to pass in the daily transac file of the newly create acc as a String.
        }
    }
    
    public float addCreditToUser(float userCredit, float initialCreditInAccFile){
        if (userCredit > 1000.00){
            System.out.println("Maximum Top up credit is 1000.000");
            return 0;
        }
        else{
            float newCredit= userCredit+initialCreditInAccFile;
            return newCredit;
            
        }
            
            
       }
    public float creditForBuyTrans(boolean buyTranValid, float buyerCredit,int tixPrice, int tixQtyNeeded){
        float newBuyCreditTrans = 0;
        if ( buyTranValid == true){
            //int tixQtyNeeded= tixQtyInFile -tixQtyAfterTrans;
            newBuyCreditTrans = buyerCredit - (tixQtyNeeded*tixPrice);
        }
        System.out.println("Transcation is not valid");
        
        return newBuyCreditTrans;
    }
    public float creditForSellTrans(boolean buyTranValid, float sellerCredit, int tixPrice, int tixQtyNeeded){
        float newSellCreditTrans = 0;
        if ( buyTranValid == true){
        newSellCreditTrans = sellerCredit + (tixQtyNeeded*tixPrice);
        }
        System.out.println("Transcation is not valid");
        
        return newSellCreditTrans;
    }
    
    public int tixQtyAfterTrans(String sellDailyTrans){ //for buy, its the no. of tix buyer wants to buy
        int tixQtyStartIndex = 38;
        int j = 3;
                while(j>0){
                    
                    if (sellDailyTrans.charAt(38) == '0'){
                        j--;
                        tixQtyStartIndex++;
                    }
                    
                    else{
                        j= 0; //might have error here
                    }     
                    
                }
                int tixQtyNeeded = Integer.parseInt(sellDailyTrans.substring(tixQtyStartIndex,41));
                return tixQtyNeeded;
        
    }
    
    public int getTixNeeded ( String lineInAccParseFile){
        int tixStartIndex= 37;
         int tixQtyInTranFile = 0;
            if (lineInAccParseFile != null){
                int j = 3;
                while(j>0){
                    
                    if (lineInAccParseFile.charAt(37) == '0'){
                        j--;
                        tixStartIndex++;
                    }
                    else{
                        j= 0; //might have error here
                    }     
                    
                }
                tixQtyInTranFile = Integer.parseInt(lineInAccParseFile.substring(tixStartIndex,41));
                return tixQtyInTranFile;
              }
           System.out.println("no such event found"); 
          return tixQtyInTranFile;
    }
    
    
}
