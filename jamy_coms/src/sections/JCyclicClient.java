/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sections;

import ifaces.iJComsCyclic;
import dictionary.JCyclicCategory;
import data.JCyclicCommand;

/**
 *
 * @author oriol
 */
public class JCyclicClient implements iJComsCyclic{

    private String text;
    
    public JCyclicClient(){
        text = "";
    }
    
    public String getCommand() {return text;};
    
    private void updateText(JCyclicCommand oCyclicCommand){
        // if valid command, build textual form
    if (oCyclicCommand.isValidCommand())
    {
        text = oCyclicCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
    }
    @Override
    public void panFrequency(float value) {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_PAN_FREQ.ordinal(), value);
        updateText(oCyclicCommand);
    }

    @Override
    public void panAmplitude(float value) {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_PAN_AMP.ordinal(), value);
        updateText(oCyclicCommand);
    }

    @Override
    public void panTrigger() {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_PAN_TRIGGER.ordinal(), 0);
        updateText(oCyclicCommand);
    }

    @Override
    public void panStop() {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_PAN_STOP.ordinal(), 0);
        updateText(oCyclicCommand);
    }

    @Override
    public void tiltFrequency(float value) {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_TILT_FREQ.ordinal(), value);
        updateText(oCyclicCommand);
    }

    @Override
    public void tiltAmplitude(float value) {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_TILT_AMP.ordinal(), value);
        updateText(oCyclicCommand);
    }

    @Override
    public void tiltTrigger() {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_TILT_TRIGGER.ordinal(), 0);
        updateText(oCyclicCommand);
    }

    @Override
    public void tiltStop() {
        JCyclicCommand oCyclicCommand = new JCyclicCommand(JCyclicCategory.eCyclicActions.eCYCLIC_TILT_STOP.ordinal(), 0);
        updateText(oCyclicCommand);
    }
    
}
