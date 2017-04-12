/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package source;

import sections.*;
/**
 *
 * @author oriol
 */
public class JAmyClient {
    private JJointClient oJointClient;
    private JAxisClient oAxisClient;
    private JCyclicClient oCyclicClient;
    private JOtherClient oOtherClient;
    
    public JAmyClient(){
        
    }
    
    public JJointClient getJointClient() {return oJointClient;}
    public JAxisClient getAxisClient() {return oAxisClient;}
    public JCyclicClient getCyclicClient() {return oCyclicClient;}
    public JOtherClient getOtherClient() {return oOtherClient;}
    
    public void sendJointCommand(){
        sendCommand(oJointClient.getCommand());
    }
    public void sendAxisCommand(){
        sendCommand(oAxisClient.getCommand());        
    }
    public void sendCyclicCommand(){
        sendCommand(oCyclicClient.getCommand());        
    }
    public void sendOtherCommand(){
        sendCommand(oOtherClient.getCommand());        
    }
    
    // dummy method for to do commands
    public void toDoCommand(){
        // nothing done
        // dummy method for to do commands
    }
    
    public void setPort(int port) {}
    
    // command sending method specific for each AmyClient implementation
    protected void sendCommand(String text){}
}
