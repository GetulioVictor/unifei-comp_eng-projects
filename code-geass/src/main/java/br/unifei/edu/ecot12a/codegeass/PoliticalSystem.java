package br.unifei.edu.ecot12a.codegeass;

import java.util.List;

public class PoliticalSystem {
    private List<Realm> realms;
    private List<Government> governments;
    private List<Revolution> revolutions;

    public void manageRealm(Realm realm) {
        System.out.println("Managing realm: " + realm.getName());
    }

    public void implementPolicy(Government government, String policy) {
        government.getPolicies().add(policy);
        System.out.println("Implementing policy: " + policy);
    }

    public void suppressRevolution(Government government, Revolution revolution) {
        System.out.println("Suppressing revolution: " + revolution.getCause());
    }

    public void mobilizeForces(Realm realm) {
        System.out.println("Mobilizing forces in realm: " + realm.getName());
    }

    public void negotiatePeace(Government government, Revolution revolution) {
        System.out.println("Negotiating peace between " + government.getType() + " and revolution with cause: " + revolution.getCause());
    }

    public List<Realm> getRealms() {
        return realms;
    }

    public void setRealms(List<Realm> realms) {
        this.realms = realms;
    }

    public List<Government> getGovernments() {
        return governments;
    }

    public void setGovernments(List<Government> governments) {
        this.governments = governments;
    }

    public List<Revolution> getRevolutions() {
        return revolutions;
    }

    public void setRevolutions(List<Revolution> revolutions) {
        this.revolutions = revolutions;
    }

    
}