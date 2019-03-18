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


public class Tickets {
    public ArrayList<String> parseTixList= new ArrayList<String>();
    public void parseTixFile(String tixDirectory, ArrayList<String> updatedParseTixList) throws IOException{
        BufferedReader reader;
        try {
            reader = new BufferedReader( new FileReader(tixDirectory));
            String line = reader.readLine();
            while( line!= null){
                parseTixList.add(line);
                line = reader.readLine();
            }
            reader.close();
            updatedParseTixList= parseTixList;
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }
    public boolean checkBuyTixValid(int tixQtyNeeded, float userCredit, String eventSellerName, ArrayList<String> updatedParseTixList){
        boolean buyTrancValid = false;
       
        for ( int i = 0; i < updatedParseTixList.size(); i++){
            String eventNameinTixFile= null;
            eventNameinTixFile = updatedParseTixList.get(i);
            if (eventNameinTixFile.contains(eventSellerName)){
                
                int tixQtyInFile = getQty(eventSellerName, updatedParseTixList);
                int tixPrice = getTixPrice(eventSellerName, updatedParseTixList);
                
                
                if ((tixQtyNeeded > tixQtyInFile) && (userCredit< (tixQtyInFile*tixPrice)) ){
                    System.out.println("There is not enough tickets to sell to the customer");
                    break; //maybe we should not use break?
                }
                
                else if ((tixQtyNeeded < tixQtyInFile) && (userCredit> (tixQtyInFile*tixPrice))){
                    buyTrancValid= true;    
            }    
            }
        }
       return buyTrancValid; 
    }
    public void editTixTextFile(boolean buyTranValid, String dailyTranscFile,ArrayList<String> updatedParseTixList){
        if(buyTranValid == true){
            updatedParseTixList.add(dailyTranscFile);
        }
    }
    public void checkNegTix(ArrayList<String> updatedParseTixList){
        for ( int i = 0; i < updatedParseTixList.size(); i++){
            String eventNameinTixFile= null;
            int tixStartIndex= 35;
            eventNameinTixFile = updatedParseTixList.get(i);
             int j = 3;
                while(j>0){
                    
                    if (eventNameinTixFile.charAt(35) == '0'){
                        j--;
                        tixStartIndex++;
                    }
                    else{
                        j= 0; //might have error here
                    }     
                }
             int tixQtyInFile = Integer.parseInt(eventNameinTixFile.substring(tixStartIndex,38));
             if (tixQtyInFile < 0){
                 System.out.println("error Message");
             } 
            
          }
    }
    public int getQty(String eventSellerName, ArrayList<String> updatedParseTixList){
         int tixStartIndex= 35;
         int tixQtyInFile = 0;
          for ( int i = 0; i < updatedParseTixList.size(); i++){
            String eventNameinTixFile= null;
            eventNameinTixFile = updatedParseTixList.get(i);
            if (eventNameinTixFile.contains(eventSellerName)){
                int j = 3;
                while(j>0){
                    
                    if (eventNameinTixFile.charAt(35) == '0'){
                        j--;
                        tixStartIndex++;
                    }
                    else{
                        j= 0; //might have error here
                    }     
                    
                }
                tixQtyInFile = Integer.parseInt(eventNameinTixFile.substring(tixStartIndex,38));
                return tixQtyInFile;
              }
           
   
          } 
          return tixQtyInFile;
       }
    public int getTixPrice (String eventSellerName, ArrayList<String> updatedParseTixList){
        int priceStartIndex= 39;
         int tixPrice = 0;
          for ( int i = 0; i < updatedParseTixList.size(); i++){
            String eventNameinTixFile= null;
            eventNameinTixFile = updatedParseTixList.get(i);
            if (eventNameinTixFile.contains(eventSellerName)){
                int k = 6;
                while(k>0){
                    
                    if (eventNameinTixFile.charAt(39) == '0'){
                        k--;
                        priceStartIndex++;
                    }
                    else{
                        k= 0; //might have error here
                    }     
                }
                tixPrice = Integer.parseInt(eventNameinTixFile.substring(priceStartIndex,44));
                return tixPrice;
              }
          }
        return tixPrice;
    }
}