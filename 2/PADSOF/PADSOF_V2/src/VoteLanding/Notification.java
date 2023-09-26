package VoteLanding;

import java.time.LocalDate;

import modifiableDates.ModifiableDate;

/**
 * Notification class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class Notification{
    private String title;
    private String body;
    private TypeNotification notification;
    private boolean read = false;
    private LocalDate sentDate;

    public Notification(TypeNotification notification){
        this.notification = notification;
        
        sentDate = ModifiableDate.getModifiableDate();
        setTitle();
        setBody();
    }
    /**
     * 
     * pendingUser
     * pendingProject
     */
    enum TypeNotification {
    	projectAccepted,
    	projectRejected,
    	projectExpired,
    	projectAchieved,
    	projectGroup,
    	pendingUser,
    	pendingProject,
    	userBanned,
    	userUnbanned
    }

    /**
     * Getter for the title of Notification
     * @return title
     */
    public String getTitle() {
        return title;
    }
    
    /**
     * Sets the title of the notification depending on what type of notification is
     * @see TypeNotification
     */
    public void setTitle() {
    	if(notification == TypeNotification.projectAccepted) {
    		title = "Project accepted";
    	} else if (notification == TypeNotification.projectRejected) {
    		title = "Project rejected";
    	} else if (notification == TypeNotification.projectExpired) {
    		title = "Project expired";
    	} else if (notification == TypeNotification.projectAchieved) {
    		title = "Project achieved";
    	} else if(notification == TypeNotification.pendingUser){
    		title = "Pending user";
    	} else if(notification == TypeNotification.pendingProject) {
    		title = "Pending project";
    	} else if (notification == TypeNotification.userBanned) {
    		title = "User banned";
    	} else if (notification == TypeNotification.userUnbanned) {
    		title = "User unbanned";
    	} else {
    		title = "Group voted a project";
    	}
    }
    
    /**
     * Getter for the body of Notification
     * @return body
     */
    public String getBody() {
        return body;
    }
    
    /**
     * Sets the body of the notification depending on what type of notification is
     * @see TypeNotification
     */
    public void setBody() {
    	String myTitle;
    	myTitle = this.getTitle();
    	
    	if (myTitle == "Project accepted") {
    		body = "Your project has been accepted";
    	} else if (myTitle == "Project rejected") {
    		body = "Your project has been rejected";
    	} else if (myTitle == " Project expired") {
    		body = "Your project has expired (30 days have passed since the acceptance)";
    	} else if (myTitle == "Project achieved") {
    		body = "Your project has reached the number of votes required";
    	} else if (myTitle == "Pending user") {
    		body = "A new user has registered, pending acceptance";
    	} else if (myTitle == "Pending project") {
    		body = "A new project has been launched, pending acceptance";
    	} else if (myTitle == "User banned") {
    		body = "You have been banned by the administrator";
    	} else if (myTitle == "User unbanned") {
    		body = "You have been unbanned by the administrator";
    	} else {
    		body = "Your group has voted a project";
    	}
    }
    
    /**
     * Sets the read field to true
     */
    public void setRead() {
        read = true;
    }
    
    /**
     * Getter for the read of Notification
     * @return read
     */
    public boolean getRead() {
        return read;
    }
    
    /**
     * Getter for the sent date of Notification
     * @return sentDate
     */
    public LocalDate getSentDate() {
        return sentDate;
    }

    
}