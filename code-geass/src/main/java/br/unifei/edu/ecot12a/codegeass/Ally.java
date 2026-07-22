package br.unifei.edu.ecot12a.codegeass;

public class Ally {
    private String trustLevel;
    private String motivationToHelp;

    public void provideSupport() {
        System.out.println("Providing support with trust level: " + trustLevel);
    }

    public void negotiateAlliance() {
        System.out.println("Negotiating alliance with motivation: " + motivationToHelp);
    }
}