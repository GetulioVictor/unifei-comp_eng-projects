package br.unifei.edu.ecot12a.codegeass;

public class Operation {
    private String type;
    private String timeLimit;

    public void plan() {
        System.out.println("Planning operation of type: " + type);
    }

    public void abort() {
        System.out.println(type + " operation is aborted");
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTimeLimit() {
        return timeLimit;
    }

    public void setTimeLimit(String timeLimit) {
        this.timeLimit = timeLimit;
    }

    
}