/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package phase4;

import java.io.IOException;
import java.util.ArrayList;

/**
 *
 * @author YouCun
 */
public class Phase4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        String dirName= "";
        String outPutFile= "";
        String tixDirectory= "";
        String accDirectory= "";
        ArrayList<String> trancFileList = null;
        ArrayList<String> tixFileList = null;
        ArrayList<String> accFileList = null;
        
        Tickets tixObj= new Tickets();
        Accounts1 accObj = new Accounts1();
        
        // TODO code application logic here
        Files1.mergeTransFiles(dirName, outPutFile);
        tixObj.parseFile(tixDirectory, tixFileList);
        tixObj.parseFile(accDirectory, accFileList);
        tixObj.parseFile(outPutFile, trancFileList);
        
        //reading through each line of merged daily transaction file
        for( int i = 0; i < trancFileList.size(); i ++){
            String transCode= "";
            String entryWithoutTransCode= "";
           String newUserName= "";
           String entryInTransFile = trancFileList.get(i); //entry of TransFile
           transCode= entryInTransFile.substring(0,2);
           
           
           
           switch(transCode){
               case "01":
                   
                   entryWithoutTransCode= entryInTransFile.substring(2,31);
                   newUserName = accObj.getUserName(entryInTransFile);
                   boolean uniqueNameTrue = accObj.uniqueUserNameCheck(newUserName, accFileList);
                   accObj.addNewUserToAccFile(uniqueNameTrue, entryWithoutTransCode, accFileList);
                   break;
               case "02":
                   newUserName = accObj.getUserName(entryInTransFile);
                   accObj.deleteUser(newUserName, accFileList);
                   break;
               case "03":
                   
                   
                   break;
               case "04":
                   entryWithoutTransCode= entryInTransFile.substring(2,31);
                   int tixQtyToBuy = accObj.getTixNeeded(entryInTransFile);
                   float buyerCredit= accObj.getCreditFromAccFile(entryWithoutTransCode);
                   String eventSellerName= entryInTransFile.substring(3,36);
                   String lineInTixFile= tixObj.getCorrespondingLineInParseTixFile(eventSellerName, accFileList);
                   tixObj.checkBuyTixValid(tixQtyToBuy, buyerCredit,lineInTixFile);
                   
                   
                   
                   break;
                   
               case "05":
                   
                   
                   break;
                   
               case "06":
                   
                   
                   
                   break;
               
               case "00":
                   
                   
                   
                   break;
                  
           }
        }
    }
    
}
