import java.rmi.*;
import java.rmi.server.*;

public class BolaImpl extends UnicastRemoteObject implements Bola {
    private String name;
    private String sport;
    private int ageLow;
    private int ageHigh;
    private int sex;
    private int weight;

    public BolaImpl(String name, String sport, int sex,
                    int ageLow, int ageHigh, int weight)
            throws RemoteException {
        this.name = name;
        this.sport = sport;
        this.sex = sex;
        this.ageLow = ageLow;
        this.ageHigh = ageHigh;
        this.weight = weight;
    }

    public boolean match(Jogador j) {
        if (j.getAge() < ageLow || j.getAge() > ageHigh)
            return false;
        if (!j.getSport().equalsIgnoreCase(sport))
            return false;
        if ((sex & j.getSex()) == 0)
            return false;
        return true;
    }

    public String getDescription() throws RemoteException {
        return "Ball: " + name + " (" + sport + ", " + weight + "g)";
    }

    public String getSport() throws RemoteException {
        return sport;
    }

    public int getWeight() throws RemoteException {
        return weight;
    }
}
