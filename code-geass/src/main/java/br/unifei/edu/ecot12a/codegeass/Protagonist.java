package br.unifei.edu.ecot12a.codegeass;

public class Protagonist extends Character implements GeassObserver {
    private String loyalty;
    private String plan;
    private boolean geassActive;

    public Protagonist(String name, String faction, String loyalty, String plan) {
        super(name, "Protagonist", faction);
        this.loyalty = loyalty;
        this.plan = plan;
    }
    
    @Override
    public void update(String geassState) {
        System.out.println(super.getName() + " updates on Geass state: " + geassState);
    }
    
    public void leadArmy() {
        System.out.println(super.getName() + " leads army with loyalty: " + loyalty);
    }
    
    public void executePlan() {
        System.out.println("Executing plan: " + plan);
    }

    public String getLoyalty() {
        return loyalty;
    }

    public void setLoyalty(String loyalty) {
        this.loyalty = loyalty;
    }

    public String getPlan() {
        return plan;
    }

    public void setPlan(String plan) {
        this.plan = plan;
    }

    public boolean isGeassActive() {
        return geassActive;
    }

    public void setGeassActive(boolean geassActive) {
        this.geassActive = geassActive;
    }
    
}