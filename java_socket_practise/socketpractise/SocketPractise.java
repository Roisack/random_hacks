/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package socketpractise;

import java.net.*;
import java.io.*;
import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author gekko
 */
public class SocketPractise {

    public static int workersReady = 0;
    public static int workersCreated = 0;

    
    public static class Lock {
        private boolean isLocked = false;
        
        public synchronized void lock() throws InterruptedException {
            while (isLocked) {
                wait();
            }
            isLocked = true;
        }
        
        public synchronized void unlock() {
            isLocked = false;
            notify();
        }
    }
    
    public static Lock lock = new Lock();
    
    public static void reportReady() throws InterruptedException {
        lock.lock();
        workersReady++;
        lock.unlock();
    }
    
    public static class Worker extends Thread {
        
        int totalNumbers;
        ArrayList numberStorage;
        int remotePort;
        ObjectOutputStream out;
        ObjectInputStream in;
        Socket connection;
        
        public Worker(int p) {
            remotePort = p;
            numberStorage = new ArrayList();
        }
        
        public void run() {
            try {
                System.out.println("Worker " + remotePort + " opening connection");
                connection = new Socket("localhost", remotePort);
                out = new ObjectOutputStream(connection.getOutputStream());
                in = new ObjectInputStream(connection.getInputStream());
            } catch (UnknownHostException ex) {
                Logger.getLogger(SocketPractise.class.getName()).log(Level.SEVERE, null, ex);
            } catch (IOException ex) {
                Logger.getLogger(SocketPractise.class.getName()).log(Level.SEVERE, null, ex);
            }
            try {
                totalNumbers = in.readInt();
            } catch (IOException ex) {
                Logger.getLogger(SocketPractise.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            int numbersReceived = 0;
            System.out.println("Worker " + remotePort + " beginning to read " + totalNumbers);
            while (numbersReceived < totalNumbers) {
                try {
                    int randomInt = in.readInt();
                    numberStorage.add(randomInt);
                    numbersReceived++;
                } catch (IOException ex) {
                    Logger.getLogger(SocketPractise.class.getName()).log(Level.SEVERE, null, ex);
                }
                
            }
            try {
                out.flush();
                out.close();
                in.close();
                connection.close();
            } catch (IOException ex) {
                Logger.getLogger(SocketPractise.class.getName()).log(Level.SEVERE, null, ex);
            }
            try {
                reportReady();
            } catch (InterruptedException ex) {
                Logger.getLogger(SocketPractise.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException, InterruptedException {
        
        int port = 3000;

        for (int i = 0; i < 10; i++) {
            System.out.println("main: opening socket");
            Socket requestSocket;
            requestSocket = new Socket("localhost", 3000);
            ObjectOutputStream out;
            out = new ObjectOutputStream(requestSocket.getOutputStream());
            ObjectInputStream in;
            in = new ObjectInputStream(requestSocket.getInputStream());
            
            int servicePort = in.readInt();
            System.out.println("main: Got port " + servicePort);
            if (servicePort == -1) {
                System.out.println("main: Got -1! Skipping");
                out.close();
                in.close();
                requestSocket.close();
                continue;
            }
            Worker w = new Worker(servicePort);
            w.start();
            workersCreated++;
            out.close();
            in.close();
            requestSocket.close();
       }
        
        while (workersReady < workersCreated) {
            System.out.println("main: " + workersReady + "/" + workersCreated);
            Thread.sleep(1000);
        }
        
        System.out.println("main: Done");
        
    }
}
