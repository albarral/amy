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
abstract public class JJointsCategory extends JComsCategory {
    
    public JJointsCategory(){
        super(eCategories.eCATEGORY_JOINTS.ordinal(), "joints category");
        build();
    }
    // check if given action is valid for this category
    public static boolean isValidAction(int value){
         return (value > eJointActions.eJOINT_UNDEF.ordinal() && value < eJointActions.eJOINT_DIM.ordinal());
    }
    // describe given action name for this category
    public static String describeAction(int value){
        String desc;
        
        if(value == eJointActions.eJOINT_HS_POS.ordinal())
            desc = "hs pos";
        else if(value == eJointActions.eJOINT_VS_POS.ordinal())
            desc = "vs pos";
        else if(value == eJointActions.eJOINT_ELB_POS.ordinal())
            desc = "elb pos";
        else if(value == eJointActions.eJOINT_HWRI_POS.ordinal())
            desc = "hwri pos";
        else if(value == eJointActions.eJOINT_VWRI_POS.ordinal())
            desc = "vwri pos";
        else
            desc = "unknown";           
        
        return desc;
    }
    // builds category with a list of commands
    protected void build(){
       listCommands.clear();
       
       // define joint commands
       JComsCommand oCommand = new JComsCommand(ID,eJointActions.eJOINT_HS_POS.ordinal(), "hs", 1, "move horizontal shoulder joint (degrees)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eJointActions.eJOINT_VS_POS.ordinal(), "vs", 1, "move vertical shoulder joint (degrees)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eJointActions.eJOINT_ELB_POS.ordinal(), "elb", 1, "move elbow joint (degrees)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eJointActions.eJOINT_HWRI_POS.ordinal(), "hwri", 1, "move horizontal wrist joint (degrees)");
       listCommands.add(oCommand);
       oCommand = new JComsCommand(ID,eJointActions.eJOINT_VWRI_POS.ordinal(), "vwri", 1, "move vertical wrist joint (degrees)");
       listCommands.add(oCommand);
    
    }
    
    public enum eJointActions
    {
         eJOINT_UNDEF,                             /*! undefined joint action */
         eJOINT_HS_POS,                         /*! horizontal shoulder position */
         eJOINT_VS_POS,                         /*! vertical shoulder position  */
         eJOINT_ELB_POS,                        /*! elbow position  */
         eJOINT_HWRI_POS,                      /*! horizontal wrist position */
         eJOINT_VWRI_POS,                      /*! vertical wrist  position */
         eJOINT_DIM
    }
    
}
