import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;
public class AccountsTest {
	@Test
	public void test() {
		Accounts1 account = new Accounts1();
		assertEquals("user01", account.getUserName());
		//assertEquals("user03", account.getUserName());
	}
	public void test2() {
		Accounts1 account = new Accounts1();
		Accounts1 account2 = new Accounts1();
		assertEquals("user02", account.getSellerUserNameRefund("transactionFile.txt"));
		assertEquals("user03", account.getSellerUserNameRefund("transactionFile.txt"));
	}
	public void test3() {
		Accounts1 account = new Accounts1();
		Accounts1 account2 = new Accounts1();
		assertEquals(false, account.uniqueUserNameCheck("user01", "transactionFile.txt"));
		assertEquals(true, account.uniqueUserNameCheck("user05", "transactionFile.txt"));
	}
	
}