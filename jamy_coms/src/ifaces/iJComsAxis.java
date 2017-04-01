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
public interface iJComsAxis {

    // axis speeds
    public void panSpeed(float value);
    public void tiltSpeed(float value);
    public void radialSpeed(float value);
        
    // axis positions   
    public void movePan(float value);
    public void moveTilt(float value);
    public void moveRadius(float value);
}
