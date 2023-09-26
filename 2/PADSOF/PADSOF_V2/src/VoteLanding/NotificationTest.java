package VoteLanding;

import static org.junit.Assert.*;

import java.time.LocalDate;

import org.junit.Test;

import VoteLanding.Notification.TypeNotification;
import modifiableDates.ModifiableDate;

public class NotificationTest {

	@Test
	public void testGetTitle() {
		Notification n1 = new Notification(TypeNotification.projectAccepted);
		
		n1.setTitle();
		String title = n1.getTitle();
		assertEquals("Project accepted", title);
	}

	@Test
	public void testSetTitle() {
		Notification n1 = new Notification(TypeNotification.projectRejected);
		
		n1.setTitle();
		String title = n1.getTitle();
		assertEquals("Project rejected", title);
	}

	@Test
	public void testGetBody() {
		Notification n1 = new Notification(TypeNotification.projectAccepted);
		
		n1.setBody();
		String body = n1.getBody();
		assertEquals("Your project has been accepted", body);
	}

	@Test
	public void testSetBody() {
		Notification n1 = new Notification(TypeNotification.projectRejected);
		
		n1.setBody();
		String body = n1.getBody();
		assertEquals("Your project has been rejected", body);
	}

	@Test
	public void testSetRead() {
		Notification n1 = new Notification(TypeNotification.projectAccepted);
		
		n1.setRead();
		boolean read = n1.getRead();
		assertTrue(read);	
	}

	@Test
	public void testGetRead() {
		Notification n1 = new Notification(TypeNotification.projectRejected);
		
		boolean read = n1.getRead();
		assertFalse(read);	
	}

	@Test
	public void testGetSentDate() {
		Notification n1 = new Notification(TypeNotification.projectAccepted);
		
		LocalDate date = n1.getSentDate();
		assertEquals(ModifiableDate.getModifiableDate(), date);
	}

}
