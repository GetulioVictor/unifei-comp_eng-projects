package br.unifei.edu.ecot12a.codegeass;

public class ArtificialIntelligence {
    private String name;
    private String capability;
    private String limitations;

    public ArtificialIntelligence(String name, String capability, String limitations) {
        this.name = name;
        this.capability = capability;
        this.limitations = limitations;
    }

    public void processData() {
        System.out.println(name + " processes data with capability " + capability);
    }

    public void calculateProbabilities() {
        System.out.println(name + " calculates outcomes but is limited by " + limitations);
    }
}