#ifndef __AMY_INTERFACE2_ARMNODE_H
#define __AMY_INTERFACE2_ARMNODE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/topics/Node.h"
#include "tron/topics/NodeSection.h"

namespace amy
{
// Definition of arm node sections and channels
 class ArmNode2 : public tron::Node
{
public:
    /*! arm sections */
    enum eArmSections
    {
        eSECTION_JOINTS,             /*! joints section */
        eSECTION_AXES,                /*! axes section  */
        eSECTION_CYCLER1,          /*! cycler 1 section  */
        eSECTION_CYCLER2,          /*! cycler 2 section  */
        eSECTION_EXTRA,             /*! extra section  */
        eSECTION_DIM
    };     
    
 private:
    /*! names of arm sections */
    const std::string SECTION_JOINTS = "joints";
    const std::string SECTION_AXES = "axes";
    const std::string SECTION_CYCLER1 = "cycler1";
    const std::string SECTION_CYCLER2 = "cycler2";
     
 public:     
   ArmNode2();

   // get node section with given code
   tron::NodeSection* getSection(int sectionCode);
   
    // build given topic (build topic name from its node/section/channel/type codes)
    virtual bool buildTopic(tron::Topic & oTopic) override;
    
    // return node description
    virtual std::string toString() override;    
    
     
};
}
#endif
