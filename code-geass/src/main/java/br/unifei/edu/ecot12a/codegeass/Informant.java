package br.unifei.edu.ecot12a.codegeass;

public class Informant extends Character {
    private String network;
    private String reliability;

    public Informant(String name, String network, String reliability) {
        super(name, "Informant", reliability);
        this.network = network;
        this.reliability = reliability;
    }

    public void collectInfo() {
        System.out.println(getName() + " collects information through network: " + network);
    }

    public void verifySource() {
        System.out.println(getName() + " verifies source with reliability: " + reliability);
    }

    public void transmit() {
        System.out.println(getName() + " transmits verified information.");
    }
}