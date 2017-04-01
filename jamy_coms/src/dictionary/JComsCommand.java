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
public class JComsCommand {
    protected int category;         /*! category to which the command belongs */
    protected int ID;               /*! command ID */
    protected String name;          /*! command name */ 
    protected int numElements;      /*! additional elements needed to complete the command */
    protected String description;   /*! command description */ 
    
    public JComsCommand(){
        this.category = 0;
        this.ID = 0;
        this.name = "";
        this.numElements = 0;
        this.description = "";
    }
    public JComsCommand(int category, int ID, String name, int numElements, String description){
        this.category = category;
        this.ID = ID;
        this.name = name;
        this.numElements = numElements;
        this.description = description;
    }
    
    public int getCategory(){return category;}
    public int getID(){return ID;}
    public String getName(){return name;}
    public int getNumElements(){return numElements;}
    public String getDescription(){return description;}
    
    //describe command
    public String toString(){
        
        String desc = "ComsCommand: [id="  + String.valueOf(ID) +
            ", category=" + String.valueOf(category) +
            ", name=" + name + 
            ", numElements=" + String.valueOf(numElements) + 
            ", desc=" + description + "]\n";
    
    return desc;    
    }
}
