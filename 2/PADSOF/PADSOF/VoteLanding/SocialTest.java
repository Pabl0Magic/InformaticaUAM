package VoteLanding;

import static org.junit.Assert.*;

import org.junit.Test;

import VoteLanding.Social.ScopeProject;

/**
 * Test for Social class with Junit
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class SocialTest {

	@Test
	public void testGetTargetGroup() {
		Social s1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		String target = s1.getTargetGroup();
		assertEquals("Children", target);
	}
	@Test
	public void testGetScope() {
		Social s1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		ScopeProject scope = s1.getScope();
		assertEquals(ScopeProject.National, scope);
	}
}
