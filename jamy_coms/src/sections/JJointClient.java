/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sections;

import ifaces.iJComsJoints;
import dictionary.JJointsCategory;
import data.JJointsCommand;

/**
 *
 * @author oriol
 */
public class JJointClient implements iJComsJoints {

    private String text;
    
    public JJointClient(){
        text = "";
    }
    
    public String getCommand() {return text;};
    
    private void updateText(JJointsCommand oJointsCommand){
        // if valid command, build textual form
    if (oJointsCommand.isValidCommand())
    {
        text = oJointsCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
    }
    
    @Override
    public void setPosHS(float value) {
        JJointsCommand oJointsCommand = new JJointsCommand(JJointsCategory.eJointActions.eJOINT_HS_POS.ordinal(), value);
        updateText(oJointsCommand);
    }

    @Override
    public void setPosVS(float value) {
        JJointsCommand oJointsCommand = new JJointsCommand(JJointsCategory.eJointActions.eJOINT_VS_POS.ordinal(), value);
        updateText(oJointsCommand);
    }

    @Override
    public void setPosELB(float value) {
        JJointsCommand oJointsCommand = new JJointsCommand(JJointsCategory.eJointActions.eJOINT_ELB_POS.ordinal(), value);
        updateText(oJointsCommand);
    }

    @Override
    public void setPosHW(float value) {
        JJointsCommand oJointsCommand = new JJointsCommand(JJointsCategory.eJointActions.eJOINT_HWRI_POS.ordinal(), value);
        updateText(oJointsCommand);
    }

    @Override
    public void setPosVW(float value) {
        JJointsCommand oJointsCommand = new JJointsCommand(JJointsCategory.eJointActions.eJOINT_VWRI_POS.ordinal(), value);
        updateText(oJointsCommand);
    }
    
}
