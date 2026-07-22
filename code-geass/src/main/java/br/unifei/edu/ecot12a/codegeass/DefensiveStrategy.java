package br.unifei.edu.ecot12a.codegeass;

public class DefensiveStrategy implements Strategy {
    @Override
    public void execute() {
        System.out.println("Executing defensive strategy.");
    }

    @Override
    public void adjust() {
        System.out.println("Adjusting defensive positioning.");
    }
}