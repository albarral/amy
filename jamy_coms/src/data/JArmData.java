/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 *
 * @author oriol
 */
public class JArmData {
    public static int numJoints = 5; // num joints in soll & ist messages
    
    // (commanded) soll angles of joints 1 to 5
    private float sollHS;    
    private float sollVS;    
    private float sollEL;    
    private float sollHW;    
    private float sollVW;    
    // (measured) ist angles of joints 1 to 5
    private float istHS;     
    private float istVS;      
    private float istEL;     
    private float istHW;     
    private float istVW;
    
    // reset values for all joints
    public void reset(){
        sollHS = 0;
        sollVS = 0;
        sollEL = 0;
        sollHW = 0;
        sollVW = 0;

        istHS = 0;
        istVS = 0;
        istEL = 0;
        istHW = 0;
        istVW = 0;
    }        
    // set soll (commanded) values for each joint
    public void setSollHS(float value) {sollHS = value;}
    public void setSollVS(float value) {sollVS = value;}
    public void setSollEL(float value) {sollEL = value;}
    public void setSollHW(float value) {sollHW = value;}
    public void setSollVW(float value) {sollVW = value;}        
    // gets soll (commanded) values for all joints
    public float getSollHS() {return sollHS;};        
    public float getSollVS() {return sollVS;};        
    public float getSollEL() {return sollEL;};        
    public float getSollHW() {return sollHW;};        
    public float getSollVW() {return sollVW;};                
    // set ist (measured) values for each joint
    public void setIstHS(float value) {istHS = value;}
    public void setIstVS(float value) {istVS = value;}
    public void setIstEL(float value) {istEL = value;}
    public void setIstHW(float value) {istHW = value;}
    public void setIstVW(float value) {istVW = value;}        
    // get ist (measured) values for each joint
    public float getIstHS() {return istHS;};        
    public float getIstVS() {return istVS;};        
    public float getIstEL() {return istEL;};        
    public float getIstHW() {return istHW;};        
    public float getIstVW() {return istVW;};        

    // check if specified object has same soll values
    public boolean sameSollValues(JArmData oArmData){
        return ((sollHS == oArmData.sollHS) &&
                (sollVS == oArmData.sollVS) &&
                (sollEL == oArmData.sollEL) &&
                (sollHW == oArmData.sollHW) &&
                (sollVW == oArmData.sollVW));
    }
    // check if specified object has same ist values        
    public boolean sameIstValues(JArmData oArmData){
        return ((istHS == oArmData.istHS) &&
                (istVS == oArmData.istVS) &&
                (istEL == oArmData.istEL) &&
                (istHW == oArmData.istHW) &&
                (istVW == oArmData.istVW));
    }

    // builds a soll message from the existing soll data 
    public String createSollMessage()
    {
        // build the soll message writing each soll value in a different line
    String separator = "*";
    
    String message = String.valueOf(sollHS) + separator 
                                  + String.valueOf(sollVS) + separator 
                                  + String.valueOf(sollEL) + separator 
                                  + String.valueOf(sollHW) + separator 
                                  + String.valueOf(sollVW) + "\n";
    
    return message;
    }
    // extracts the soll data from a given soll message  
    public boolean processSollMessage(String message){
        boolean bvalid = false;
        String separator = "*";

        // split the soll message in tokens, where each token is a soll value
        List<String> listTokens = Arrays.asList(message.split(separator));

        // then transform each token (soll value in textual form) to its numeric value
        if (listTokens.size() == JArmData.numJoints)
        {             
            sollHS = Float.valueOf(listTokens.get(0));
            bvalid = !Float.isNaN(sollHS);
            if (bvalid){
                sollVS = Float.valueOf(listTokens.get(1));
                bvalid = !Float.isNaN(sollVS);
            }
            if (bvalid){
                sollEL = Float.valueOf(listTokens.get(2));
                bvalid = !Float.isNaN(sollEL);
            }
            if (bvalid){
                sollHW = Float.valueOf(listTokens.get(3));
                bvalid = !Float.isNaN(sollHW);
            }
            if (bvalid){
                sollVW = Float.valueOf(listTokens.get(4));
                bvalid = !Float.isNaN(sollVW);
            }
        }
        return bvalid;
    }

    // returns a description of the object
    public String toString(){
       
        String desc = "[ArmData]: \n sollHS = " + String.valueOf(sollHS) + 
                             "\n sollVS = " + String.valueOf(sollVS) +
                             "\n sollEL = " + String.valueOf(sollEL) +
                             "\n sollHW = " + String.valueOf(sollHW) +
                             "\n sollVW = " + String.valueOf(sollVW) +
                             "\n istHS = " + String.valueOf(istHS) + 
                             "\n istVS = " + String.valueOf(istVS) + 
                             "\n istEL = " + String.valueOf(istEL) + 
                             "\n istHW = " + String.valueOf(istHW) + 
                             "\n istVW = " + String.valueOf(istVW);
    
    return desc;
    }
    
}
