#include <iostream>
#include <memory>
#include <eigen3/Eigen/Dense>


using Mat4 = Eigen::Matrix4d;

class CJoint{
    protected:
        //Membres protégés
        double q_;
        double qMin_;
        double qMax_;

    public:
        //constructeur
        CJoint();
        CJoint(double q, double qMin, double qMax);

        //destructeur
        virtual ~CJoint(){};

        //Méthodes virtuelles
        virtual Mat4 getTransform() const = 0 ;
        virtual std::string getTypename() const = 0;
        virtual std::unique_ptr<CJoint> clone() const = 0;

        //getters et setters
        double getQ() const { return q_; }
        double getQMin() const { return qMin_; }
        double getQMax() const { return qMax_; }
        void setQ(double q) {
            if(qMin_ < q && q < qMax_){
                q_ = q;
            }
            else{
                throw std::out_of_range("q est hors range");
            }
        }   


};

class CJointRevolute : public CJoint
{
    protected:
        double O = 0;
        double dx = 0;

    
    public:
        // Redéfinition des méthodes virtuelles pour notre classes dérivées
        virtual Mat4 getTransform() const override;
        virtual std::string getTypename() const override;
        virtual std::unique_ptr<CJoint> clone() const override;

        //getters et setters
        double getO() const { return O; }
        double getDx() const { return dx; }
        void setO(double o) { O = o; }
        void setDx(double dx) { this->dx = dx; }


};

class CJointPrismatic : public CJoint
{
    protected:
        double d = 0;

    public:
        // Redéfinition des méthodes virtuelles pour notre classes dérivées
        virtual Mat4 getTransform() const override;
        virtual std::string getTypename() const override;
        virtual std::unique_ptr<CJoint> clone() const override;

        //getters et setters
        double getD() const { return d; }
        void setD(double d) { this->d = d; }


};