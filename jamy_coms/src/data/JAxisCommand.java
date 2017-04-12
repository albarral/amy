/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import dictionary.JComsCategory;
import dictionary.JAxisCategory;

/**
 *
 * @author oriol
 */
public class JAxisCommand extends JAmyCommand{
    
    public JAxisCommand(int action, float value){
        
        category = JComsCategory.eCategories.eCATEGORY_AXIS.ordinal();
        this.action = action;
        this.value = value;
        bvalid = JAxisCategory.isValidAction(action);
    }  
}
