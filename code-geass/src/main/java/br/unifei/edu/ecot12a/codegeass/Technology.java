package br.unifei.edu.ecot12a.codegeass;

public class Technology {
    private String name;
    private String application;
    private String developer;

    public Technology(String name, String application, String developer) {
        this.name = name;
        this.application = application;
        this.developer = developer;
    }

    public void innovate() {
        System.out.println("Innovating " + name + " for " + application);
    }

    public void upgrade() {
        System.out.println(name + " being upgraded by " + developer);
    }

    public void implement() {
        System.out.println(name + " implemented in the field");
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getApplication() {
        return application;
    }

    public void setApplication(String application) {
        this.application = application;
    }

    public String getDeveloper() {
        return developer;
    }

    public void setDeveloper(String developer) {
        this.developer = developer;
    }

    
}