package VoteLanding;

import static org.junit.Assert.*;

import java.util.List;

import org.junit.Test;

import VoteLanding.Project.Status;
import VoteLanding.Social.ScopeProject;

public class ProjectTest {
	
	private static User Pablo = new User("Pablo", "1234A", "P");
	private static User Miguel = new User("Miguel", "5678B", "M");
	private static User Carlos = new User("Carlos", "9012C", "C");
	
	@Test
	public void testGetId() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 324234);
		
		long id = p1.getId();
		assertEquals(4, id);
	}

	@Test
	public void testSetId() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 54645654);
		
		p1.setId();
		long id =p1.getId();
		assertEquals(6, id);
	}

	@Test
	public void testGetName() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 348939);
		
		String name = p1.getName();
		assertEquals("Park", name);
	}

	@Test
	public void testGetDesc() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 344545);
		
		String desc = p1.getDesc();
		assertEquals( "We will create a park for the children.", desc);
	}

	@Test
	public void testGetVotesRequired() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.",2434343);
		
		p1.setVotesRequired(15);
		int vote = p1.getVotesRequired();
		assertEquals(15, vote);
	}

	@Test
	public void testSetVotesRequired() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		p1.setVotesRequired(34);
		int vote = p1.getVotesRequired();
		assertEquals(34, vote);
	}

	@Test
	public void testGetNumVotes() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		p1.setNumVotes(23);
		int vote = p1.getNumVotes();
		assertEquals(23, vote);
		
	}

	@Test
	public void testSetNumVotes() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		p1.setNumVotes(45);
		int vote = p1.getNumVotes();
		assertEquals(45, vote);		
	}

	@Test
	public void testGetStatus() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		p1.setStatus(Status.Approved);
		Status stat = p1.getStatus();
		assertEquals(Status.Approved, stat);
	}

	@Test
	public void testSetStatus() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
	
		p1.setStatus(Status.Rejected);
		Status stat = p1.getStatus();
		assertEquals(Status.Rejected, stat);
	}

	@Test
	public void testGetDaysLeft() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		p1.setDaysLeft(30);
		int days = p1.getDaysLeft();
		assertEquals(30, days);
	}
	
	@Test
	public void testSetDaysLeft() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		p1.setDaysLeft(30);
		int days = p1.getDaysLeft();
		assertEquals(30, days);
	}

	@Test
	public void testUpdateVotes() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addFollower(Miguel);
		p1.voteProjectIndv(Miguel);
		p1.voteProjectGroup(g1);
		g1.addFollower(Carlos);
		int votes = p1.getNumVotes();
		assertEquals(2, votes);
	}

	@Test
	public void testVoteProjectIndv() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		
		p1.voteProjectIndv(Carlos);
		List<User> indiv = p1.getVotedIndiv();
		boolean cont = indiv.contains(Carlos);
		boolean contWrong = indiv.contains(Miguel);
		assertTrue(cont);
		assertFalse(contWrong);
	}

	@Test
	public void testVoteProjectGroup() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addFollower(Carlos);
		g1.addFollower(Miguel);
		p1.voteProjectGroup(g1);
		List<Group> groupVotes = p1.getVotedGroup();
		boolean cont = groupVotes.contains(g1);
		assertTrue(cont);
	}

	@Test
	public void testCheckExpired() {
		Project p1 = new Social("Children", ScopeProject.National, "Park", "We will create a park for the children.", 100);
		int expired = 0;
		int noExpired = 10;
		boolean expiration;
		
		for (int i = 0; i < 2; i++) {
			if (i == 0) {
				p1.setDaysLeft(expired);
				expiration = p1.checkExpired();
				assertTrue(expiration);
			} else {
				p1.setDaysLeft(noExpired);
				expiration = p1.checkExpired();
				assertFalse(expiration);
			}
		}
	}

}
