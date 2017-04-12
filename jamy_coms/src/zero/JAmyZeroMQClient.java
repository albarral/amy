/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zero;

import org.zeromq.ZMQ;
import source.JAmyClient;
/**
 *
 * @author oriol
 */
public class JAmyZeroMQClient extends JAmyClient{
    
    ZMQ.Context context = ZMQ.context(1);
    ZMQ.Socket socketClient = context.socket(ZMQ.REQ);
    
    String clientPort;
    
    public JAmyZeroMQClient(){
        
        socketClient.setReceiveTimeOut(100);
    }
    
    @Override
    public void setPort(int port){
        
        clientPort = String.valueOf(port);
        socketClient.connect("tcp://localhost:"+clientPort);
        System.out.println("Client GUI ZMQ connecting...");
    }
    
    @Override
    public void sendCommand(String command){
        
        boolean send = socketClient.send(command, 0);

        byte[] responseBytes = socketClient.recv(0);
        String response = new String(responseBytes);
    }
}
