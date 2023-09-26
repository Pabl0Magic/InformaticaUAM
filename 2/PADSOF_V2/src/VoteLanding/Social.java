package VoteLanding;

import java.io.IOException;

import es.uam.eps.sadp.grants.CCGG;
import es.uam.eps.sadp.grants.GrantRequest;
import es.uam.eps.sadp.grants.InvalidRequestException;
import es.uam.eps.sadp.grants.GrantRequest.ProjectKind;

/**
 * Social class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class Social extends Project{
    private String targetGroup;
    private ScopeProject scope;
    
    public Social(String targetGroup, ScopeProject scope, String name, String desc, double requestedAmount) {
        super(name, desc, requestedAmount);
        this.targetGroup = targetGroup;
        this.scope = scope;
    }

    public enum ScopeProject {
        National,
        International
    }

    /**
     * Getter for the group targeted of a social project
     * @return targetGroup
     */
    public String getTargetGroup() {
        return targetGroup;
    }
    
    /**
     * Getter for the scope of a social project
     * @return ScopeProject
     */
    public ScopeProject getScope() {
    	return scope;
    }
    
    /**
     * Sends a project to the external association 
     * 
     * @throws IOException
     * @throws InvalidRequestException
     */
    @Override
    public void sendExternalAssociation() throws InvalidRequestException, IOException{
    	try {
    		GrantRequest send = new ProjectSend(this, ProjectKind.Social);
    		CCId = CCGG.getGateway().submitRequest(send);
    	}catch (IOException error1) {
    		System.out.println(error1);
    	}catch(InvalidRequestException error2) {
    		System.out.println(error2);
    	}
    }
}