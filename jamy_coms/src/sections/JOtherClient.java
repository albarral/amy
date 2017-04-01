/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sections;
import ifaces.iJComsOthers;
/**
 *
 * @author oriol
 */
abstract public class JOtherClient implements iJComsOthers{
    
    String text;
    
    JOtherClient(){
        
        text = "";
    }
    
    @Override
    public void keepTilt(int value){
        
    }
    
    @Override
    public void endAmy(){
        
    }
}
