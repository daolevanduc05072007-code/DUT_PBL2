#include"Entity.h"
#include"AssetManager.h"
class Box : public Entity
{
    private:
        bool onTarget = false;
    public:
        Box(int x , int y , int cellSize , int offsetX , int offsetY ) ;

        void setX(int x);
        void setY(int y);
        void SetOnTarget( bool status );

        void Draw( const AssetManager &assets ) override ;
};