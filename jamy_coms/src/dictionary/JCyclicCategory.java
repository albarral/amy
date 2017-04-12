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
abstract public class JCyclicCategory extends JComsCategory {
    
    public JCyclicCategory(){
        super(eCategories.eCATEGORY_CYCLIC.ordinal(), "cyclic category");
        build();
    }
    
    public static boolean isValidAction(int value){
        return (value > eCyclicActions.eCYCLIC_UNDEF.ordinal() && value < eCyclicActions.eCYCLIC_DIM.ordinal());
    }
    
    public static String describeAction(int value){
        
        String desc;
        
        if(value == eCyclicActions.eCYCLIC_PAN_FREQ.ordinal())
            desc = "pan frequency";
        else if(value == eCyclicActions.eCYCLIC_PAN_AMP.ordinal())
            desc = "pan amplitude";
        else if(value == eCyclicActions.eCYCLIC_PAN_TRIGGER.ordinal())
            desc =  "pan trigger";
        else if(value == eCyclicActions.eCYCLIC_PAN_STOP.ordinal())
            desc = "pan stop";
        else if(value == eCyclicActions.eCYCLIC_TILT_FREQ.ordinal())
            desc = "tilt frequency";
        else if(value == eCyclicActions.eCYCLIC_TILT_AMP.ordinal())
            desc = "tilt amplitude";
        else if(value == eCyclicActions.eCYCLIC_TILT_TRIGGER.ordinal())
            desc = "tilt trigger";
        else if(value == eCyclicActions.eCYCLIC_TILT_STOP.ordinal())
            desc = "tilt stop";
        else
            desc = "unknown";           
        
        return desc;
    }
    
    protected void build(){
        
        listCommands.clear();
    
        // define commands for pan cyclic movements
        JComsCommand oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_PAN_FREQ.ordinal(), "panf", 1, "set frequency of pan cycles (Hz)");    
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_PAN_AMP.ordinal(), "pana", 1, "set amplitude of pan cycles (degrees)");
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_PAN_TRIGGER.ordinal(), "pan1", 0, "trigger pan cyclic movement");
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_PAN_STOP.ordinal(), "pan0", 0, "stop pan cyclic movement");
        listCommands.add(oCommand);
        // define commands for tilt cyclic movements
        oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_TILT_FREQ.ordinal(), "tiltf", 1, "set frequency of tilt cycles (Hz)");    
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_TILT_AMP.ordinal(), "tilta", 1, "set amplitude of tilt cycles (degrees)");
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_TILT_TRIGGER.ordinal(), "tilt1", 0, "trigger tilt cyclic movement");
        listCommands.add(oCommand);
        oCommand = new JComsCommand(ID, eCyclicActions.eCYCLIC_TILT_STOP.ordinal(), "tilt0", 0, "stop tilt cyclic movement");
        listCommands.add(oCommand);
        
    }

    public enum eCyclicActions
    {
         eCYCLIC_UNDEF,                          /*! undefined cyclic action */
         eCYCLIC_PAN_FREQ,                      // pan movement 
         eCYCLIC_PAN_AMP,
         eCYCLIC_PAN_TRIGGER,
         eCYCLIC_PAN_STOP,
         eCYCLIC_TILT_FREQ,                      // tilt movement
         eCYCLIC_TILT_AMP,
         eCYCLIC_TILT_TRIGGER,
         eCYCLIC_TILT_STOP,
         eCYCLIC_DIM
    }
    
}

