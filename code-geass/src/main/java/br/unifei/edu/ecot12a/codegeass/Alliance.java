package br.unifei.edu.ecot12a.codegeass;

import java.util.List;

public class Alliance {
    private List<Faction> members;
    private String commonGoal;

    public void form() {
        System.out.println("Forming an alliance with common goal: " + commonGoal);
    }

    public void dissolve() {
        System.out.println("Dissolving the alliance.");
    }

    public void renegotiateTerms() {
        System.out.println("Renegotiating terms of the alliance.");
    }

    public List<Faction> getMembers() {
        return members;
    }

    public void setMembers(List<Faction> members) {
        this.members = members;
    }

    public String getCommonGoal() {
        return commonGoal;
    }

    public void setCommonGoal(String commonGoal) {
        this.commonGoal = commonGoal;
    }

    
}