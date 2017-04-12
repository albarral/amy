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
abstract public class JAxisCategory extends JComsCategory {
    
    public JAxisCategory(){
        super(eCategories.eCATEGORY_AXIS.ordinal(), "axis_category");
        build();
    }
    // check if given action is valid for this category
    public static boolean isValidAction(int value){
         return (value > eAxisActions.eAXIS_UNDEF.ordinal() && value < eAxisActions.eAXIS_DIM.ordinal());
    }
    // describe given action name for this category
    public static String describeAction(int value){
        String desc;
        
        if(value == eAxisActions.eAXIS_PAN_POS.ordinal())
            desc = "pan pos";
        else if(value == eAxisActions.eAXIS_TILT_POS.ordinal())
            desc = "tilt pos";
        else if(value == eAxisActions.eAXIS_RAD_POS.ordinal())
            desc = "radius pos";
        else if(value == eAxisActions.eAXIS_PAN_SPEED.ordinal())
            desc = "pan speed";
        else if(value == eAxisActions.eAXIS_TILT_SPEED.ordinal())
            desc = "tilt speed";
        else if(value == eAxisActions.eAXIS_RAD_SPEED.ordinal())
            desc = "radius speed";
        else
            desc = "unknown";           
        
        return desc;
    }
    // builds category with a list of commands
    protected void build(){
       listCommands.clear();
       
       // define axis position commands
       JComsCommand oCommand = new JComsCommand(ID,eAxisActions.eAXIS_PAN_POS.ordinal(), "pan", 1, "move pan (degrees)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eAxisActions.eAXIS_TILT_POS.ordinal(), "tilt", 1, "move tilt (degrees)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eAxisActions.eAXIS_RAD_POS.ordinal(), "rad", 1, "move radius (cm)");
       listCommands.add(oCommand);
       
       // define axis speed commands
       oCommand = new JComsCommand(ID,eAxisActions.eAXIS_PAN_SPEED.ordinal(), "vpan", 1, "move pan at given speed (degrees/s)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eAxisActions.eAXIS_TILT_SPEED.ordinal(), "vtilt", 1, "move tilt at given speed (degrees/s)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eAxisActions.eAXIS_RAD_SPEED.ordinal(), "vrad", 1, "move tilt at given speed (degrees/s)");
       listCommands.add(oCommand);
    
    }
    
    public enum eAxisActions
    {
         eAXIS_UNDEF,                          /*! undefined axis action */
         eAXIS_PAN_POS,                       /*! pan position */
         eAXIS_TILT_POS,                       /*! tilt position */
         eAXIS_RAD_POS,                       /*! radial position */
         eAXIS_PAN_SPEED,                     /*! pan speed */
         eAXIS_TILT_SPEED,                     /*! tilt speed */
         eAXIS_RAD_SPEED,                      /*! radial speed */
         eAXIS_DIM
    }
}
