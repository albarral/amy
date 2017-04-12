package dictionary;

import java.util.ArrayList;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author oriol
 */
abstract public class JComsCategory {
    
    public enum eCategories{
    eCATEGORY_UNDEF,               /*! undefined category */
    eCATEGORY_JOINTS,              /*! command of joint category */
    eCATEGORY_AXIS,                 /*! command of axis category */
    eCATEGORY_CYCLIC,            /*! command of cyclic category */
    eCATEGORY_OTHER,             /*! command of other category */
    eCATEGORY_DIM
}
    
    public int ID = 0;                    /*! category ID  */
    public String name = "";    /*! category name  */
     ArrayList<JComsCommand> listCommands = new ArrayList();  /*! list of commands for this category */
    
    public JComsCategory(){
        ID = eCategories.eCATEGORY_UNDEF.ordinal();   
        name = "undef";
    }
    public JComsCategory(int ID, String name){
        this.ID = ID;   
        this.name = name;
    }
    
    public int getID(){return ID;}
    public String getName(){return name;}
    public ArrayList getListCommand(){return listCommands;}
    
    // check if given category is valid
    public static boolean isValidCategory(int cat){
        return (cat > eCategories.eCATEGORY_UNDEF.ordinal() && cat < eCategories.eCATEGORY_DIM.ordinal()); 
    }    
    // check if given action is valid (depends on each category)
    
    // describe category
    @Override
    public String toString(){
        String desc = "ComsCategory: [id="  + String.valueOf(ID) + ", name=" + name + "]\n";
        int lenght = listCommands.size();
        for (int index = 0; index<lenght; index++){//JComsCommand oCommand: listCommands)
            JComsCommand oCommand;
            oCommand = listCommands.get(index);
            desc += oCommand.toString() + "\n";
        }
        return desc;
    }
    // describe category name
    public static String describeCategory(int value){
        
        String desc;
        
        if(value == eCategories.eCATEGORY_UNDEF.ordinal())
            desc = "undefined";
            
        else if(value == eCategories.eCATEGORY_JOINTS.ordinal())
            desc = "joint";
            
        else if(value == eCategories.eCATEGORY_AXIS.ordinal())
            desc = "axis";
            
        else if(value == eCategories.eCATEGORY_CYCLIC.ordinal())
            desc = "cyclic";
            
        else if(value == eCategories.eCATEGORY_OTHER.ordinal())
            desc = "other";
        else
            desc = "invalid";           
        
        return desc;
    }
    // describe given action name (depends on each category)
    
    // builds category with a list of commands
    abstract protected void build();
}


