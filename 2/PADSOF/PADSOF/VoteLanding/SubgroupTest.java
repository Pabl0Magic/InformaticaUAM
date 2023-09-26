package VoteLanding;

import static org.junit.Assert.*;

import org.junit.Test;

/**
 * Test for Subgroup class with Junit
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class SubgroupTest {
	
	private static User Pablo = new User("Pablo", "1234A", "P");;
	
	@Test
	public void testGetParent() {
		 Group g1 = new Group("Neighborhood","Improve conditions for our street", Pablo);
		 Subgroup sg1 = new Subgroup("Swimming pool", "Try to have a swimming pool", Pablo, g1, 1);
		 
		 Group g2 = sg1.getParent();
		 assertEquals(g2, g1);
	}

	@Test
	public void testGetLevel() {
		Group g1 = new Group("Neighborhood","Improve conditions for our street", Pablo);
		Subgroup sg1 = new Subgroup("Swimming pool", "Try to have a swimming pool", Pablo, g1, 1);
		 
		int level = sg1.getLevel();
		assertEquals(1, level);
	}

}
