
import java.net.*; // for Socket and ServerSocket
import java.io.*; // for IOException

class PoolDispatcher {
// Default thread-pool size

    private int numThreads = 8; // Number of threads in pool

    public void startDispatching(final ServerSocket servSock) {
// Create N-1 threads, each running an iterative server
        for (int i = 0; i < (numThreads - 1); i++) {
            Thread thread = new Thread() {
                public void run() {
                    dispatchLoop(servSock);
                }
            };
            thread.start();
            System.out.println("Created and started Thread = " + thread.getName());
        }
        System.out.println("Iterative server starting in main thread " + Thread.currentThread().getName());
// Use main thread as Nth iterative server
        dispatchLoop(servSock);
        /* NOT REACHEAD */
    }

    private void dispatchLoop(final ServerSocket servSock) {
// Run forever, accepting and handling each connection
        for (;;) {
            try {
// Block waiting for connection
                Socket clntSock = servSock.accept();
                Runnable protocol = new EchoProtocol(clntSock);
                protocol.run();
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public static void main(String[] args) throws Exception {

        int servPort = 7500;
        ServerSocket servSock = new ServerSocket(servPort);
        PoolDispatcher pd = new PoolDispatcher();
        pd.startDispatching(servSock);
        /* NOT REACHED */
    }
}
