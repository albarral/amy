/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import dictionary.JComsCategory;

/**
 *
 * @author oriol
 */
public class JAmyCommand {
    
    public static String separator;
    
    protected int category;   /*! command category  */
    protected int action;       /*! action to be performed */
    protected float value;     /*! value applied by the action */
    protected boolean bvalid;     /*! command validity */   
    protected String text;       /*! command textual form */ 
    
    JAmyCommand(){
        category = JComsCategory.eCategories.eCATEGORY_UNDEF.ordinal();
        action = 0;
        value = 0;
        text = "";
        bvalid = false;
    }
    
    JAmyCommand(int action, float value)
    {
        // undefined category, invalid command
        category = JComsCategory.eCategories.eCATEGORY_UNDEF.ordinal();
        this.action = action;
        this.value = value;
        bvalid = false;
    }
    
    public int getCategory() {return category;};
    public int getAction() {return action;};
    public float getValue() {return value;};
    public boolean isValidCommand() {return bvalid;};
    public String getText() {return text;};
    
    public String buildTextualForm()
    {
        // the textual command is built by 3 numbers (category, action and value) separated by the predefined separator (the "*" character)
        text = String.valueOf(category) + separator + String.valueOf(action) + separator + String.valueOf(value);
        return text;
    }
    protected String describeAction()
    {
        return "invalid";    
    }
}
