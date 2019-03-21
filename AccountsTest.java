import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;
public class AccountsTest {
	@Test
	public void getUserNameTest() {
		Accounts1 account = new Accounts1();
		assertEquals("user01", account.getUserName());
		//assertEquals("user03", account.getUserName());
	}
	public void getSellerUserNameRefundTest() {
		Accounts1 account = new Accounts1();
		Accounts1 account2 = new Accounts1();
		assertEquals("user02", account.getSellerUserNameRefund("transactionFile.txt"));
		assertEquals("user03", account.getSellerUserNameRefund("transactionFile.txt"));
	}
	public void uniqueUserNameCheckTest() {
		Accounts1 account = new Accounts1();
		Accounts1 account2 = new Accounts1();
		assertEquals(false, account.uniqueUserNameCheck("user01", "transactionFile.txt"));
		assertEquals(true, account.uniqueUserNameCheck("user05", "transactionFile.txt"));
	}
	public void getUserCreditFromOutputFileTest() {
		Accounts1 account = new Accounts1();
		account.addCreditToUser(20.0, 0.0);
		assertEquals(20.0, getUserCreditFromOutputFile("user01"));
	}
	
	public void  getCreditFromAccFileTest() {
		Accounts1 account = new Accounts1();
		account.addCreditToUser(20.0, 0,0);
		assertEquals(20.0, getCreditFromAccFile("accountFile.txt"));
	}
	public void convertCreditFormatTest() {
		Accounts1 account = new Accounts1();
		account.addCreditToUser(10.0, 0.0);
		assertEquals(10.0, convertCreditFormat("10.0"));
	}
	public void getCorrespondingLineInParseAccFileTest() {
		Accounts1 account = new Accounts1();
		assertEquals("accountFile.txt", "accountFile.txt");
	}
	public void editCreditInAccFileTest() {
		Accounts1 account = new Accounts1();
		ArrayList<String> updatedParseAccList = [["user01", "0.0"], ["user02", "0.0"]];
		account.editCreditInAccFile(updatedParseAccList, "user01", "19.0");
		assertEquals("19.0", getCreditFromAccFile("accountFile.txt"));
	}
	public void deleteUserTest() {
		Accounts1 account = new Accounts1();
		ArrayList<String> updatedParseAccList = [["user01"], ["user02"]];
		account.deleteUser("user01", updatedParseAccList);
		assertEquals([["user02"]], updatedParseAccList);
	}
	public void addCreditToUserTest() {
		Accounts1 account = new Accounts1();
		account.addCreditToUser(19.00, 0.0);
		assertEquals(19.00, getUserCreditFromOutputFile("user01"));)
	}
	public void creditForBuyTransTest() {
		Accounts1 account = new Accounts1();
		assertEquals(9.0, account.creditForBuyTrans(true, 19.0, 10, 1));	
	}
	public void creditForSellTransTest() {
		Accounts1 account = new Accounts1();
		assertEquals(30.0, account.creditForSellTrans(true, 20.0, 10, 1));
	}
	public void tixQtyAfterTransTest() {
		Accounts1 account = new Accounts1();
		assertEquals(10, account.tixQtyAfterTrans("11"));
	}
	public void getTixNeededTest() {
		Accounts1 account = new Accounts1();
		assertEquals(10, account.getTixNeeded("accountFile.txt"));
	}
	
}