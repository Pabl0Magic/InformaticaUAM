package VoteLanding;
import java.util.*;

import es.uam.eps.sadp.grants.*;
import java.io.*;

/**
 * Project class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public abstract class Project {
    private static long lastId = 1;
    private long id;
    protected String CCId;
    private String name;
    private String desc;
    private List<User> votedIndiv;
    private List<Group> votedGroup;
    private int votesRequired;
    private int numVotes;
    private Status status;
    private int daysLeft;
    private double requestedAmount;

    enum Status{
        Approved,
        Pending,
        Rejected
    }

    public Project(String name, String desc, double requestedAmount) {
        this.name = name;
        this.desc = desc;
        this.requestedAmount = requestedAmount;
        
        votedIndiv = new ArrayList<User>();
        votedGroup = new ArrayList<Group>();
        setId();
    } 

    /**
     * Getter for the id of a project
     * @return id
     */
    public long getId() {
        return id;
    }
    
    /**
     * Setter for the id of a project
     *
     */
    public void setId() {
    	id = lastId;
    	lastId++;
    }
    
    /**
     * Getter for the name of a project
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * Getter for the description of a project
     * @return description
     */
    public String getDesc() {
        return desc;
    }
    
    /**
     * Getter for the required votes of a project
     * @return votesRequired
     */
    public int getVotesRequired() {
        return votesRequired;
    }
    
    /**
     * Setter for the required votes of a project
     * @param num
     */
    public void setVotesRequired(int num) {
        votesRequired = num;
    }

    /**
     * Getter for the current number of votes of a project
     * @return numVotes
     */
    public int getNumVotes() {
        return numVotes;
    }
    
    /**
     * Setter for the current numuber of votes of a project
     * @param votes
     */
    public void setNumVotes(int votes) {
    	numVotes = votes;
    }

    /**
     * Getter for the status of a project
     * @return status
     */
    public Status getStatus() {
        return status;
    }
    
    /**
     * Setter for the status of a project
     * @param status
     */
    public void setStatus(Status stat) {
    	status = stat;
    }
    
    /**
     * Getter for the days left for a project to end
     * @return daysLeft
     */
    public int getDaysLeft() {
        return daysLeft;
    }
    
    /**
     * Setter for the days left for a project to end
     * @param num
     */
    public void setDaysLeft(int num) {
    	daysLeft = num;
    }
    
    /**
     * Getter for the CCIdx
     * @return CCId
     */
    public String getCCId() {
    	return CCId;
    }
    
    /**
     * Getter for the requested amount of a project
     * @return requestedAmount
     */
    public double getRequestedAmount() {
    	return requestedAmount;
    }
    
    /**
     * Updates the current number of votes if a project 
     * 
     */
    public void updateVotes() {
    	int votes = votedIndiv.size();
    	
    	for(Group g: votedGroup) {    		
    		for(User u: g.getFollower()) {
    			if(votedIndiv.contains(u)==false) {
    				votes++;
    			}
    		}	
    		if(votedIndiv.contains(g.getCreator())==false) {
    			votes++;
    		}
    	}
    	
    	setNumVotes(votes);
    	
    }
    
    /**
     * Adds a user to the list of individual voters and calls updateVotes()
     * @param user
     */
    public void voteProjectIndv(User u) {
    	if(votedIndiv.contains(u)==false) {
    		votedIndiv.add(u);
    		updateVotes();
    	}
    }
    
    /**
     * Returns the list with the users that have voted individually
     * @return votedIndiv
     */
    public List<User> getVotedIndiv() {
    	return votedIndiv;
    }
    
    /**
     * Adds a group to the list of group voters and calls updateVotes()
     * @param group
     */
    public void voteProjectGroup(Group g) {
    	if(votedGroup.contains(g)==false) {
    		votedGroup.add(g);
    		updateVotes();
    	}
    }
    
    /**
     * Returns the list with the groups that have voted a project
     * @return votedGroup
     */
    public List<Group> getVotedGroup() {
    	return votedGroup;
    }
    
    /**
     * Returns if a project has expired
     * @return boolean
     */
    public boolean checkExpired() {
    	if(daysLeft<=0) {
    		return true;
    	}else {
    		return false;
    	}
    }
    
    
    abstract public void sendExternalAssociation() throws InvalidRequestException, IOException;
    
    /* assignId lo hacemos en el constructor
     * contactEntity ni idea de como hacerlo
     * 
     */ 
    
    
    
    
}