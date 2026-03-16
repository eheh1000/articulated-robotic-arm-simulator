#include <vector>
#include "CJoint.h"

class CBras{
    protected:
        std::vector<std::unique_ptr<CJoint>> bras_;

    public:
        //constructeur 
        CBras();

        //destructeur
        ~CBras();

        //méthode
        void addJoint(std::unique_ptr<CJoint> joint);
        Mat4 ComputeFK();

        //getter
        int getNbJoints();
        CJoint* getJoint(size_t joint);

        //surchage de l'opérateur
        friend std::ostream& operator<<(std::ostream& os,const CBras& bras);



};