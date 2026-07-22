package br.unifei.edu.ecot12a.codegeass;

public class Spy extends Character {
    private String alias;
    private String disguiseSkill;

    public Spy(String name, String alias, String disguiseSkill) {
        super(name, "Spy", disguiseSkill);
        this.alias = alias;
        this.disguiseSkill = disguiseSkill;
    }

    public void infiltrate() {
        System.out.println(getName() + " infiltrates with disguise skill: " + disguiseSkill);
    }

    public void gatherInfo() {
        System.out.println(getName() + " gathers information undercover.");
    }

    public void report() {
        System.out.println(getName() + " reports intel as: " + alias);
    }
}