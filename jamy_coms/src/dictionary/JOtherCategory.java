package dictionary;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author oriol
 */
abstract public class JOtherCategory extends JComsCategory {
    
    JOtherCategory(){
        super(eCategories.eCATEGORY_OTHER.ordinal(), "other category");
        build();
    }
    
    public static boolean isValidAction(int value){
        return (value > eOtherActions.eOTHER_UNDEF.ordinal() && value < eOtherActions.eOTHER_DIM.ordinal());
    }
    
    public static String describeAction(int value){
        
        String desc;
        
        if(value == eOtherActions.eOTHER_ARM_STOP.ordinal())
            desc = "stop";
        else if(value == eOtherActions.eOTHER_KEEP_TILT.ordinal())
            desc = "keep tilt";
        else if(value == eOtherActions.eOTHER_AMY_END.ordinal())
            desc =  "end";
        else
            desc = "unknown";           
        
        return desc;
    }
    
    @Override
    protected final void build(){
        
        listCommands.clear();
    
        // define pan cyclic commands
        JComsCommand oCommand = new JComsCommand(ID, eOtherActions.eOTHER_ARM_STOP.ordinal(), "stop", 0, "stop arm");      
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eOtherActions.eOTHER_KEEP_TILT.ordinal(), "keep", 0, "keep the tilt position");
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eOtherActions.eOTHER_AMY_END.ordinal(), "end", 0, "end amy process");
        listCommands.add(oCommand);
        
    }

    public enum eOtherActions
    {
         eOTHER_UNDEF,                       /*! undefined action */
         eOTHER_ARM_STOP,                 /*! stop arm */
         eOTHER_KEEP_TILT,                  /*! keep the tilt position */
         eOTHER_AMY_END,                   /*! end amy */
         eOTHER_DIM
    }
    
}


