/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import dictionary.JComsCategory;
import dictionary.JCyclicCategory;
/**
 *
 * @author oriol
 */
public class JCyclicCommand extends JAmyCommand{
    
    public JCyclicCommand(int action, float value){
        
        category = JComsCategory.eCategories.eCATEGORY_CYCLIC.ordinal();
        this.action = action;
        this.value = value;
        bvalid = JCyclicCategory.isValidAction(action);
    }
}
