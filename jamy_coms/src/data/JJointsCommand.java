/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package data;
import dictionary.JComsCategory;
import dictionary.JJointsCategory;
/**
 *
 * @author oriol
 */
public class JJointsCommand extends JAmyCommand{
    
    public JJointsCommand(int action, float value){
        
        category = JComsCategory.eCategories.eCATEGORY_JOINTS.ordinal();
        this.action = action;
        this.value = value;
        bvalid = JJointsCategory.isValidAction(action);
    }
    
}
