import java.io.*;

public class Accounts{

    public static void Accounts(){
        /**
         * Handles user accounts
         */

         private String oldUserAccFileDest;
         private String newUserAccFileDest;
         private int transCode;

         /**
          * Uses transaction file and account file to check if username is unique
          *
          * @param   transCode
          * @param   mergeTransFile The merged transaction file
          * @param   oldUserAccFile The old user account file
          * @return  Nothing
          */
          public static void uniqueUsernameCheck(int transCode, File mergeTransFile, File oldUserAccFile){
              //TODO: Check to see if the username is unique
          }

        /**
         * Merges the transaction file into the current Accounts file
         *
         * @param   transCode
         * @param   mergeTransFile The merged transaction file
         * @param   oldUserAccFile The old user account file
         * @return  Nothing
         */
         public mergeUserAccount(int transCode, File mergeTransFile, File oldUserAccFile){
              //TODO: Merge the user account
         }
    }
}
