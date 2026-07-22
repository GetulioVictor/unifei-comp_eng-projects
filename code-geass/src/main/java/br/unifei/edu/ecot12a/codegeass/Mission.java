package br.unifei.edu.ecot12a.codegeass;

public abstract class Mission {
    private String objective;
    private String status;
    private String reward;

    public abstract void start();
    public abstract void complete();
    public abstract void fail();
    
    public String getObjective() {
        return objective;
    }
    public void setObjective(String objective) {
        this.objective = objective;
    }
    public String getStatus() {
        return status;
    }
    public void setStatus(String status) {
        this.status = status;
    }
    public String getReward() {
        return reward;
    }
    public void setReward(String reward) {
        this.reward = reward;
    }
    
}
