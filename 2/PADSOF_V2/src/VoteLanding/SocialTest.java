package VoteLanding;

import static org.junit.Assert.*;

import org.junit.Test;

import VoteLanding.Social.ScopeProject;

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
