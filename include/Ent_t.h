#ifndef ENT_T_H
#define ENT_T_H


class Ent_t
{
    public:
        Ent_t(int x, int y);
        int x;
        int y;
        ~Ent_t();
        virtual char whatIam();
        void setCoordinates(int x,int y);
        int idSystem;
        int creationTime ; // should be of type time
        void print();

    protected:

    private:
};

#endif // ENT_T_H
