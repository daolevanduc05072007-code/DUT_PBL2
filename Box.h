#include"Entity.h"
#include"AssetManager.h"
class Box : public Entity
{
    private:
        bool IsOnTarget = false;
    public:
        Box(int X, int Y, int CellSize, int OffsetX, int OffsetY);

        void SetX(int X);
        void SetY(int Y);
        void SetOnTarget(bool Status);

        void Draw(const AssetManager& Assets) override;
};