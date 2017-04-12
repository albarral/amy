/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sections;

import ifaces.iJComsAxis;
import dictionary.JAxisCategory;
import data.JAxisCommand;
/**
 *
 * @author oriol
 */
public class JAxisClient implements iJComsAxis {
    
    private String text;
    
    public JAxisClient(){
        text = "";
    }
    
    public String getCommand() {return text;};
    
    private void updateText(JAxisCommand oAxisCommand){
        // if valid command, build textual form
    if (oAxisCommand.isValidCommand())
    {
        text = oAxisCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
    }

    @Override
    public void panSpeed(float value) {
        JAxisCommand oAxisCommand = new JAxisCommand(JAxisCategory.eAxisActions.eAXIS_PAN_SPEED.ordinal(), value);
        updateText(oAxisCommand);
    }

    @Override
    public void tiltSpeed(float value) {
        JAxisCommand oAxisCommand = new JAxisCommand(JAxisCategory.eAxisActions.eAXIS_TILT_SPEED.ordinal(), value);
        updateText(oAxisCommand);
    }

    @Override
    public void radialSpeed(float value) {
        JAxisCommand oAxisCommand = new JAxisCommand(JAxisCategory.eAxisActions.eAXIS_RAD_SPEED.ordinal(), value);
        updateText(oAxisCommand);
    }

    @Override
    public void movePan(float value) {
        JAxisCommand oAxisCommand = new JAxisCommand(JAxisCategory.eAxisActions.eAXIS_PAN_POS.ordinal(), value);
        updateText(oAxisCommand);
    }

    @Override
    public void moveTilt(float value) {
        JAxisCommand oAxisCommand = new JAxisCommand(JAxisCategory.eAxisActions.eAXIS_TILT_POS.ordinal(), value);
        updateText(oAxisCommand);
    }

    @Override
    public void moveRadius(float value) {
        JAxisCommand oAxisCommand = new JAxisCommand(JAxisCategory.eAxisActions.eAXIS_RAD_POS.ordinal(), value);
        updateText(oAxisCommand);
    }
    
    
    
}
