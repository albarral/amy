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
public class JComsDictionary {
    
    JJointsCategory oJointCategory;
    JAxisCategory oAxisCategory;
    JCyclicCategory oCyclicCategory;
    JOtherCategory oOtherCategory;
    
    JJointsCategory getJointCategory() {return oJointCategory;};
    JAxisCategory getAxisCategory() {return oAxisCategory;};
    JCyclicCategory getCyclicCategory() {return oCyclicCategory;};
    JOtherCategory getOtherCategory() {return oOtherCategory;};
    
     // describe dictionary
    public String toString(){
        String desc = "ComsDictionary: \n" + 
            oJointCategory.toString() + 
            oAxisCategory.toString() + 
            oCyclicCategory.toString() +
            oOtherCategory.toString();

    return desc;    
    }
    
    // describe given action name of the given category
    static String describeAction4Category(int cat, int action){
        
        String desc;
        
        if(cat == JComsCategory.eCategories.eCATEGORY_UNDEF.ordinal())
            desc = "undefined category";
        else if(cat == JComsCategory.eCategories.eCATEGORY_JOINTS.ordinal())
            desc = JJointsCategory.describeAction(action);
        else if(cat == JComsCategory.eCategories.eCATEGORY_AXIS.ordinal())
            desc =  JAxisCategory.describeAction(action);
        else if(cat == JComsCategory.eCategories.eCATEGORY_CYCLIC.ordinal())
            desc = JCyclicCategory.describeAction(action);
        else if(cat == JComsCategory.eCategories.eCATEGORY_OTHER.ordinal())
            desc = JOtherCategory.describeAction(action);
        else
            desc = "invalid category";            
        
        return desc;
        
    }
    
}
