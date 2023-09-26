package VoteLanding;

import es.uam.eps.sadp.grants.GrantRequest;

public class ProjectSend implements GrantRequest {
	
	private String extraData;
	private String projectDescription;
	private ProjectKind projectKind;
	private String projectTitle;
	private Double requestedAmount;

	public ProjectSend(Project p, ProjectKind projectKind) {
		this.extraData = Integer.toString(p.getDaysLeft());
		this.projectDescription = p.getDesc();
		this.projectKind = projectKind;
		this.projectTitle = p.getName();
		this.requestedAmount = Double.valueOf(p.getRequestedAmount());
	}
	
	/**
     * Getter for the extra data of a sent project
     * @return extra data
     */
	@Override
	public String getExtraData() {
		return extraData;
	}

	/**
     * Getter for the description of a sent project
     * @return projectDescrption
     */
	@Override
	public String getProjectDescription() {
		return projectDescription;
	}

	/**
     * Getter for the kind of a sent project
     * @return projectKind
     */
	@Override
	public ProjectKind getProjectKind() {
		return projectKind;
	}
	
	/**
     * Getter for the title of a sent project
     * @return projectTitle
     */
	@Override
	public String getProjectTitle() {
		return projectTitle;
	}

	/**
     * Getter for the requested amount of a sent project
     * @return requestedAmount
     */
	@Override
	public double getRequestedAmount() {
		return requestedAmount;
	}
	
}
