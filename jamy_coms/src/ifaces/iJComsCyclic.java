/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ifaces;

/**
 *
 * @author oriol
 */
public interface iJComsCyclic {
        
    // pan cyclic movements
    public void panFrequency(float value);
    public void panAmplitude(float value);
    public void panTrigger();
    public void panStop();
    
    // tilt cyclic movements
    public void tiltFrequency(float value);
    public void tiltAmplitude(float value);
    public void tiltTrigger() ;
    public void tiltStop();
}
