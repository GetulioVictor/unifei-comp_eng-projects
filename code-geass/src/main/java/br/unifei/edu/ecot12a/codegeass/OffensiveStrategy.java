package br.unifei.edu.ecot12a.codegeass;

public class OffensiveStrategy implements Strategy {
    @Override
    public void execute() {
        System.out.println("Executing offensive strategy.");
    }

    @Override
    public void adjust() {
        System.out.println("Adjusting offensive tactics.");
    }
}