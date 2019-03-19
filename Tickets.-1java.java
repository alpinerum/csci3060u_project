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
    
    public void parseFile(String tixDirectory, ArrayList<String> updatedParseTixList) throws IOException{
        BufferedReader reader;
        ArrayList<String> parseTixList= new ArrayList<String>();
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
    public boolean checkBuyTixValid(int tixQtyNeeded, float userCredit,String lineInTixParseFile){
        boolean buyTrancValid = false;
       
        
            int tixQtyInFile = getQty(lineInTixParseFile);
            int tixPrice = getTixPrice(lineInTixParseFile);
                
                
                if ((tixQtyNeeded > tixQtyInFile) && (userCredit< (tixQtyNeeded*tixPrice)) ){
                    System.out.println("There is not enough tickets to sell to the customer");
                    //break; //maybe we should not use break?
                }
                else if ((tixQtyNeeded < tixQtyInFile) && (userCredit> (tixQtyNeeded*tixPrice))){
                    buyTrancValid= true;    
            }    
         
        
       return buyTrancValid;
       
    }
    public void editTixTextFile(boolean buyTranValid,int tixQtyNeeded, String eventSellerName,String lineInTixParseFile ,ArrayList<String> updatedParseTixList){
        String newTixLineToRemove;
        if(buyTranValid == true){
                    String newTixQtyAvail= Integer.toString(getQty(lineInTixParseFile) - tixQtyNeeded);
                    String newTixQtyAppend= "";
                    if ( newTixQtyAvail.length()< 3){
                        for ( int i = 0; i < (3-newTixQtyAvail.length()); i ++){
                            newTixQtyAppend+='0';
                        }
                        newTixQtyAppend+=newTixQtyAvail;
               }else{
                        newTixQtyAppend+=newTixQtyAvail;
                    }
                for(int i = 0; i < updatedParseTixList.size(); i++){
                    
               if ( updatedParseTixList.get(i).contains(eventSellerName)){
                   newTixLineToRemove= updatedParseTixList.get(i);
               
                   String x = updatedParseTixList.get(i).substring(0, 35) + newTixQtyAppend + updatedParseTixList.get(i).substring(38, 45);
                   updatedParseTixList.remove(newTixLineToRemove);
                   updatedParseTixList.add(x);
                        
               }
               
                
        } 
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
    public int getQty(String lineInTixParseFile){
         int tixStartIndex= 35;
         int tixQtyInFile = 0;
            if (lineInTixParseFile != null){
                int j = 3;
                while(j>0){
                    
                    if (lineInTixParseFile.charAt(35) == '0'){
                        j--;
                        tixStartIndex++;
                    }
                    else{
                        j= 0; //might have error here
                    }     
                    
                }
                tixQtyInFile = Integer.parseInt(lineInTixParseFile.substring(tixStartIndex,38));
                return tixQtyInFile;
              }
           System.out.println("no such event found"); 
          return tixQtyInFile;
       }
    public int getTixPrice (String lineInTixParseFile){
        int priceStartIndex= 39;
         int tixPrice = 0;
                int k = 6;
                if(lineInTixParseFile != null){
              
                while(k>0){
                    
                    if (lineInTixParseFile.charAt(39) == '0'){
                        k--;
                        priceStartIndex++;
                    }
                    else{
                        k= 0; //might have error here
                    }     
                }
                tixPrice = Integer.parseInt(lineInTixParseFile.substring(priceStartIndex,44));
                return tixPrice;
              }
                else{
                    System.out.println("no such event found");
          }
        return tixPrice;
    }
    
    public String getCorrespondingLineInParseTixFile(String eventSellerName, ArrayList<String> updatedParseTixList){
           String lineInTixParseFile;
           for (int i = 0; i < updatedParseTixList.size(); i ++){
               lineInTixParseFile= updatedParseTixList.get(i);
               if ( lineInTixParseFile.contains(eventSellerName)){
                   return lineInTixParseFile;
               }
              
        }
           return null;
    }
}
