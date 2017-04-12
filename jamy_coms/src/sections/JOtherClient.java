/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sections;

import ifaces.iJComsOthers;
import dictionary.JOtherCategory;
import data.JOtherCommand;
/**
 *
 * @author oriol
 */
abstract public class JOtherClient implements iJComsOthers{
    
    private String text;
    
    public JOtherClient(){
        
        text = "";
    }
    
    public String getCommand() {return text;};
    
    private void updateText(JOtherCommand oOtherCommand){
        // if valid command, build textual form
    if (oOtherCommand.isValidCommand())
    {
        text = oOtherCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
    }
    
    @Override
    public void keepTilt(int value){
        JOtherCommand oJointsCommand = new JOtherCommand(JOtherCategory.eOtherActions.eOTHER_KEEP_TILT.ordinal(), value);
        updateText(oJointsCommand);
    }
    
    @Override
    public void endAmy(){
        JOtherCommand oJointsCommand = new JOtherCommand(JOtherCategory.eOtherActions.eOTHER_AMY_END.ordinal(), 0);
        updateText(oJointsCommand);
    }
}
