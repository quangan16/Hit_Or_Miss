#include "Item.h"
#include "Math.h"

Item::Item(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
    : Sprite2D(model, shader, texture), BoxCollider2D(GetItemPosition(), 64, 64)
{
}

void Item::SetRandomPosition() {
    int x, y;
    x = (float)rand() / RAND_MAX * (float)Globals::screenWidth;
    y = (float)rand() / RAND_MAX * (float)Globals::screenHeight;
    SetItemPosition(x, y);
}