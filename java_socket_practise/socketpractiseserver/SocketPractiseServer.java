/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package socketpractiseserver;

import java.net.*;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author gekko
 */

public class SocketPractiseServer {
    
    public static final int port_start = 3001;
    public static final int port_stop = 3050;
    public static int assigned_ports = 0;
    public static ObjectOutputStream out;
    public static ObjectInputStream in;
    
    public static class NumberServer extends Thread {
        int servicePort;
        ServerSocket serverSocket;
        Socket connection;
        ObjectOutputStream out;
        ObjectInputStream in;
        
        public NumberServer(int p) {
            servicePort = p;
        }
        
        public void run() {
            try {
                serverSocket = new ServerSocket(servicePort);
                serverSocket.setSoTimeout(50000);
                System.out.println("Numberserver " + servicePort + " waiting for connections");
                connection = serverSocket.accept();
                out = new ObjectOutputStream(connection.getOutputStream());
                in = new ObjectInputStream(connection.getInputStream());
            } catch (UnknownHostException ex) {
                Logger.getLogger(SocketPractiseServer.class.getName()).log(Level.SEVERE, null, ex);
            } catch (IOException ex) {
                Logger.getLogger(SocketPractiseServer.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            int randomcount = (int)(Math.random()*98) + 2;
            int i = 0;

            System.out.println("NumberServer " + servicePort + " Telling remote randomcount");
            try {
                out.writeInt(randomcount);
            } catch (IOException ex) {
                Logger.getLogger(SocketPractiseServer.class.getName()).log(Level.SEVERE, null, ex);
            }

            System.out.println("NumberServer " + servicePort + "Writing " + randomcount + " numbers");
            while (i < randomcount) {
                int randomNumber = (int)(Math.random()*100);
                System.out.println("NumberServer " + servicePort + "Writing " + randomNumber);
                try {
                    out.writeInt(randomNumber);
                } catch (IOException ex) {
                    Logger.getLogger(SocketPractiseServer.class.getName()).log(Level.SEVERE, null, ex);
                }
                i++;
            }
            
            try {
                out.flush();
                out.close();
                in.close();
                connection.close();
                serverSocket.close();
            } catch (IOException ex) {
                Logger.getLogger(SocketPractiseServer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    public static int getNextFreePort() {
        int p;
        
        p = port_start + assigned_ports;
        if (p > port_stop)
            return -1;
        assigned_ports++;
        
        return p;
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(port_start-1);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        
        serverSocket.setSoTimeout(500000);
        
        Socket connection = null;
        boolean running = true;
        while (running) {
            
            System.out.println("main: Waiting...");
            try {
                connection = serverSocket.accept();
            } catch (SocketTimeoutException ex) {
                continue;
            }
            
            System.out.println("main: Got contact");
            
            out = new ObjectOutputStream(connection.getOutputStream());

            out.flush();
            in = new ObjectInputStream(connection.getInputStream());
            
            int p = getNextFreePort();
            NumberServer ns = new NumberServer(p);
            ns.start();
            out.writeInt(p);
            System.out.println("main: Assigned port " + p);
            out.close();
            in.close();
            connection.close();
        }
        System.out.println("main: Done");
    }
}
