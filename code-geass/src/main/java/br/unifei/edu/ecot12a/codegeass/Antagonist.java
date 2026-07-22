package br.unifei.edu.ecot12a.codegeass;

public class Antagonist extends Character {
    private String rival;
    private String motivation;

    public Antagonist(String name, String faction, String rival, String motivation) {
        super(name, "Antagonist", faction);
        this.rival = rival;
        this.motivation = motivation;
    }
    
    public void confrontProtagonist() {
        System.out.println(super.getName() + " confronts " + rival + " driven by " + motivation);
    }
    
    public void scheme() {
        System.out.println(super.getName() + " schemes tactically");
    }

    public String getRival() {
        return rival;
    }

    public void setRival(String rival) {
        this.rival = rival;
    }

    public String getMotivation() {
        return motivation;
    }

    public void setMotivation(String motivation) {
        this.motivation = motivation;
    }
    
    
}