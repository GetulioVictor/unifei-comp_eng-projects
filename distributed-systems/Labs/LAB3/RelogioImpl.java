import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.text.SimpleDateFormat;
import java.util.Date;

public class RelogioImpl extends UnicastRemoteObject implements Relogio {

    private static final SimpleDateFormat FORMATO_DATA =
            new SimpleDateFormat("dd/MM/yyyy");

    private static final SimpleDateFormat FORMATO_HORA =
            new SimpleDateFormat("HH:mm:ss");

    // Implementations must have an explicit constructor
    // in order to declare the RemoteException exception
    public RelogioImpl() throws RemoteException {
        super();
    }

    public String getData() throws RemoteException {
        String data = FORMATO_DATA.format(new Date());
        System.out.println("Metodo getData() chamado -> " + data);
        return data;
    }

    public String getHora() throws RemoteException {
        String hora = FORMATO_HORA.format(new Date());
        System.out.println("Metodo getHora() chamado -> " + hora);
        return hora;
    }
}
