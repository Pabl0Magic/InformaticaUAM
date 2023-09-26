package VoteLanding;

import static org.junit.Assert.*;
import org.junit.Test;

/**
 * Test for Administrator class with Junit
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class AdministratorTest {

	@Test
	public void testGetName() {
		Administrator a1 = new Administrator("Admin", "Hello_World");
		
		String admin = a1.getName();
		assertEquals("Admin", admin);
	}

	@Test
	public void testGetPassword() {
		Administrator a1 = new Administrator("Admin", "Hello_World");
		
		String password = a1.getPassword();
		assertEquals("Hello_World", password);
	}
}
