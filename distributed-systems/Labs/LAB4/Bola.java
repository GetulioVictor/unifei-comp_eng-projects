import java.rmi.*;

public interface Bola extends Remote {
    public static final int MALE = 1;
    public static final int FEMALE = 2;
    public static final int BOTH = MALE + FEMALE;

    public String getDescription() throws RemoteException;
    public String getSport() throws RemoteException;
    public int getWeight() throws RemoteException;
}
